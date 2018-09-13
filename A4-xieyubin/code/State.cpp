#include "State.h" 
using namespace std;


State::State()
{
    idx = 1;
    idy = 1;
    utility = 0;
    wall = false;
    terminal = false;
    policy = "";
}

State::State(int col, int row, double utilityVal, double col_R)
{
	idx = col;
	idy = row;
	utility = utilityVal;
    wall = false;
    terminal = false;
    policy = "";
    costOfLiving = col_R;
}

void State::reInit (int col, int row, double utilityVal,
             bool w, bool t, string pol, double col_R)
{
    idx = col;
    idy = row;
    utility = utilityVal;
    wall = w;
    terminal = t;
    policy = pol;
    costOfLiving = col_R;
}

void State::setU(double val)
{
	utility = val;
}

double State::getU()
{
	return utility;
}

void State::setPolicy(string pol)
{
    policy = pol;
}
