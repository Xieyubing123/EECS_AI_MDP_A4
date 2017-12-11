#include<iostream>
#include<vector>
#include<map>
#include "problems.cpp"
using namespace std;



int main(void)
{
    cout << "\n**********Problem 1**********\n\n" << endl;
    //P1-output.txt
    std::ofstream outfileP1 ("P1-output.txt");

    doProblem1(outfileP1);
    
    outfileP1.close();
    cout << "\n**********Problem 2**********\n\n" << endl;
    
    double mean10 = 0;
    double firstRun10 = 0;
    double temp = 0;
    double std10 = 0;
    double exp10 = 0;
    double mean100 = 0;
    double std100 = 0;
    double exp100 = 0;
    double mean1000 = 0;
    double std1000 = 0;
    double exp1000 = 0;

    doProblem2(10, mean10, std10, exp10, firstRun10);
    cout << "\n" << endl;
    doProblem2(100, mean100, std100, exp100, temp);
    cout << "\n" << endl;
    doProblem2(1000, mean1000, std1000, exp1000, temp);
    
    std::ofstream outfileP2 ("P2-output.txt");
    
    outfileP2 << "Expected utility: " << exp10 << endl;
    outfileP2 << "First run: " << firstRun10 << endl;
    outfileP2 << "10-run average utility: " << mean10 << endl;
    outfileP2 << "10-run standard dev: " << std10 << endl;
    outfileP2 << "100-run average utility: " << mean100 << endl;
    outfileP2 << "100-run standard dev: " << std100 << endl;
    outfileP2 << "1000-run average utility: " << mean1000 << endl;
    outfileP2 << "1000-run standard dev: " << std1000 << endl;
    outfileP2.close();

    cout << "\n**********Problem 3**********\n\n" << endl;
    
    std::ofstream outP3 ("P3-output.txt");
    doProblem3(outP3);
    outP3.close();

    
	return 0;
}
