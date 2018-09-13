#ifndef STATE_H
#define STATE_H

#include <string>
using namespace std;

enum Action {UP, DOWN, LEFT, RIGHT, STAY};

class State
{
public:
    bool terminal;
    bool wall;
    int idx;
    int idy;
    double utility;
    double costOfLiving;
    string policy;
    
    State();
    State(int col, int row, double utilityVal, double col_R);
    void reInit (int col, int row, double utilityVal,
                 bool w, bool t, string pol, double col_R);
    double getU();
    void setU(double val);
    void setPolicy(string pol);

};
#endif
