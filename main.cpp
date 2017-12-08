#include<iostream>
#include<vector>
#include<map>
#include "problems.cpp"
using namespace std;



int main(void)
{
    cout << "\n**********Problem 1**********\n\n" << endl;
    doProblem1();
    
    cout << "\n**********Problem 2**********\n\n" << endl;
    doProblem2(10);
    cout << "\n" << endl;
    doProblem2(100);
    cout << "\n" << endl;
    doProblem2(1000);

    cout << "\n**********Problem 3**********\n\n" << endl;
    doProblem3();

    
	return 0;
}
