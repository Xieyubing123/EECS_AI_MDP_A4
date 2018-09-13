#include "helper.h"

void initStatesUtility(StatesMap & states)
{
    //hardcode the textbook initial state 
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
    //hardcode the textbook initial state 
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

    for (int act = (int)UP; act <= (int)RIGHT; ++act)
    {

        double actExpect = states.getResultStatesExpect(col,
                                                        row,
                                                        (Action)act,
                                                        0.8,
                                                        0.1,
                                                        0.1);
        actExpects.push_back(actExpect);
        actionMap[actExpect] = act;
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
                double change = abs(newUtility - states.getUtility(i, j));
                
                if (change > maxChange)
                    maxChange = change;
                
                states.setUtility(i, j, newUtility);
            }
        }
        if (maxChange < miniErr)
            break;   
    }//while(true)
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

//dynamicProgrammingMDPsolver
StatesMap dpMDPsolver(double Rs,int col, int row, double minErr,
                         double discountFactor, const int problemNum)
{
    StatesMap states = StatesMap(col, row, Rs);
    if (problemNum == 1 || problemNum == 2)
        initStatesUtility(states);
    else
        initP3StatesUtility(states, problemNum);
    
    valueIteration(states, Rs, discountFactor,
                   minErr, col, row);
    
    findOptimalPolicy(states, col, row);
    return states;
}

//for solving problem 1 and 2
void binarySearch(double minRs, double maxRs, int col,
                  int row, double minErr,
                  double discountFactor,
                  vector<double> &RsList,
                  map<string, int>& policyCount,
                  map<double, string>& RsPolicyMap)
{
    double err = 0.0000001;
    const int PROBLEM_1 = 1;  //also work for problem 2

    if (maxRs - minRs < err)
        return;

    string minPolStr = "";
    string maxPolStr = "";
    
    StatesMap minState =
    dpMDPsolver(minRs, col, row, minErr, discountFactor, PROBLEM_1);
    minPolStr = minState.makePlicyStr();
    RsPolicyMap[minRs] = minPolStr;
    
    StatesMap maxState =
    dpMDPsolver(maxRs, col, row, minErr, discountFactor, PROBLEM_1);
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
    
}

//for solving problem 3
void gammaBinarySearch(double minDis, double maxDis, int col,
                        int row, double minErr, vector<double> &DisList,
                        double Rs, map<string, int>& policyCount,
                        map<double, string>& RsPolicyMap)
{
    double err = minErr;
    const int PROBLEM_3 = 3;
    if (maxDis - minDis < err)
        return;

    string minPolStr = "";
    string maxPolStr = "";
    
    
    StatesMap minState =
    dpMDPsolver(Rs, col, row, minErr, minDis, PROBLEM_3);
    minPolStr = minState.makePlicyStr();
    RsPolicyMap[minDis] = minPolStr;
    
    StatesMap maxState =
    dpMDPsolver(Rs, col, row, minErr, maxDis, PROBLEM_3);
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
    
}


//////////////////////////p2//////////////////////////////////////
//genreate/simulate a rundom action 
Action randomAct(Action act)
{
    int v1 = rand() % 100 + 1;         // v1 in the range 1 to 100
    
    vector<Action> UpRan = {UP, LEFT, RIGHT};
    vector<Action> DownRan = {DOWN, RIGHT, LEFT};
    vector<Action> LeftRan = {LEFT, DOWN, UP};
    vector<Action> RightRan = {RIGHT, UP, DOWN};
    vector<vector<Action>> randVec = {UpRan, DownRan, LeftRan, RightRan};

    if (v1 <= 80)
        return randVec[(int)act][0];
    else if (v1 <= 100 && v1 > 90)
        return randVec[(int)act][2];
    else
        return randVec[(int)act][1];
}

double simulateRun(StatesMap& states, int initX, int initY, double Rs)
{
    int x = initX;
    int y = initY;
    double reward = 0;

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

