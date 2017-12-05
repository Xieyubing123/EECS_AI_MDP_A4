#include<iostream>
#include<vector>
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
    
    State()
    {
        x = 1;
        y = 1;
        utility = 0;
        wall = false;
        terminal = false;
    }
    
	State(int col, int row, double utilityVal)
	{
		x = col;
		y = row;
		utility = utilityVal;
        wall = false;
        terminal = false;

	}
    
    void reInit (int col, int row, double utilityVal, bool w, bool t)
    {
        x = col;
        y = row;
        utility = utilityVal;
        wall = w;
        terminal = t;
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

class StatesMap
{
public:
    int maxX;
    int maxY;
    
    vector<vector<State>> states;
    
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
                states[col][row].reInit(col, row, 0, false, false);
            }
        }
    }
    
    void setWall(int x, int y)
    {
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].wall = true;
    }
    
    void setTerminal(int x, int y, double u)
    {
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].terminal = true;
        states[idx][idy].utility = u;
    }
    
    void updateStateUtility(int x, int y, double utility)
    {
        int idx = x - 1;
        int idy = y - 1;
        states[idx][idy].utility = utility;
    }
    
    void printStates()
    {
        
        
        for (int row = maxY - 1; row >= 0; --row)
        {
            cout << row + 1;
            for (int col = 0; col < maxX; ++col)
            {
                if (states[col][row].wall)
                {
                    cout << "    " << "x";
                }
                else
                {
                    cout << "    " << states[col][row].utility;
                }
            }
                cout << endl;
        }
        
        cout << " ";
        for (int i = 1; i <= maxX; ++i)
        {
            cout << "    " << i;
        }
        cout << endl;
    }
    
    double getUtility(int x, int y)
    {
        
        int idx = x - 1;
        int idy = y - 1;
        
        if (states[idx][idy].wall)
        {
            cout << "wall has  no utility" << endl;
            exit(1);
        }
        
        return states[idx][idy].utility;
    }
    
    vector<State> getResultStates(int x, int y, Action act)
    {
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
