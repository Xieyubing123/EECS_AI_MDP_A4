#ifndef STATESMAP_H
#define STATESMAP_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <map>
#include "State.h"
using namespace std;


class StatesMap
{
public:
    int maxX;
    int maxY;
    double Rs;
    vector< vector<State> > states;
    vector<string> policyVec;
    string policyStr;
    vector<State> StateVec;

    StatesMap(int x, int y, double CostOfLiving);
    void initMap();
    
    double getStateCostOfLiving(int x, int y);
    double getUtility(int x, int y);
    State getState(int x, int y);
    vector<State> getResultStates(int x, int y, Action act);
    double getResultStatesExpect(int x, int y, Action act,
                                 double prob1, double prob2,
                                 double prob3);

    void setWall(int x, int y);
    void setRs(double r);
    void setTerminal(int x, int y, double u);
    void setUtility(int x, int y, double utility);
    void setCostOfLiving(int x, int y, double col);
    void setPolicy(int x, int y, string pol);

    string makePlicyStr();
    State resultState(int idx, int idy, State cur);

    /////////Utility Print Function//////
    void printStates();
    void printStatesToFile(ofstream& out);
    void printCOL(); //cost of living
    void printPolicy();
    void printPolicyTofile(ofstream& out);
    void printCompPolicy(StatesMap& other);    
    void printCompPolicyToFile(StatesMap& other, ofstream& out);
};
#endif
