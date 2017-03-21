#include "dfa.h"

using namespace std;

DFA::DFA()
{
	numOfStates_ = 0;
}

DFA::~DFA()
{
	// ...
}

void DFA::load(char *path)
{
	ifstream in(path);
	int n, tmp, a, b;
	char ch;

	if( !in.is_open() )
	{
		cerr << "Cannot open file: " << path << endl;
		return;
	}

	// 字符集
	in >> alphabets_;
	// cout << alphabets_ << endl;

	// 状态节点
	in >> n;
	// cout << n << endl;
	for(int i = 0; i < n; i++)
	{
		in >> tmp;
		addNewState(tmp);
		// cout << tmp << " ";
	}
	// cout << endl;

	// start state
	in >> startState_;
	// cout << startState_ << endl;

	// accepted nodes
	in >> n;
	// cout << n << endl;
	for(int i = 0; i < n; i++)
	{
		in >> tmp;
		acceptedStates_.push_back(tmp);
		// cout << tmp << " ";
	}
	// cout << endl;

	in >> n;
	// cout << n << endl;
	for(int i = 0; i < n; i++)
	{
		in >> a >> b >> ch;
		addTransition(a, b, ch);
		// cout << a << " " << b << " " << ch << endl;
	}

	in.close();
}

void DFA::save(char *path)
{
	// ...
}

void DFA::showDFA()
{
	cout << "Alphabests: " << alphabets_ << endl;

	cout << "Start State: " << startState_ << endl;

	cout << "Accepted States: ";
	for(int i = 0; i < acceptedStates_.size(); i++)
		cout << acceptedStates_[i] << " ";
	cout << endl;

	cout << "Transitions Map:" << endl;
	for(int i = 0; i < dfa_.size(); i++)
	{	
		int curState = dfa_[i].first;
		const vector<PIC> &vec = dfa_[i].second;

		printf("State %d: ", curState);
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

	dfa_.push_back( PIPIC(newState, linkList) );

	node2index_[newState] = numOfStates_++;
}

void DFA::addTransition(int a, int b, char ch)
{
	int indexA = node2index_[a];

	vector<PIC> &vec = dfa_[indexA].second;

	vec.push_back( PIC(b, ch) );
}