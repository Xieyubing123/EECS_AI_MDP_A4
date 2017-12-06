#include<iostream>
#include<vector>
#include<map>
#include "helper.cpp"
using namespace std;



int main(void)
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
    
    //StatesMap states =  dynamicProgrammingMDPsolver(-1.65, col, row, minErr, discountFactor);
    //states.printStates();
    //states.printPolicy();
    binarySearch(-10.00000000, 0 - minErr, col, row, minErr, discountFactor,
                 RsList, policyCount, RsPolicyMap);
    
    cout << RsList.size() << endl;
    sort(RsList.begin(), RsList.end());
    cout << "Threshold value: " << 0 << endl;
    
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
    
	return 0;
}
