#include "CDCL.h"
#include <cstdlib>
using namespace std;

string CDCL::current_trace()
{
	string ans = "";
	for (int i = 0; i < numVariable; i++)
	{
		if (var[i].decision_level == unvisited)
			ans += "2";
		else {
			if (var[i].status == true)
				ans += "1";
			else
				ans += "0";
		}
	}
	return ans;
}

bool CDCL::find_trace(const string& s)
{
	bool flag;
	for (size_t i = 0; i < visit_trace.size(); i++)
	{
		flag = true;
		//cout << visit_trace[i] << " ";
		for (int j = 0; j < numVariable; j++)
		{
			if (s[j] != visit_trace[i][j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			return true;
	}
	//cout << endl;
	return false;
}

void CDCL::check(const int& conj_id, bool& is_conflict)
{
	bool flag = false;
	for (int i = 0; i < numVariable; i++)
	{
		if (conj[conj_id][i] != 0)
		{
			//cout << var[0].decision_level << "iii" << endl;
			if (var[i].decision_level != unvisited)
			{
				//cout << "check.enter.\n";
				if (conj[conj_id][i] == 1 && var[i].status == true || conj[conj_id][i] == -1 && var[i].status == false)
				{
					is_SAT[conj_id] = true;
					is_conflict = false;
					return;
				}
			}
		}
	}
	for (int i = 0; i < numVariable; i++)
	{
		if (conj[conj_id][i] != 0)
		{
			if (var[i].decision_level == unvisited)
			{
				//cout << "conj " << conj_id << " unkown.\n";
				is_conflict = false;
				return;
			}
		}
	}
	//cout << "conj " << conj_id << " conflict.\n";
	is_conflict = true;
}

bool CDCL::single_conj(const int& conj_id)
{
	bool flag = false;
	for (int i = 0; i < numVariable; i++)
	{
		if (var[i].decision_level == unvisited && conj[conj_id][i] != 0)
		{
			if (!flag)
				flag = true;
			else
				return false;
		}
	}
	return flag;
}

void CDCL::confirm(const int& conj_id)
{
	for (int i = 0; i < numVariable; i++)
	{
		if (var[i].decision_level == unvisited && conj[conj_id][i] != 0)
		{
			var[i].decision_level = current_level;
			var[i].conj = conj_id;
			var[i].rank = current_rank;
			if (conj[conj_id][i] == 1)
				var[i].status = true;
			else
				var[i].status = false;
			//cout << "confirmed: " << i << " " << var[i].status << endl;
			is_SAT[conj_id] = true;
			return;
		}
	}
}

void CDCL::UP(bool& is_conflict, int& conflict_clause)
{
	for (int i = 0; i < numConj; i++)
	{
		//cout << "is_SAT: " << is_SAT[i] << endl;
		if (is_SAT[i])
			continue;
		else {
			//cout << i << endl;
			check(i, is_conflict);
			if (is_conflict)
			{
				conflict_clause = i;
				return;
			}
			if (single_conj(i) && !is_SAT[i])
			{
				confirm(i);
				current_rank++;
				UP(is_conflict, conflict_clause);
				if (is_conflict)
					return;
			}
		}
	}
	is_conflict = false;
}

bool CDCL::appear(const int& variable_id)
{
	for (size_t i = 0; i < beforelevel_conflict_set.size(); i++)
		if (beforelevel_conflict_set[i].id == variable_id)
			return true;
	for (size_t i = 0; i < currentlevel_conflict_set.size(); i++)
		if (currentlevel_conflict_set[i].id == variable_id)
			return true;
	return false;
}

void CDCL::analyse_clause(const int& conj_id, const int& node_id)
{
	for (int i = 0; i < numVariable; i++)
	{
		if (conj[conj_id][i] != 0 && i != node_id)
		{
			if (!appear(i))
			{
				if (var[i].decision_level < current_level)
				{
					if (conj[conj_id][i] == 1)
						beforelevel_conflict_set.push_back(LevelNode(i, var[i].rank, var[i].decision_level, true, var[i].conj));
					else
						beforelevel_conflict_set.push_back(LevelNode(i, var[i].rank, var[i].decision_level, false, var[i].conj));
				}
				else {
					if (conj[conj_id][i] == 1)
						currentlevel_conflict_set.push_back(LevelNode(i, var[i].rank, var[i].decision_level, true, var[i].conj));
					else
						currentlevel_conflict_set.push_back(LevelNode(i, var[i].rank, var[i].decision_level, false, var[i].conj));
				}
			}
		}
	}
}

LevelNode CDCL::biggest_rank(vector<LevelNode>& v, int& _id)
{
	int max = -1;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (v[i].rank > max)
		{
			max = v[i].rank;
			_id = i;
		}
	}
	return v[_id];
}

void CDCL::clause_learning(const int& conflict_clause)
{
	//cout << "clause learning.\n";
	int id;
	analyse_clause(conflict_clause, -1);
	//cout << "recorded list: \n";
	//for (size_t i = 0; i < beforelevel_conflict_set.size(); i++)
	//	cout << beforelevel_conflict_set[i].id << " " << beforelevel_conflict_set[i].rank << endl;
	//cout << "current list: \n";
	//for (size_t i = 0; i < currentlevel_conflict_set.size(); i++)
	//	cout << currentlevel_conflict_set[i].id << " " << currentlevel_conflict_set[i].rank << endl;
	while (currentlevel_conflict_set.size() > 1)
	{
		LevelNode cur = biggest_rank(currentlevel_conflict_set, id);
		//cout << "analyse clause: " << cur.conj << endl;
		analyse_clause(cur.conj, cur.id);
		//cout << "before erase.\n";
		//cout << "id: " << id << endl;
		currentlevel_conflict_set.erase(currentlevel_conflict_set.begin() + id);
		//cout << "recorded list: \n";
		//for (size_t i = 0; i < beforelevel_conflict_set.size(); i++)
		//	cout << beforelevel_conflict_set[i].id << " " << beforelevel_conflict_set[i].rank << endl;
		//cout << "current list: \n";
		//for (size_t i = 0; i < currentlevel_conflict_set.size(); i++)
		//	cout << currentlevel_conflict_set[i].id << " " << currentlevel_conflict_set[i].rank << endl;
	}
	beforelevel_conflict_set.push_back(LevelNode(currentlevel_conflict_set.front()));
}

void CDCL::traceback(LevelNode& node_change)
{
	node_change = beforelevel_conflict_set.back();
	beforelevel_conflict_set.pop_back();
	currentlevel_conflict_set.clear();
	current_level = 0;
	for (size_t i = 0; i < beforelevel_conflict_set.size(); i++)
	{
		current_level = max(current_level, beforelevel_conflict_set[i].decision_level);
	}
	for (int i = 0; i < numVariable; i++)
	{
		if (!appear(i))
		{
			var[i].clear();
		}
	}
	for (int i = 0; i < numConj; i++)
		is_SAT[i] = false;
	for (int i = 0; i < numConj; i++)
	{
		bool is_conflict;
		check(i, is_conflict);
	}
}

void CDCL::get_ans(bool& ans, int& node_id, bool change_status)
{
	//system("pause");
	if (ans)
		return;
	//cout << "current_level: " << current_level << endl;
	//cout << "current_trace: " << current_trace() << endl;
	int _node_id = unvisited;
	bool is_conflict;
	int conflict_clause;
	LevelNode node_change;
	bool SAT = true;
	for (int i = 0; i < numConj; i++)
	{
		if (is_SAT[i] == false)
			SAT = false;
	}
	if (SAT)
	{
		//cout << "SAT!\n";
		ans = true;
		return;
	}
	if (current_level == 0)
	{
		UP(is_conflict, conflict_clause);
		if (is_conflict)
		{
			ans = false;
			return;
		}
		current_level++;
		get_ans(ans, _node_id, 0);
		return;
	}
	//cout << "node_id: " << node_id << endl;
	if (node_id == unvisited)
	{
		//cout << "enter.\n";
		for (int i = 0; i < numVariable; i++)
		{
			//cout << "i: " << i << endl;
			if (var[i].decision_level == unvisited)
			{
				//cout << "enter2.\n";
				node_id = i;
				break;
			}
		}
		if (node_id == unvisited)
		{
			ans = true;
			return;
		}
		//cout << "out.\n";
		current_rank = 0;
		var[node_id].conj = unvisited;
		var[node_id].decision_level = current_level;
		//cout << "node_id_after: " << node_id << endl;
		var[node_id].rank = current_rank;
		current_rank++;
		var[node_id].id = node_id;
		for (int i = 0; i <= 1; i++)
		{
			//cout << variable[node_id] << " " << i << endl;
			var[node_id].status = i;
			//cout << current_trace() << endl;
			//cout << find_trace(current_trace()) << endl;
			if (find_trace(current_trace()))
				continue;
			else
				visit_trace.push_back(current_trace());
			UP(is_conflict, conflict_clause);
			//cout << "UP end.\n";
			if (is_conflict)
			{
				//cout << "Conflict!\n";
				//cout << "conflict clause: " << conflict_clause << endl;
				clause_learning(conflict_clause);
				traceback(node_change);
				_node_id = node_change.id;
			}
			current_level++;
			//cout << "next_change: " << node_change.id << " " << node_change.status << endl;
			//cout << "next current_level: " << current_level << endl;
			get_ans(ans, _node_id, node_change.status);
			if (ans)
			{
				//cout << "level: " << node_id << endl;
				return;
			}
		}
	}
	else {
		current_rank = 0;
		var[node_id].conj = unvisited;
		var[node_id].decision_level = current_level;
		//cout << "node_id_after: " << node_id << endl;
		var[node_id].rank = current_rank;
		current_rank++;
		var[node_id].id = node_id;
		var[node_id].status = change_status;
		if (find_trace(current_trace()))
			return;
		else
			visit_trace.push_back(current_trace());
		//cout << "before_UP: " << current_trace() << endl;
		UP(is_conflict, conflict_clause);
		//cout << "after UP: " << current_trace() << endl;
		//cout << "UP end.\n";
		if (is_conflict)
		{
			//cout << "Conflict!\n";
			//cout << "conflict clause: " << conflict_clause << endl;
			clause_learning(conflict_clause);
			traceback(node_change);
			_node_id = node_change.id;
		}
		current_level++;
		//cout << "next_change: " << node_change.id << " " << node_change.status << endl;
		//cout << "next current_level: " << current_level << endl;
		get_ans(ans, _node_id, node_change.status);
		if (ans)
		{
			//cout << "level: " << node_id << endl;
			return;
		}
	}
}