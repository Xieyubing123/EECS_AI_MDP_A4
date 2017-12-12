#include<iostream>
#include<vector>
#include<map>
#include <cmath>        // std::abs
#include "State.cpp"

void initStatesUtility(StatesMap & states)
{
    states.setWall(2, 2);
    states.setTerminal(4, 2, -1);
    states.setTerminal(4, 3, 1);
    states.setUtility(1,1,0.705);
    states.setUtility(1,2,0.762);
    states.setUtility(1,3,0.812);
    states.setUtility(2,1,0.655);
    states.setUtility(2,3,0.868);
    states.setUtility(3,1,0.611);
    states.setUtility(3,2,0.660);
    states.setUtility(3,3,0.918);
    states.setUtility(4,1,0.388);
    states.setPolicy(2, 2, "X");
    states.setPolicy(4, 3, "+1");
    states.setPolicy(4, 2, "-1");
}

void initP3StatesUtility(StatesMap & states, double r)
{
    states.setTerminal(3, 3, 10);//set utitlity, col
    states.setUtility(1,1,0);
    states.setUtility(1,2,0);
    states.setUtility(1,3,0);
    states.setUtility(2,1,0);
    states.setUtility(2,2,0);
    states.setUtility(2,3,0);
    states.setUtility(3,1,0);
    states.setUtility(3,2,0);
    
    states.setCostOfLiving(1, 3, r);
    states.setPolicy(3, 3, "+10");
}

string actToStringPolicy(Action act)
{
    vector<string> str = {"^", "v", "<", ">"};
    return str[(int)act];
}

double findBestExp(StatesMap &states, int col, int row, Action &bestAct)
{
    vector<double> actExpects;
    map<double, int> actionMap;
    //for each action
    for (int act = (int)UP; act <= (int)RIGHT; ++act)
    {
        if (col == 3 && row == 2 && states.getUtility(3, 2) < -3.0389)
        {
            //states.printStates();
            //cout << states.getUtility(3, 2) << endl;
        }
        double actExpect = states.getResultStatesExpect(col,
                                                        row,
                                                        (Action)act,
                                                        0.8,
                                                        0.1,
                                                        0.1);
        actExpects.push_back(actExpect);
        actionMap[actExpect] = act;
        //cout << "(" << col << "," << row << "," << act << "," << actExpect << ")" << endl;
    }
    
    sort(actExpects.begin(), actExpects.end());
    double bestExp = actExpects[actExpects.size() - 1];
    bestAct = (Action)actionMap[bestExp];
    
    return bestExp;
}

void valueIteration(StatesMap &states, double Rs, double discountFactor,
                    double miniErr, int col, int row)
{
    //for each state
    while(true)
    {
        double maxChange = 0;
        
        for (int i = 1; i <= col; ++i)
        {
            for (int j = 1; j <= row; ++j)
            {
                State curState = states.getState(i, j);
                
                if (curState.wall || curState.terminal)
                    continue;
                
                Action tempAct = UP;
                double maxExp = findBestExp(states, i, j, tempAct);
                double newUtility = states.getStateCostOfLiving(i, j)
                                    + discountFactor * maxExp;
                ///cout << "(" << i << "," << j << ")" << "col: " << states.getStateCostOfLiving(i, j) << endl;
                //states.printStates();
                //cout << endl;
                double change = abs(newUtility - states.getUtility(i, j));
                
                if (change > maxChange)
                    maxChange = change;
                
                states.setUtility(i, j, newUtility);
            }
        }
        
        //states.printStates();

        if (maxChange < miniErr)
        {
            break;
        }
    }
}

void findOptimalPolicy(StatesMap &states, int col, int row)
{
    for (int i = 1; i <= col; ++i)
    {
        for (int j = 1; j <= row; ++j)
        {
            State curState = states.getState(i, j);
            
            if (curState.wall || curState.terminal)
                continue;
            
            Action bestAct = UP;
            findBestExp(states, i, j, bestAct);
            states.setPolicy(i, j, actToStringPolicy(bestAct));
        }
    }
}

StatesMap dynamicProgrammingMDPsolver(double Rs,int col,
                                 int row, double minErr,
                                 double discountFactor, int problemNum)
{
    StatesMap states = StatesMap(col, row, Rs);
    if (problemNum == 1 || problemNum == 2)
    {
        initStatesUtility(states);
    }
    else
    {
        initP3StatesUtility(states, 3);
        //states.printStates();
        //states.printCOL();

    }
    
    valueIteration(states, Rs, discountFactor,
                   minErr, col, row);
    
    findOptimalPolicy(states, col, row);
    return states;
}

void binarySearch(double minRs, double maxRs, int col,
                  int row, double minErr,
                  double discountFactor,
                  vector<double> &RsList,
                  map<string, int>& policyCount,
                  map<double, string>& RsPolicyMap)
{
    double err = 0.0000001;
    if (maxRs - minRs < err)
    {
        return;
    }
    string minPolStr = "";
    string maxPolStr = "";
    
    
    StatesMap minState =
    dynamicProgrammingMDPsolver(minRs, col, row, minErr, discountFactor, 1);
    minPolStr = minState.makePlicyStr();
    RsPolicyMap[minRs] = minPolStr;
    
    StatesMap maxState =
    dynamicProgrammingMDPsolver(maxRs, col, row, minErr, discountFactor, 1);
    maxPolStr = maxState.makePlicyStr();
    RsPolicyMap[maxRs] = maxPolStr;

    

    if (minPolStr == maxPolStr)
    {
        if (policyCount[maxPolStr] < 1)
        {
            RsList.push_back(maxRs);
            policyCount[maxPolStr]++;
        }
        
        
    }
    else
    {
        /*
        if (policyCount[minPolStr] < 1)
        {
            RsList.push_back(minRs);
            policyCount[minPolStr]++;
        }
        */
        
        if (policyCount[maxPolStr] < 1)
        {
            RsList.push_back(maxRs);
            policyCount[maxPolStr]++;
        }
        
        
        binarySearch((maxRs + minRs)/2.0000000, maxRs - err, col,
                     row, minErr, discountFactor,
                     RsList,policyCount,RsPolicyMap);
        
        binarySearch(minRs + err, (maxRs + minRs)/2.0000000 , col,
                     row, minErr, discountFactor,
                     RsList,policyCount,RsPolicyMap);
        

    }
    
    //cout << RsList.size() << endl;
}

void gammaBinarySearch(double minDis, double maxDis, int col,
                  int row, double minErr,
                  vector<double> &DisList,
                       double Rs,
                  map<string, int>& policyCount,
                  map<double, string>& RsPolicyMap)
{
    double err = minErr;
    if (maxDis - minDis < err)
    {
        return;
    }
    string minPolStr = "";
    string maxPolStr = "";
    
    
    StatesMap minState =
    dynamicProgrammingMDPsolver(Rs, col, row, minErr, minDis, 3);
    minPolStr = minState.makePlicyStr();
    RsPolicyMap[minDis] = minPolStr;
    
    StatesMap maxState =
    dynamicProgrammingMDPsolver(Rs, col, row, minErr, maxDis, 3);
    maxPolStr = maxState.makePlicyStr();
    RsPolicyMap[maxDis] = maxPolStr;
    
    
    
    if (minPolStr == maxPolStr)
    {
        if (policyCount[maxPolStr] < 1)
        {
            DisList.push_back(maxDis);
            policyCount[maxPolStr]++;
        }
        
        
    }
    else
    {
        /*
         if (policyCount[minPolStr] < 1)
         {
         RsList.push_back(minRs);
         policyCount[minPolStr]++;
         }
         */
        
        if (policyCount[maxPolStr] < 1)
        {
            DisList.push_back(maxDis);
            policyCount[maxPolStr]++;
        }
        
        
        gammaBinarySearch((maxDis + minDis)/2.0000000, maxDis - err, col,
                     row, minErr,
                     DisList, Rs, policyCount,RsPolicyMap);
        
        gammaBinarySearch(minDis + err, (maxDis + minDis)/2.0000000 , col,
                     row, minErr,
                     DisList, Rs, policyCount,RsPolicyMap);
        
        
    }
    
    //cout << RsList.size() << endl;
}

/////////////////////////////////////////////////////////////////////////////////////
/////////////////p2/////////////////

Action randomAct(Action act)
{
    int v1 = rand() % 100 + 1;         // v1 in the range 1 to 100
    
    vector<Action> UpRan = {UP, LEFT, RIGHT};
    vector<Action> DownRan = {DOWN, RIGHT, LEFT};
    vector<Action> LeftRan = {LEFT, DOWN, UP};
    vector<Action> RightRan = {RIGHT, UP, DOWN};
    
    vector<vector<Action>> randVec = {UpRan, DownRan, LeftRan, RightRan};
    if (v1 <= 80)
    {
        return randVec[(int)act][0];
    }
    else if (v1 <= 100 && v1 > 90)
    {
        return randVec[(int)act][2];
    }
    else
    {
        return randVec[(int)act][1];
    }
}

double simulateRun(StatesMap& states, int initX, int initY, double Rs)
{
    int x = initX;
    int y = initY;
    double reward = 0;
    //get
    //nextState = states.getResultStates(x, y, randomAct())
    while (true)
    {
        Action bestAct = UP;
        findBestExp(states, x, y, bestAct);
        
        Action randomizedAct = randomAct(bestAct);
        State newState = states.getResultStates(x, y, randomizedAct)[0];
        reward += Rs;
        
        if(newState.terminal)
        {
            reward += newState.utility;
            break;
        }
        
        x = newState.idx + 1;
        y = newState.idy + 1;
    }
    
    return reward;
}

