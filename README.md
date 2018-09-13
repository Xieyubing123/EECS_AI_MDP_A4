# MDP in 4 × 3 fully observable environment
## This is just a repo that to store my past project after it was finished, not the actually working repo

## Markov decision process (MDP)

Implement methods to solve a Markov Decision Process (MDP) for an optimal policy, described in the textbook 
< Artificial Intelligence- A Modern Approach >. In the textbook, Markov Decision Processes are defined in Section 
17.1, and Section 17.2 describes the Value Iteration approach to solving an MDP. Section 17.3 describes the
Policy Iteration approach, which is related to this project. Tasks for this project: 
* Explore the difference between expected reward (average over many runs) and actual reward (on a particular run), given that the result of an action is uncertain.
* Explore the impact of “discount rate” γ

### Figure 17.2:
![alt text](https://github.com/Xieyubing123/EECS492_A4/blob/master/stateExample_17.2.png)

### Figure 17.3:
![alt text](https://github.com/Xieyubing123/EECS492_A4/blob/master/stateExample_17.3.png)

In figure 17.3:
Expected utility for going left 0.655 * 0. 8 + 0.611 * 0. 1 + 0. 660 * 0.1 = 0.6511
Expected utility for going up 0.660 * 0.8 + 0.655 * 0.1 + 0.388 * 0.1 = 0. 6323
Since the Expected value of going left (go to state (2, 1)) is higher than going up, this is why the optimal policy for R(s) = -0.04 say to move left from the state(3, 1).

### output data (may different when run in different environment, this is data from cean environment):

* Expected utility: 0.387925
* First run: 0.4
* 10-run average utility: 0.632 
* 10-run standard dev: 0.118389 
* 100-run average utility: 0.3064 
* 100-run standard dev: 0.672719 
* 1000-run average utility: 0.371 
* 1000-run standard dev: 0.601363

the expected value of initial state is 0.387925, although the average(mean) change when we have more
run, we can still notice that as we have more run, the average utility is getting closer to the expected utility.
For example, in 10 run, since the randomness, the means are 0.632 and standard deviation is 0.118389, which is
quite far from the expected utility, however, when we have 100 run, the means change to 0.3064, and standard deviation become 0.672719. We can see that the means is getting closer to 0.387. When we have 1000 run, the means is 0.371, which is even more closer to the expected utility. Also, the standard deviation change is also become smaller, which means the standard deviation is also start to converge to some value.

## compile:
```
g++ -c main.cpp problems.cpp helper.cpp StatesMap.cpp  State.cpp --std=c++11
g++ --std=c++11 main.o problems.o helper.o StatesMap.o State.o

```
