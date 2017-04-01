# DFA Simulator

> This is a simple DFA simulator.
> ***
> Wirte down your DFA in a .dfa file, and load it into the program. Then the program will generate the DFA based on the description in the .dfa file. 
> ***
> After loading your DFA configuration, this program will check whether your DFA is really a DFA (correctness and completeness).
> ***
> this program can tell you whether a expression(or a string) could be accepted by this DFA. What's more, this program can generate all accepted expressions automatically, once you determined the maximum length of the expression.

## How to Compile this project

Make the target executable file:
```shell
make
```

Make the target executable file and RUN it
```shell
make run
```

Clean the target executable file and clean all the object file (.obj)
```shell
make clean
```

## The format of .dfa file

ab			// line #1: the alphabets set
4			// line #2: the number of states
0 1 2 3		// line #3: the identifier of each state(number only), seperated by a space
0			// line #4: the start state
1			// line #5: the number of accept states
3			// line #6: the identifier of accept state, seperated by a space
8			// line #7: the number of state transitions
0 1 a  		// from state_0 to state_1 when read in a
0 2 b
1 3 a
1 2 b
2 1 a
2 3 b
3 3 a
3 3 b
