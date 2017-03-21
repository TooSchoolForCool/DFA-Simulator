#include <iostream>

#include "dfa.h"

using namespace std;


string manu()
{
	string ret = "";
	string stars(30, '*');

	ret += stars + '\n';
	ret += "\tManu\n";
	ret += stars + '\n';

	ret += "1. print all accepted string.\n";
	ret += "2. check string.\n";
	ret += "3. save DFA.\n";
	ret += "0. quit.\n";
	ret += "please enter your choice: ";

	return ret;
}

void printAllACStr(DFA &dfa)
{
	int maxLen;

	cout << "Please enter the maximum length of stings: ";
	cin >> maxLen;

	dfa.travel(maxLen);
}

void checkExp(DFA &dfa)
{
	string exp;

	cout << "Please enter the expression below:" << endl;
	cin >> exp;

	cout << (dfa.checkExpression(exp) ? "Accepted" : "Refused") << endl;
}

void saveDFA(DFA &dfa)
{
	string path;

	cout << "Please enter the save path below: \n";
	cin >> path;

	dfa.save(path);
}

void (*pfunc[])(DFA &) = {&printAllACStr, &checkExp, &saveDFA};

int main()
{
	int ret;
	DFA dfa;

	dfa.load("test_dfa_1.dfa");

	dfa.showDFA();

	while(1)
	{
		cout << manu();
		cin >> ret;

		if(ret == 0)
			break;
		else if(ret >= 1 && ret <= 3)
			pfunc[ret - 1](dfa);
		else
			cout << "No such option..." << endl;
	}

	return 0;
}