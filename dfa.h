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

#define PIC 	std::pair<int, char>
#define PIPIC	std::pair<int, std::vector<PIC> >

class DFA
{
public:
	DFA();
	~DFA();

public:
	// load DFA 载入DFA
	void load(const char *path);
	void save(const char *path);
	void travel(std::string str, int curState, int maxDepth);

	void showDFA();
	void addNewState(int newState);
	void addTransition(int a, int b, char ch);

private:
	bool isAccepted(int curState);

private:
	std::string alphabets_;

	std::vector<PIPIC> dfa_;
	std::map<int, int> node2index_;
	int numOfTransitions;
	
	int startState_;
	std::map<int, bool> acceptedStates_;

	// std::map<int, int> index2node_;
};

#endif 	// _DFA_H