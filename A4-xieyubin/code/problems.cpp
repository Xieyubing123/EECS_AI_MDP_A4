#include "problems.h"
using namespace std;

void doProblem1(ofstream& out)
{
    double minErr = 0.00000010000;
    double discountFactor = 1;
    const int PROBLEM_1 = 1;
    int col = 4;
    int row = 3;
    map<string, int> policyMap;
    vector<double> RsList;
    map<string, int> policyCount;
    map<double, string> RsPolicyMap;
    
    binarySearch(-2.00000000, 0 - 0.00010000, col, row, minErr,
                discountFactor, RsList, policyCount, RsPolicyMap);
    std::sort(RsList.begin(), RsList.end());

    StatesMap lastStates = dpMDPsolver(RsList[RsList.size() - 1],
                                       col, row, minErr, discountFactor,
                                       PROBLEM_1);
    
    for (int i = (int)RsList.size() - 1; i >= 0; --i)
    {
        if (i == ((int)RsList.size() - 1))
            out << "Up Bound(approximate 0): " << RsList[i] << endl;
        else
            out << "Threshold value: " << RsList[i] << endl;
        
        StatesMap states = dpMDPsolver(RsList[i], col, row,
                                                 minErr, discountFactor, 1);
        states.printCompPolicyToFile(lastStates, out);
        lastStates = states;
    }
}

void doProblem2(int run, double & Resultmean, double& Resultstd,
                         double & expectedVal, double& firstRun)
{
    vector<double> vals;

    double minErr = 0.0000001;
    double discountFactor = 1;
    double Rs = -0.040000;
    const int PROBLEM_2 = 2;
    int col = 4;
    int row = 3;
    StatesMap States = dpMDPsolver(Rs, col, row, minErr,
                                   discountFactor, PROBLEM_2);

    double sum = 0;
    double mean = 0;
    int size = 0;

    std::ofstream outfile ("../generated/P2-data-" + to_string(run) + ".txt");
    //outfile.open("/Users/yubingxie/PycharmProjects/drawHistorgram/data.txt");
    
    for (int i = 0; i < run; ++i)
    {
        double temp = simulateRun(States, 4, 1, Rs);
        vals.push_back(temp);
        outfile << temp << endl;
        if (i == 0)
            firstRun = temp;
        
        sum += temp;
        size++;
    }
    
    outfile.close();
    
    mean = sum/size;
    double std = 0;
    for (int i = 0; i < size; ++i)
        std += (vals[i] - mean)*(vals[i] - mean);
    
    std = std / size;
    std = sqrt(std);
    
    Resultmean = mean;
    Resultstd = std;
    expectedVal = States.getUtility(4, 1);
}

void doProblem3(ofstream& out)
{
    double minErr = 0.00001000;
    double Rs = -1.00000;
    const int PROBLEM_3 = 3;
    int col = 3;
    int row = 3;
    map<string, int> policyMap;
    vector<double> DisList;
    map<string, int> policyCount;
    map<double, string> RsPolicyMap;
    
    gammaBinarySearch(0, 1 - 0.0010, col, row, minErr, DisList,
                      Rs, policyCount, RsPolicyMap);
    std::sort(DisList.begin(), DisList.end());
    
    vector<double> LowerBound;
    map<string, int> LowerBoundpolicyCount;
    map<double, string> LowerBoundRsPolicyMap;
    gammaBinarySearch(0, 0.001, col, row, minErr, LowerBound,
                      Rs, LowerBoundpolicyCount, LowerBoundRsPolicyMap);

    StatesMap lastStates = dpMDPsolver(Rs, col, row, minErr,
                                       LowerBound[0], PROBLEM_3);
    out << "Lower bound: (approximate 0) " << LowerBound[0] << endl;
    lastStates.printPolicyTofile(out);
    lastStates.printStatesToFile(out);
    
    for (int i = 0; i <= (int)DisList.size() - 1; ++i)
    {
        if (i == ((int)DisList.size() - 1))
            out << "Upper bound: (approximate 1) " << DisList[i] << endl;
                else
            out << "Threshold value: " << DisList[i] << endl;
        
        StatesMap states = dpMDPsolver(Rs, col, row, minErr,
                                       DisList[i], PROBLEM_3);
        states.printPolicyTofile(out);
        states.printStatesToFile(out);
        lastStates = states;
    }
}

