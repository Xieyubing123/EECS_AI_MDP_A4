#include<iostream>
#include<vector>
#include "helper.cpp"
using namespace std;



int main(void)
{
    StatesMap states = StatesMap(4, 3);
    states.setWall(2, 2);
    states.setTerminal(4, 2, -1);
    states.setTerminal(4, 3, 1);
    states.printStates();
    
    


	return 0;
}
