#ifndef DCLL_H_
#define DCLL_H_

#include "input.h"

class Dcll:public Formula
{
private:
    int *clause;//clause usable unit number
    int *timVariable;//the time a variable show up
public:
    Dcll() {}
    Dcll(string a):Formula(a) {
        clause=new int[numConj]();
        timVariable=new int[numVariable]();
        for(int i=0;i<numConj;i++)
        {
            for(int j=0;j<numVariable;j++)
            {
                if(conj[i][j])
                {
                    clause[i]++;
                    timVariable[j]++;
                }
            }
        }
    }
    Dcll(const Dcll& papa);
    void change(int noVa,bool val);
    void deleClause(int i);
    void isolate();//if there is a clause with one variable
    void single();//if a variable only appear in one clause
    bool emptyClause();
    bool clearall();
    bool start();
    bool judge(int noVa,bool val);
};

#endif