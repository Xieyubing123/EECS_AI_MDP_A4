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
                double newUtility = Rs + discountFactor * maxExp;
                double change = abs(newUtility - states.getUtility(i, j));
                
                if (change > maxChange)
                    maxChange = change;
                
                states.setUtility(i, j, newUtility);
            }
        }
        
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
                                 double discountFactor)
{
    StatesMap states = StatesMap(col, row);
    initStatesUtility(states);
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
    if (maxRs - minRs < 0.0001)
    {
        return;
    }
    string minPolStr = "";
    string maxPolStr = "";
    
    
    StatesMap minState =
    dynamicProgrammingMDPsolver(minRs, col, row, minErr, discountFactor);
    minPolStr = minState.makePlicyStr();
    RsPolicyMap[minRs] = minPolStr;
    
    StatesMap maxState =
    dynamicProgrammingMDPsolver(maxRs, col, row, minErr, discountFactor);
    maxPolStr = maxState.makePlicyStr();
    RsPolicyMap[maxRs] = maxPolStr;

    

    if (minPolStr == maxPolStr)
    {
        if (policyCount[minPolStr] < 1)
        {
            RsList.push_back(minRs);
            policyCount[minPolStr]++;
        }
    }
    else
    {
        if (policyCount[minPolStr] < 1)
        {
            RsList.push_back(minRs);
            policyCount[minPolStr]++;
        }
        
        if (policyCount[maxPolStr] < 1)
        {
            RsList.push_back(maxRs);
            policyCount[maxPolStr]++;
        }
        
        binarySearch(minRs, (maxRs + minRs)/2.0000000 , col,
                     row, minErr, discountFactor,
                     RsList,policyCount,RsPolicyMap);
        
        binarySearch((maxRs + minRs)/2.0000000, maxRs, col,
                     row, minErr, discountFactor,
                     RsList,policyCount,RsPolicyMap);
    }
    
    cout << RsList.size() << endl;
}

