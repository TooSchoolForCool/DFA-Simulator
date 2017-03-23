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
	string path;
	DFA dfa;

	cout << "1. Enter by hand.\n";
	cout << "2. Read from file.\n";
	cout << "Please enter your choice: ";
	cin >> ret;

	if(ret == 2)
	{
		cout << "Please Enter the file path:\n";
		cin >> path;
		dfa.load(path);
	}
	else if(ret == 1)
	{
		int tmp, n;
		int a, b;
		string str;
		vector<int> vec;

		cout << "Alphabets: ";
		cin >> str;
		dfa.setAlphabets(str);

		cout << "Number of states: ";
		cin >> n;
		for(int i = 0; i < n; i++)
		{
			cin >> tmp;
			dfa.addNewState(tmp);
		}

		cout << "Start State: ";
		cin >> n;
		dfa.setStartState(n);

		cout << "Number of final state: ";
		cin >> n;
		for(int i = 0; i < n; i++)
		{
			cin >> tmp;
			vec.push_back(tmp);
		}
		dfa.setAcceptedStates(vec);

		cout << "Number of transition: ";
		cin >> n;
		for(int i = 0; i < n; i++)
		{
			cin >> a >> b >> str;
			dfa.addTransition(a, b, str);
		}

		dfa.checkDFATransitions();
	}
	else
	{
		return 0;
	}

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