#ifndef _DFA_H
#define _DFA_H

// C++ library
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

// C library
#include <stdio.h>
#include <stdlib.h>

#define PIS 	std::pair<int, std::string>
#define PIPIS	std::pair<int, std::vector<PIS> >

class DFA
{
public:
	DFA();
	~DFA();

public:
	// load DFA 载入DFA
	void load(const char *path);
	void save(const char *path);
	void travel(int maxDepth);
	bool checkExpression(const std::string, bool showProcess=false);

	void showDFA();
	void addNewState(int newState);
	void addTransition(int a, int b, std::string str);

private:
	bool _isAccepted(int curState);
	void _getNextTransitions(int curState, std::vector<PIS> &nextStates);
	int _getNextState(int curState, char alphabet);
	void _travel(std::string str, int curState, int maxDepth);

private:
	std::string alphabets_;

	std::vector<PIPIS> dfa_;
	std::map<int, int> node2index_;
	int numOfTransitions_;
	
	int startState_;
	std::map<int, bool> acceptedStates_;
};

#endif 	// _DFA_H