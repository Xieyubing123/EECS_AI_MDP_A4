#include "problems.h"
#include "helper.h"
#include "StatesMap.h"
#include "State.h"

using namespace std;

int main(void)
{
    cout << "\n**********Problem 1**********" << endl;

    std::ofstream outfileP1 ("../generated/P1-output.txt");
    doProblem1(outfileP1);
    outfileP1.close();
    cout << "\nProblem 1 done, result in ../generated/P1-output.txt\n\n" << endl;
    
    cout << "\n**********Problem 2**********" << endl;
    
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
    cout << "\nProblem 2 done\n\n" << endl;
    
    cout << "\n**********Problem 3**********\n\n" << endl;
    
    std::ofstream outP3 ("../generated/P3-output.txt");
    doProblem3(outP3);
    outP3.close();
    cout << "\nProblem 3 done, result in ../generated/P3-output.txt\n\n" << endl;

    
	return 0;
}
