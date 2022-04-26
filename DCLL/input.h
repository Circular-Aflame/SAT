#ifndef INPUT_H_
#define INPUT_H_
//Here defines Formula to store a formula.
//Providing function: 
// Input a formula stored as an object.
// Output the stantard conjunctive clauses of the formula.
//Auther: circular
//Date:2022.4.25
#include <stdio.h>

class Formula
{
private:
	int numVariable;
	char* variable;

public:
	void input();

};

#endif