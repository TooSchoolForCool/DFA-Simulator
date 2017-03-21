#include "dfa.h"

using namespace std;

DFA::DFA()
{
	numOfTransitions = 0;
}

DFA::~DFA()
{
	// ...
}

void DFA::load(const char *path)
{
	ifstream in(path);
	int n, tmp, a, b;
	char ch;

	if( !in.is_open() )
	{
		cerr << "Cannot open file: " << path << endl;
		return;
	}

	// read alphabets
	in >> alphabets_;

	// read in number of states
	in >> n;
	// read in each state
	for(int i = 0; i < n; i++)
	{
		in >> tmp;
		addNewState(tmp);
	}

	// read in start state
	in >> startState_;

	// read in number of accepted state
	in >> n;
	// read in each accepted state
	for(int i = 0; i < n; i++)
	{
		in >> tmp;
		acceptedStates_[tmp] = true;
	}

	// read in number transitions
	in >> n;
	// read in each transition
	for(int i = 0; i < n; i++)
	{
		in >> a >> b >> ch;
		addTransition(a, b, ch);
	}

	in.close();
}

void DFA::save(const char *path)
{
	ofstream out(path);

	// write in alphabets
	out << alphabets_ << endl;
	
	// write in number of states
	out << dfa_.size() << endl;

	// write in state number
	for(int i = 0; i < dfa_.size(); i++)
	{
		out << dfa_[i].first << " ";
	}
	out << endl;

	// write in start state
	out << startState_ << endl;

	// write in number of accepted states
	out << acceptedStates_.size() << endl;

	// write in accepted state number
	for(map<int, bool>::iterator iter = acceptedStates_.begin(); 
		iter != acceptedStates_.end(); iter++)
	{
		out << iter->first << " ";
	}
	out << endl;

	// write in number of transitions
	out << numOfTransitions << endl;
	// write in each transition
	for(int i = 0; i < dfa_.size(); i++)
	{	
		int curState = dfa_[i].first;
		const vector<PIC> &vec = dfa_[i].second;

		for(int j = 0; j < vec.size(); j++)
		{
			out << curState << " " << vec[j].first << " " << vec[j].second << endl;
		}
	}

	out.close();
}

void DFA::travel(string str, int curState, int maxDepth)
{
	// if(str.length() == maxDepth)
	// {

	// }
}

void DFA::showDFA()
{
	string stars(40, '*');

	cout << stars << endl;
	cout << "\tBrief DFA Description" << endl;
	cout << stars << endl;

	cout << "* Alphabests: " << alphabets_ << endl;

	cout << "* Start State: " << startState_ << endl;

	cout << "* Accepted States: ";
	for(map<int, bool>::iterator iter = acceptedStates_.begin(); 
		iter != acceptedStates_.end(); iter++)
	{
		cout << iter->first << " ";
	}
	cout << endl;

	cout << "* Transitions Map:" << endl;
	for(int i = 0; i < dfa_.size(); i++)
	{	
		int curState = dfa_[i].first;
		const vector<PIC> &vec = dfa_[i].second;

		printf("\tState %d: ", curState);
		for(int j = 0; j < vec.size(); j++)
		{
			printf("(%d->%d %c) ", curState, vec[j].first, vec[j].second);
		}
		cout << endl;
	}
}

void DFA::addNewState(int newState)
{
	vector<PIC> linkList;

	node2index_[newState] = dfa_.size();

	dfa_.push_back( PIPIC(newState, linkList) );
}

void DFA::addTransition(int a, int b, char ch)
{
	int indexA = node2index_[a];

	vector<PIC> &vec = dfa_[indexA].second;

	vec.push_back( PIC(b, ch) );

	numOfTransitions++;
}

bool DFA::isAccepted(int curState)
{
	
}