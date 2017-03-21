#include "dfa.h"

using namespace std;

DFA::DFA()
{
	numOfTransitions_ = 0;
}

DFA::~DFA()
{
	// ...
}

void DFA::load(const char *path)
{
	ifstream in(path);
	int n, tmp, a, b;
	string str;

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
		in >> a >> b >> str;
		addTransition(a, b, str);
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
	out << numOfTransitions_ << endl;
	// write in each transition
	for(int i = 0; i < dfa_.size(); i++)
	{	
		int curState = dfa_[i].first;
		const vector<PIS> &vec = dfa_[i].second;

		for(int j = 0; j < vec.size(); j++)
		{
			out << curState << " " << vec[j].first << " " << vec[j].second << endl;
		}
	}

	out.close();
}

void DFA::travel(int maxDepth)
{
	_travel("", startState_, maxDepth);
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
		const vector<PIS> &vec = dfa_[i].second;

		printf("\tState %d: ", curState);
		for(int j = 0; j < vec.size(); j++)
		{
			printf("(%d->%d ", curState, vec[j].first);
			cout << vec[j].second << ") ";
		}
		cout << endl;
	}
}

void DFA::addNewState(int newState)
{
	vector<PIS> linkList;

	node2index_[newState] = dfa_.size();

	dfa_.push_back( PIPIS(newState, linkList) );
}

void DFA::addTransition(int a, int b, string str)
{
	int indexA = node2index_[a];

	vector<PIS> &vec = dfa_[indexA].second;

	vec.push_back( PIS(b, str) );

	numOfTransitions_++;
}

bool DFA::_isAccepted(int curState)
{
	if(acceptedStates_.find(curState) != acceptedStates_.end())
		return true;
	else
		return false;
}

void DFA::_getNextStates(int curState, vector<PIS> &nextStates)
{
	int curStateIndex = node2index_[curState];
	int size = dfa_[curStateIndex].second.size();
	const vector<PIS> &linkList = dfa_[curStateIndex].second;

	for(int i = 0; i < size; i++)
		nextStates.push_back(linkList[i]);
}

void DFA::_travel(string str, int curState, int maxDepth)
{
	if(str.length() <= maxDepth && _isAccepted(curState))
	{
		cout << str << endl;
	}

	if(str.length() == maxDepth)
		return;

	vector<PIS> nextStates;
	_getNextStates(curState, nextStates);

	for(vector<PIS>::iterator iter = nextStates.begin(); 
		iter != nextStates.end(); iter++)
	{
		string tmp = iter->second;
		_travel(str + iter->second, iter->first, maxDepth);
	}
}