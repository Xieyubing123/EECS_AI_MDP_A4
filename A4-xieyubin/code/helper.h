#ifndef HELPER_H
#define HELPER_H

#include <cmath>        // std::abs
#include "StatesMap.h"
#include "State.h"

void initStatesUtility(StatesMap & states);

void initP3StatesUtility(StatesMap & states, double r);

string actToStringPolicy(Action act);

double findBestExp(StatesMap &states, int col, int row, Action &bestAct);

void valueIteration(StatesMap &states, double Rs, double discountFactor,
                    double miniErr, int col, int row);

void findOptimalPolicy(StatesMap &states, int col, int row);

StatesMap dpMDPsolver(double Rs,int col,
                                 int row, double minErr,
                                 double discountFactor, int problemNum);

void binarySearch(double minRs, double maxRs, int col,
                  int row, double minErr,
                  double discountFactor,
                  vector<double> &RsList,
                  map<string, int>& policyCount,
                  map<double, string>& RsPolicyMap);

void gammaBinarySearch(double minDis, double maxDis, int col,
                  int row, double minErr,
                  vector<double> &DisList,
                       double Rs,
                  map<string, int>& policyCount,
                  map<double, string>& RsPolicyMap);

//////////////////////////////////////////////////////////////////////////////
/////////////////p2/////////////////

Action randomAct(Action act);

double simulateRun(StatesMap& states, int initX, int initY, double Rs);
#endif
