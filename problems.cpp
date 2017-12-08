#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include "helper.cpp"
using namespace std;


void doProblem1()
{
    double minErr = 0.0000001;
    double discountFactor = 1;
    double Rs = -0.040000;
    int col = 4;
    int row = 3;
    map<string, int> policyMap;
    vector<double> RsList;
    map<string, int> policyCount;
    map<double, string> RsPolicyMap;
    
    binarySearch(-10.00000000, 0 - 0.0001, col, row, minErr, discountFactor,
                 RsList, policyCount, RsPolicyMap);
    
    cout << RsList.size() << endl;
    sort(RsList.begin(), RsList.end());
    //cout << "Threshold value: " << 0 << endl;
    
    StatesMap lastStates = dynamicProgrammingMDPsolver(RsList[RsList.size() - 1], col, row, minErr, discountFactor);
    
    for (int i = (int)RsList.size() - 1; i >= 0; --i)
    {
        //cout << "---------RS--------" << endl;
        cout << "Threshold value: " << RsList[i] << endl;
        StatesMap states = dynamicProgrammingMDPsolver(RsList[i], col, row, minErr, discountFactor);
        //states.printStates();
        states.printCompPolicy(lastStates);
        lastStates = states;
    }
}

void doProblem2()
{
    map<double, int> rewardShowUpTime;
    map<int, double> RevRewardShowUpTime;
    //vector<int>
    double minErr = 0.0000001;
    double discountFactor = 1;
    double Rs = -0.040000;
    int col = 4;
    int row = 3;
    StatesMap States = dynamicProgrammingMDPsolver(Rs, col, row, minErr, discountFactor);
    States.printStates();
    

    ofstream outfile;
    outfile.open("/Users/yubingxie/PycharmProjects/dropHistorgram/data.txt");
    
    for (int i = 0; i < 100; ++i)
    {
        outfile << simulateRun(States, 4, 1, Rs) << endl;
        rewardShowUpTime[simulateRun(States, 4, 1, Rs)]++;
    }
    
    for (auto i = rewardShowUpTime.begin(); i != rewardShowUpTime.end(); ++i)
    {
        cout << i->first << " " << i->second << endl;
        RevRewardShowUpTime[i->second] = i->first;
    }
    //simulateRun
    
    outfile.close();
}

void doProblem3()
{
    double minErr = 0.0000001;
    double discountFactor = 1;
    double Rs = -0.04000;
    int col = 3;
    int row = 3;
    map<string, int> policyMap;
    vector<double> RsList;
    map<string, int> policyCount;
    map<double, string> RsPolicyMap;
    
    StatesMap states = dynamicProgrammingMDPsolver(Rs, col, row, minErr, discountFactor);

}

