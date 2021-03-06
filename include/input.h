#ifndef INPUT_H_
#define INPUT_H_
//Here defines Formula to store a formula.
//Providing function: 
// Input a formula stored as an object.
// Output the stantard conjunctive clauses of the formula.
//Auther: circular
//Date:2022.4.25
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Formula
{
protected:
	int numVariable;//number of variable
	vector<string> variable;//variable name
	string origin;//oringinal formula
	int numConj;//number of conjunctive
	int** conj;//storey of conjuntives
	bool* value;//results
	int numValue;//sum of values
public:
	Formula() {}
	Formula(string a) {input(a);}
	void input(string a);//input the formula
	void getVariable(string a);//get the variables
	void getConj(string a);//get the conj

	void calcu();

	void output();//output the conjunctive
	void stdoutput();//the oringinal formula as when it was input
	void showVariable();
};

#endif