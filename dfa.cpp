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

/**
 * load DFA configuration file (.dfa file)
 * 载入DFA配置文件(.dfa文件)
 */
void DFA::load(const string path)
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
	in >> tmp;
	setStartState(tmp);

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

	checkDFATransitions();

	in.close();
}

/**
 * save current dfa settings into a file
 * 将当前DFA配置保存到文件中
 */
void DFA::save(const string path)
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

/**
 * travel through the DFA and find out all possible expressions which 
 * length is less than or equal to maxDepth
 * 遍历整个DFA，找出所有长度至多为maxDepth的合法表达式
 */
void DFA::travel(int maxDepth)
{
	_travel("", startState_, maxDepth);
}

/**
 * check if string str will be accepted by the DFA.
 * if showProcess is true, then print out the check process.
 * 判断表达式是否会被接受，如果showpProcess为真，则输出中间过程
 */
bool DFA::checkExpression(const string str, bool showProcess)
{
	int len = str.length();
	int curState = startState_;

	for(int i = 0; i < len; i++)
	{
		curState = _getNextState(curState, str[i]);
	}

	return _isAccepted(curState);
}

/**
 * Show a prief description of current DFA
 * 输出当前DFA内容
 */
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

/**
 * Add a new state node
 * 添加新的状态
 */
void DFA::addNewState(int newState)
{
	vector<PIS> linkList;

	// Check Duplicate
	if(node2index_.find(newState) != node2index_.end())
	{
		cerr << "Duplicate State: " << newState << endl;
		exit(1);
	}

	node2index_[newState] = dfa_.size();

	dfa_.push_back( PIPIS(newState, linkList) );
}

/**
 * Add a new transition
 * 添加新的状态转移
 */
void DFA::addTransition(int a, int b, string str)
{
	// Check if state a, b exists
	if(node2index_.find(a) == node2index_.end() 
		|| node2index_.find(b) == node2index_.end())
	{
		cerr << "Cannot find state: " << a << ", " << b << endl;
		exit(1);
	}

	// Check if alphabet str exist
	if(alphabets_.find(str) ==  string::npos)
	{
		cout << "Do not have such alphabet: " << str << endl;
		exit(1);
	}

	int indexA = node2index_[a];

	vector<PIS> &vec = dfa_[indexA].second;

	vec.push_back( PIS(b, str) );

	numOfTransitions_++;
}

/**
 * Set Start State
 * 设置初始状态
 */
void DFA::setStartState(int startState)
{
	if(node2index_.find(startState) == node2index_.end())
	{
		cerr << "Cannot find the start state: " << startState << " in the whole states" << endl;
		exit(1);
	}
	startState_ = startState;
}

/**
 * Set final state
 * 设置接受状态
 */
void DFA::setAcceptedStates(const std::vector<int> vec)
{
	if(vec.size() == 0)
	{
		cerr << "Empty accepted state" << endl;
		exit(1);
	}

	for(int i = 0; i < vec.size(); i++)
	{
		acceptedStates_[vec[i]] = true;
	}
}

/**
 * Set Alphabets set
 * 设置字符集
 */
void DFA::setAlphabets(std::string alphabets)
{
	alphabets_ = alphabets;
}

/**
 * Check current DFA transition table if is correct
 * 检查当前DFA状态转移是否合法
 */
bool DFA::checkDFATransitions()
{	
	int i, j, k;
	if(acceptedStates_.size() == 0)
	{
		cerr << "Empty accepted state" << endl;
		exit(1);
	}

	// Check transition table if is complete
	for(i = 0; i < dfa_.size(); i++)
	{
		int curState = dfa_[i].first;
		vector<PIS> linkList = dfa_[i].second;

		for(j = 0; j < alphabets_.length(); j++)
		{
			for(k = 0; k < linkList.size(); k++)
			{
				if(linkList[k].second[0] == alphabets_[j])
					break;
			}

			if(k == linkList.size())
			{
				cerr << "State " << curState << " do NOT have transition of " << alphabets_[j] << endl;
				exit(0);
			}
		}
	}
}

/**
 * Check if curState is a final state
 * 判断当前状态是否被接受
 */
bool DFA::_isAccepted(int curState)
{
	if(acceptedStates_.find(curState) != acceptedStates_.end())
		return true;
	else
		return false;
}

/**
 * Find all possible transitions of current state
 * 找到当前节点所有可能的状态转移
 */
void DFA::_getNextTransitions(int curState, vector<PIS> &nextStates)
{
	int curStateIndex = node2index_[curState];
	int size = dfa_[curStateIndex].second.size();
	const vector<PIS> &linkList = dfa_[curStateIndex].second;

	for(int i = 0; i < size; i++)
		nextStates.push_back(linkList[i]);
}

/**
 * Get the next state when current state read in `alphabet`
 * 找出当前节点读入alphabet后的下一节点
 */
int DFA::_getNextState(int curState, char alphabet)
{
	int curStateIndex = node2index_[curState];
	vector<PIS> linkList = dfa_[curStateIndex].second;

	for(vector<PIS>::iterator iter = linkList.begin();
		iter != linkList.end(); iter++)
	{
		if(iter->second[0] == alphabet)
		{
			return iter->first;
		}
	}

	// check for special alphabet `~`, which means any alphabet other than `\n`
	for(vector<PIS>::iterator iter = linkList.begin();
		iter != linkList.end(); iter++)
	{
		if(iter->second == "~")
		{
			return iter->first;
		}
	}

	return -1;
}

/**
 * Real travel funtion, call by the wrapper function travel(int maxDepth)
 * 真正的遍历DFA函数，被travel函数调用
 */
void DFA::_travel(string str, int curState, int maxDepth)
{
	if(str.length() <= maxDepth && _isAccepted(curState))
	{
		cout << str << endl;
	}

	if(str.length() == maxDepth)
		return;

	vector<PIS> nextStates;
	_getNextTransitions(curState, nextStates);

	for(vector<PIS>::iterator iter = nextStates.begin(); 
		iter != nextStates.end(); iter++)
	{
		string tmp = iter->second;
		_travel(str + iter->second, iter->first, maxDepth);
	}
}