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
	/**
	 * load DFA configuration file (.dfa file)
	 * 载入DFA配置文件(.dfa文件)
	 */
	void load(const std::string path);
	/**
	 * save current dfa settings into a file
	 * 将当前DFA配置保存到文件中
	 */
	void save(const std::string path);
	/**
	 * travel through the DFA and find out all possible expressions which 
	 * length is less than or equal to maxDepth
	 * 遍历整个DFA，找出所有长度至多为maxDepth的合法表达式
	 */
	void travel(int maxDepth);
	/**
	 * check if string str will be accepted by the DFA.
	 * if showProcess is true, then print out the check process.
	 * 判断表达式是否会被接受，如果showpProcess为真，则输出中间过程
	 */
	bool checkExpression(const std::string, bool showProcess=false);
	/**
	 * Show a prief description of current DFA
	 * 输出当前DFA内容
	 */
	void showDFA();

private:
	/**
	 * Add a new state node
	 * 添加新的状态
	 */
	void _addNewState(int newState);
	/**
	 * Add a new transition
	 * 添加新的状态转移
	 */
	void _addTransition(int a, int b, std::string str);
	/**
	 * Check if curState is a final state
	 * 判断当前状态是否被接受
	 */
	bool _isAccepted(int curState);
	/**
	 * Find all possible transitions of current state
	 * 找到当前节点所有可能的状态转移
	 */
	void _getNextTransitions(int curState, std::vector<PIS> &nextStates);
	/**
	 * Get the next state when current state read in `alphabet`
	 * 找出当前节点读入alphabet后的下一节点
	 */
	int _getNextState(int curState, char alphabet);
	/**
	 * Real travel funtion, call by the wrapper function travel(int maxDepth)
	 * 真正的遍历DFA函数，被travel函数调用
	 */
	void _travel(std::string str, int curState, int maxDepth);

private:
	// store alphabets set 保存字符集
	std::string alphabets_;

	// store DFA transition table 保存DFA状态转移表
	std::vector<PIPIS> dfa_;
	// a hash table, final each state's index in transition table
	// 根据状态值找到状态转移表中的索引
	std::map<int, int> node2index_;

	// 状态转移数目
	int numOfTransitions_;
	
	// Start State 初始状态
	int startState_;
	// Final(Accepted) State 接受状态
	std::map<int, bool> acceptedStates_;
};

#endif 	// _DFA_H