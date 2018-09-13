#include "StatesMap.h" 
using namespace std;


StatesMap::StatesMap(int x, int y, double CostOfLiving)
{
    maxX = x;
    maxY = y;
    Rs = CostOfLiving;
    initMap();
}

void StatesMap::initMap()
{
    states.resize(maxX, vector<State>(maxY, State(1, 1, 0, Rs)));
    
    for (int col = 0; col < maxX; ++col)
    {
        for (int row = 0; row < maxY; ++row)
        {
            states[col][row].reInit(col, row, 0, false, false, "", Rs);
        }
    }
}

double StatesMap::getStateCostOfLiving(int x, int y)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    int idx = x - 1;
    int idy = y - 1;
    
    if(states[idx][idy].wall)
    {
        cerr << "wall has no COL" << endl;
        exit(1);
    }
    
    if(states[idx][idy].terminal)
    {
        //for eterminal state col == utility
        return states[idx][idy].utility;
    }
    else
    {
        return states[idx][idy].costOfLiving;
    }
    
}

void StatesMap::setWall(int x, int y)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    int idx = x - 1;
    int idy = y - 1;
    states[idx][idy].wall = true;
}

void StatesMap::setRs(double r)
{
    Rs = r;
}

void StatesMap::setTerminal(int x, int y, double u)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    int idx = x - 1;
    int idy = y - 1;
    states[idx][idy].terminal = true;
    states[idx][idy].utility = u;
    states[idx][idy].costOfLiving = u;
}

void StatesMap::setUtility(int x, int y, double utility)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    int idx = x - 1;
    int idy = y - 1;
    states[idx][idy].utility = utility;
}

void StatesMap::setCostOfLiving(int x, int y, double col)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    int idx = x - 1;
    int idy = y - 1;
    states[idx][idy].costOfLiving = col;
}

void StatesMap::setPolicy(int x, int y, string pol)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    int idx = x - 1;
    int idy = y - 1;
    states[idx][idy].policy = pol;
}

string StatesMap::makePlicyStr()
{
    policyStr = "";
    for (int row = maxY - 1; row >= 0; --row)
    {
        for (int col = 0; col < maxX; ++col)
        {
            policyStr += states[col][row].policy;
        }
    }
    
    return policyStr;
}

double StatesMap::getUtility(int x, int y)
{
    
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    int idx = x - 1;
    int idy = y - 1;
    
    if (states[idx][idy].wall)
    {
        cerr << "wall has  no utility" << endl;
        exit(1);
    }
    
    return states[idx][idy].utility;
}

State StatesMap::getState(int x, int y)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    return states[x - 1][y - 1];
}

vector<State> StatesMap::getResultStates(int x, int y, Action act)
{
    if (x <= 0 || x > maxX || y <= 0 || y > maxY)
    {
        cerr << "invalid row or col" << endl;
        exit(1);
    }
    
    int idx = x - 1;
    int idy = y - 1;
    
    vector<State> result;
    State curState = states[idx][idy];
    
    //counter clock wise
    if (act == UP)
    {
        result.push_back(resultState(idx, idy + 1, curState));
        result.push_back(resultState(idx - 1, idy, curState));
        result.push_back(resultState(idx + 1, idy, curState));

    }
    else if (act == DOWN)
    {
        //counter clock wise
        result.push_back(resultState(idx, idy - 1, curState));
        result.push_back(resultState(idx + 1, idy, curState));
        result.push_back(resultState(idx - 1, idy, curState));
    }
    else if (act == LEFT)
    {
        result.push_back(resultState(idx - 1, idy, curState));
        result.push_back(resultState(idx, idy - 1, curState));
        result.push_back(resultState(idx, idy + 1, curState));
    }
    else if (act == RIGHT)
    {
        result.push_back(resultState(idx + 1, idy, curState));
        result.push_back(resultState(idx, idy + 1, curState));
        result.push_back(resultState(idx, idy - 1, curState));
    }
    else if (act == STAY)
    {
        result.push_back(curState);
        result.push_back(curState);
        result.push_back(curState);
    }
    
    return result;
}

double StatesMap::getResultStatesExpect(int x, int y, Action act,
                             double prob1, double prob2,
                             double prob3)
{
    
    vector<State> results = getResultStates(x, y, act);
    
    return results[0].utility * prob1 + results[1].utility * prob2 +
            results[2].utility * prob3;
}

State StatesMap::resultState(int idx, int idy, State cur)
{
    if (idx >= 0 && idx < maxX && idy >= 0 && idy < maxY
        && !states[idx][idy].wall)
    {
        return states[idx][idy];
    }
    
    return cur;
}

/////////Utility Print Function//////
void StatesMap::printStates()
{
    cout << "-----------states-----------\n";
    
    for (int row = maxY - 1; row >= 0; --row)
    {
        cout << row + 1;
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].wall)
            {
                cout << "    " << "xxxxxxxxxx";
            }
            else
            {
                cout << "    " << setprecision(8);
                cout << fixed << states[col][row].utility;
            }
        }
            cout << endl;
    }
    
    for (int i = 1; i <= maxX; ++i)
    {
        cout << "            " << i;
    }
    cout << endl;
}

void StatesMap::printStatesToFile(ofstream& out)
{
    out << "Utilities:" << endl;
    
    for (int row = maxY - 1; row >= 0; --row)
    {
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].wall)
            {
                out << "    " << "xxxxxxxxxx";
            }
            else
            {
                out << "    " << setprecision(8);
                out << fixed << states[col][row].utility;
            }
        }
        out << endl;
    }
    out << endl;
}

void StatesMap::printCOL()
{
    cout << "-----------Cost of Living-----------\n";
    
    for (int row = maxY - 1; row >= 0; --row)
    {
        cout << row + 1;
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].wall)
            {
                cout << "    " << "xxxxxxxxxx";
            }
            else
            {
                cout << "    " << setprecision(8) << fixed;
                cout << states[col][row].costOfLiving;
            }
        }
        cout << endl;
    }
    
    for (int i = 1; i <= maxX; ++i)
    {
        cout << "            " << i;
    }
    cout << endl;
}

void StatesMap::printPolicy()
{
    cout << "-----------policy-----------\n";
    
    for (int row = maxY - 1; row >= 0; --row)
    {
        cout << row + 1;
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].policy == "")
            {
                cout << "policy not set yet" << endl;
                exit(1);
            }
            
            cout << "  " << states[col][row].policy;
        }
        cout << endl;
    }
    
    cout << " ";
    for (int i = 1; i <= maxX; ++i)
    {
        cout << "  " << i;
    }
    cout << endl;
}

void StatesMap::printPolicyTofile(ofstream& out)
{
    out << "Optimal Policy:" << endl;

    for (int row = maxY - 1; row >= 0; --row)
    {
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].policy == "")
            {
                out << "policy not set yet" << endl;
                exit(1);
            }
            
            out << "  " << states[col][row].policy;
        }
        out << endl;
    }
    out << endl;
}

void StatesMap::printCompPolicy(StatesMap& other)
{    
    for (int row = maxY - 1; row >= 0; --row)
    {
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].policy == "")
            {
                cout << "policy not set yet" << endl;
                exit(1);
            }
            
            if (states[col][row].policy != other.states[col][row].policy)
                cout << "   " << states[col][row].policy << "*";
            else
                cout << "   " << states[col][row].policy;
        }
        cout << endl;
    }
    cout << endl;
}

void StatesMap::printCompPolicyToFile(StatesMap& other, ofstream& out)
{
    out << "Optimal Policy:" << endl;

    for (int row = maxY - 1; row >= 0; --row)
    {
        for (int col = 0; col < maxX; ++col)
        {
            if (states[col][row].policy == "")
            {
                out << "policy not set yet" << endl;
                exit(1);
            }
            
            if (states[col][row].policy != other.states[col][row].policy)
                out << "   " << states[col][row].policy << "*";
            else
                out << "   " << states[col][row].policy;
        }
        out << endl;
    }
    out << endl;
}
