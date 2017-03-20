#ifndef _DFA_H
#define _DFA_H

// C++ library
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

// C library
#include <stdio.h>
#include <stdlib.h>

class DFA
{
public:
	DFA();
	~DFA();

public:
	// load DFA 载入DFA
	void load(char *path);
	void save(char *path);

	void showDFA();
private:

};

#endif 	// _DFA_H