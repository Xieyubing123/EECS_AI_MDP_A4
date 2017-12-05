#include<iostream>
#include<vector>

using namespace std;

void VSstopFunc()
{
	int a = 0;
	cin >> a;
}

class State
{
public:
	int x;
	int y;
	double utility;

	State(int col, int row, double utilityVal)
	{
		x = col;
		y = row;
		utility = utilityVal;
	}

	void setU(double val)
	{
		utility = val;
	}

	double getU()
	{
		return utility;
	}

};

int main(void)
{

	//map of state (x, y) -->U
	cout << "asd" << endl;
	//1 value iteration to build the map with Utility
	//2 given the R(s) and y, calculate the policy


	return 0;
}