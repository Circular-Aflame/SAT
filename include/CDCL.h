#pragma once
#ifndef CDCL_H
#define CDCL_H

#include "dpll.h"
#include <vector>
#include <string>
#include <queue>
#define unvisited -1
struct LevelNode {
	int id, rank;
	int decision_level;
	int conj;
	bool status;
	LevelNode() :id(0), rank(0), decision_level(unvisited), status(0), conj(0) {}
	LevelNode(const LevelNode& a) :id(a.id), rank(a.rank), decision_level(a.decision_level), conj(a.conj), status(a.status) {}
	LevelNode(const int& _id, const int& _rank, const int& _decision_level, const bool& _status, const int& _conj) :id(_id), rank(_rank), decision_level(_decision_level), status(_status), conj(_conj) {}
	void clear() {
		id = conj = rank = 0;
		status = false;
		decision_level = unvisited;
	}
};

class CDCL : public Formula {
private:
	LevelNode* var;
	bool* is_SAT;
	vector<LevelNode> beforelevel_conflict_set;
	vector<LevelNode> currentlevel_conflict_set;
	vector<std::string> visit_trace;
	int current_level = 0;
	int current_rank = 0;
	bool single_conj(const int& conj_id);
	void confirm(const int& conj_id);
	void check(const int& conj_id, bool& is_conflict);
	void analyse_clause(const int& conj_id, const int&);
	bool appear(const int& variable_id);
	LevelNode biggest_rank(vector<LevelNode>&, int&);
	std::string current_trace();
	bool find_trace(const std::string&);
public:
	CDCL(const std::string& s): Formula(s){
		var = new LevelNode[numVariable]();
		is_SAT = new bool[numConj];
		for (int i = 0; i < numConj; i++)
			is_SAT[i] = false;
	}
	~CDCL() {
		delete[] var;
		delete[] is_SAT;
	}
	void UP(bool& is_conflict, int& conflict_clause);
	void clause_learning(const int&);
	void get_ans(bool&, int&, bool);
	void traceback(LevelNode& node_change);
};

#endif // !CDCL_H