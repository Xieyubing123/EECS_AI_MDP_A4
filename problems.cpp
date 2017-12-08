#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include "helper.cpp"
#include <math.h>       /* sqrt */
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
    
    binarySearch(-2.00000000, 0 - 0.0001, col, row, minErr, discountFactor,
                 RsList, policyCount, RsPolicyMap);
    
    //cout << RsList.size() << endl;
    std::sort(RsList.begin(), RsList.end());
    //cout << "Threshold value: " << 0 << endl;
    
    StatesMap lastStates = dynamicProgrammingMDPsolver(RsList[RsList.size() - 1], col, row, minErr, discountFactor, 1);
    
    for (int i = (int)RsList.size() - 1; i >= 0; --i)
    {
        //cout << "---------RS--------" << endl;
        if (i == ((int)RsList.size() - 1))
        {
            cout << "Up Bound(approximate 0): " << RsList[i] << endl;
        }
        else
        {
            cout << "Threshold value: " << RsList[i] << endl;
        }
        
        StatesMap states = dynamicProgrammingMDPsolver(RsList[i], col, row, minErr, discountFactor, 1);
        //states.printStates();
        states.printCompPolicy(lastStates);
        lastStates = states;
    }
}

void doProblem2(int run)
{
    map<double, int> rewardShowUpTime;
    map<int, double> RevRewardShowUpTime;
    vector<double> vals;
    //vector<int>
    double minErr = 0.0000001;
    double discountFactor = 1;
    double Rs = -0.040000;
    int col = 4;
    int row = 3;
    StatesMap States = dynamicProgrammingMDPsolver(Rs, col, row, minErr, discountFactor, 2);
    States.printStates();
    States.printPolicy();

    double sum = 0;
    double mean = 0;
    int size = 0;
    ofstream outfile;
    outfile.open("/Users/yubingxie/PycharmProjects/dropHistorgram/data.txt");
    
    cout << "\n values:" << endl;
    for (int i = 0; i < run; ++i)
    {
        double temp = simulateRun(States, 4, 1, Rs);
        vals.push_back(temp);
        outfile << temp << endl;
        sum += temp;
        size++;
        //cout << temp << endl;
        rewardShowUpTime[temp]++;
    }
    
    cout << "reward:     count:" << endl;
    for (auto i = rewardShowUpTime.begin(); i != rewardShowUpTime.end(); ++i)
    {
        cout << i->first << "    " << i->second << endl;
        RevRewardShowUpTime[i->second] = i->first;
    }
    //simulateRun
    outfile.close();

    mean = sum/size;
    cout << "mean of " << size <<  " run : " <<  mean << endl;
    
    double std = 0;
    for (int i = 0; i < size; ++i)
    {
        std += (vals[i] - mean)*(vals[i] - mean);
    }
    std = std / size;
    std = sqrt(std);
    cout << "standard deviation of " << size <<  " run : " <<  std << endl;

}

void doProblem3()
{
    double minErr = 0.0000001000;
    double discountFactor = 0.99;
    double Rs = -1.00000;
    int col = 3;
    int row = 3;
    map<string, int> policyMap;
    vector<double> DisList;
    map<string, int> policyCount;
    map<double, string> RsPolicyMap;
    
    gammaBinarySearch(0, 1 - 0.001000, col, row, minErr, DisList, Rs, policyCount, RsPolicyMap);

    
    //cout << DisList.size() << endl;
    std::sort(DisList.begin(), DisList.end());
    //cout << "Threshold value: " << 0 << endl;
    
    StatesMap lastStates = dynamicProgrammingMDPsolver(Rs, col, row, minErr, DisList[DisList.size() - 1], 3);
    
    for (int i = (int)DisList.size() - 1; i >= 0; --i)
    {
        //cout << "---------RS--------" << endl;
        if (i == ((int)DisList.size() - 1))
        {
            cout << "Upper bound: (approximate 1) " << DisList[i] << endl;
        }
        else
        {
            cout << "Threshold value: " << DisList[i] << endl;
        }
        
        StatesMap states = dynamicProgrammingMDPsolver(Rs, col, row, minErr, DisList[i], 3);
        //states.printStates();
        states.printCompPolicy(lastStates);
        lastStates = states;
    }
}

