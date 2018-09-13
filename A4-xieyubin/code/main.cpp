#include "problems.h"

using namespace std;

int main(void)
{
    cout << "\n**********Problem 1**********\n" << endl;

    std::ofstream outfileP1 ("../generated/P1-output.txt");
    doProblem1(outfileP1);
    outfileP1.close();
    cout << "P1 done result folder: ../generated/\n\n" << endl;

    cout << "\n**********Problem 2**********\n" << endl;
    
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
    
    const int RUN_10 = 10;
    const int RUN_100 = 100;
    const int RUN_1000 = 1000;

    doProblem2(RUN_10, mean10, std10, exp10, firstRun10);
    doProblem2(RUN_100, mean100, std100, exp100, temp);
    doProblem2(RUN_1000, mean1000, std1000, exp1000, temp);

    std::ofstream outfileP2 ("../generated/P2-output.txt");
    
    outfileP2 << "Expected utility: " << exp10 << endl;
    outfileP2 << "First run: " << firstRun10 << endl;
    outfileP2 << "10-run average utility: " << mean10 << endl;
    outfileP2 << "10-run standard dev: " << std10 << endl;
    outfileP2 << "100-run average utility: " << mean100 << endl;
    outfileP2 << "100-run standard dev: " << std100 << endl;
    outfileP2 << "1000-run average utility: " << mean1000 << endl;
    outfileP2 << "1000-run standard dev: " << std1000 << endl;
    outfileP2.close();
    cout << "P2 done result folder: ../generated/\n\n" << endl;
    
    cout << "\n**********Problem 3**********\n" << endl;
    
    std::ofstream outP3 ("../generated/P3-output.txt");
    doProblem3(outP3);
    outP3.close();
    cout << "P3 done result folder: ../generated/\n\n" << endl;

    
	return 0;
}
