#include<iostream>
#include<vector>
#include <iomanip>
#include<map>

using namespace std;
enum Action {UP, DOWN, LEFT, RIGHT, STAY};

class State
{
public:
    bool terminal;
    bool wall;

	int x;
	int y;
	double utility;
    string policy;
    
    State()
    {
        x = 1;
        y = 1;
        utility = 0;
        wall = false;
        terminal = false;
        policy = "";
    }
    
	State(int col, int row, double utilityVal)
	{
		x = col;
		y = row;
		utility = utilityVal;
        wall = false;
        terminal = false;
        policy = "";

	}
    
    void reInit (int col, int row, double utilityVal,
                 bool w, bool t, string pol)
    {
        x = col;
        y = row;
        utility = utilityVal;
        wall = w;
        terminal = t;
        policy = pol;
    }

	void setU(double val)
	{
		utility = val;
	}

	double getU()
	{
		return utility;
	}
    
    void setPolicy(string pol)
    {
        policy = pol;
    }

};

class StatesMap
{
public:
    int maxX;
    int maxY;
    double Rs;
    
    vector<vector<State>> states;
    vector<string> policyVec;
    string policyStr;
    
    vector<State> StateVec;
    StatesMap(int x, int y)
    {
        maxX = x;
        maxY = y;
        initMap();
    }
    
    void initMap()
    {
        //matrix.resize( row_count , vector<int>( column_count , initialization_value ) );

        states.resize(maxX, vector<State>(maxY, State(1, 1, 0)));
        
        for (int col = 0; col < maxX; ++col)
        {
            for (int row = 0; row < maxY; ++row)
            {
                states[col][row].reInit(col, row, 0, false, false, "");
            }
        }
    }
    
    void setWall(int x, int y)
    {
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
            exit(1);
        }
        
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].wall = true;
    }
    
    void setRs(double r)
    {
        Rs = r;
    }
    
    void setTerminal(int x, int y, double u)
    {
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
            exit(1);
        }
        
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].terminal = true;
        states[idx][idy].utility = u;
    }
    
    void setUtility(int x, int y, double utility)
    {
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
            exit(1);
        }
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].utility = utility;
    }
    void setPolicy(int x, int y, string pol)
    {
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
            exit(1);
        }
        
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].policy = pol;
    }
    
    void printStates()
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
                    cout << "    " << setprecision(8) << fixed << states[col][row].utility;
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
    
    
    string makePlicyStr()
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
    
    void printPolicy()
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
    
    double getUtility(int x, int y)
    {
        
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
            exit(1);
        }
        
        int idx = x - 1;
        int idy = y - 1;
        
        if (states[idx][idy].wall)
        {
            cout << "wall has  no utility" << endl;
            exit(1);
        }
        
        return states[idx][idy].utility;
    }
    
    State getState(int x, int y)
    {
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
            exit(1);
        }
        
        return states[x - 1][y - 1];
    }
    vector<State> getResultStates(int x, int y, Action act)
    {
        if (x <= 0 || x > maxX || y <= 0 || y > maxY)
        {
            cout << "invalid row or col" << endl;
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
    
    double getResultStatesExpect(int x, int y, Action act,
                                 double prob1, double prob2,
                                 double prob3)
    {
        
        vector<State> results = getResultStates(x, y, act);
        
        return results[0].utility * prob1 + results[1].utility * prob2 +
                results[2].utility * prob3;
    }
    
    State resultState(int idx, int idy, State cur)
    {
        if (idx >= 0 && idx < maxX && idy >= 0 && idy < maxY
            && !states[idx][idy].wall)
        {
            return states[idx][idy];
        }
        
        return cur;
    }
};
