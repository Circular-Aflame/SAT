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
using namespace std;

class Formula
{
private:
	int numVariable;//number of variable
	char* variable;//variable name
	string oringin;//oringinal formula
public:
	
	void input();//input the formula
	void output();//output the conjunctive
	void stdoutput();//the oringinal formula as when it was input

};

#endif