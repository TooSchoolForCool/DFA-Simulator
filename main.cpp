#include <iostream>

#include "dfa.h"

using namespace std;

string makeManu()
{
	string ret = "";
	string stars(30, '*');


	ret += stars + '\n';
	ret += "\tManu\n";
	ret += stars + '\n';

	ret += "1. print all accepted string.\n";
	ret += "2. check string.\n";
	ret += "0. quit.\n";
	ret += "please enter your choice: ";

	return ret;
}

int main()
{
	DFA dfa;

	dfa.load("test_dfa_1.dfa");

	dfa.showDFA();

	cout << makeManu() << endl;

	dfa.save("dfa_out_1.dfa");

	return 0;
}