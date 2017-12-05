#include<iostream>
#include<vector>
#include<map>
#include "helper.cpp"
using namespace std;



int main(void)
{
    double minErr = 0.0000001;
    double discountFactor = 1;
    double Rs = -0.04;
    int col = 4;
    int row = 3;
    map<string, int> policyMap;
    vector<double> RsList;
    map<string, int> policyCount;
    map<double, string> RsPolicyMap;
    
    //dynamicProgrammingMDPsolver(Rs, col, row, minErr, discountFactor);
    binarySearch(-2.0000000, 0.0000000, col, row, minErr, discountFactor,
                 RsList, policyCount, RsPolicyMap);
    
    cout << RsList.size() << endl;
    sort(RsList.begin(), RsList.end());
    for (int i = 0; i < RsList.size(); ++i)
    {
        cout << "---------RS--------" << endl;
        cout << "Rs: " << RsList[i] << endl;
        dynamicProgrammingMDPsolver(RsList[i], col, row, minErr, discountFactor).printPolicy();
        
    }
    
    /*
     void binarySearch(double minRs, double maxRs, int col,
     int row, double minErr,
     double discountFactor,
     vector<double> &RsList,
     map<string, int>& policyCount,
     map<double, string>& RsPolicyMap)
     */
	return 0;
}
