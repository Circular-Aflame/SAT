#include "dpll.h"

Dpll::Dpll(const Dpll&papa)
{
    numVariable=papa.numVariable;
    variable=papa.variable;
    numConj=papa.numConj;
    conj=new int*[numConj];
    for(int i=0;i<numConj;i++)
    {
        conj[i]=new int[numVariable]();
    }
    clause=new int[numConj]();
    for(int i=0;i<numConj;i++)
    {
        clause[i]=papa.clause[i];
    }
    timVariable=new int[numVariable]();
    for(int i=0;i<numVariable;i++)
    {
        timVariable[i]=papa.timVariable[i];
    }
}

bool Dpll::emptyClause()
{
    for(int i=0;i<numConj;i++)
    {
        if(!clause[i])
        {
            return true;
        }
    }
    return false;
}

void Dpll::deleClause(int i)
{
    clause[i]=-1;
    for(int j=0;j<numVariable;j++)
    {
        if(conj[i][j])
        {
            timVariable[j]--;
        }
    }
}

void Dpll::single()
{
    for(int i=0;i<numVariable;i++)
    {
        if(timVariable[i]==1)
        {
            for(int j=0;j<numConj;j++)
            {
                if(conj[j][i])
                {
                    deleClause(j);
                }
            }
        }
    }
}

void Dpll::isolate()
{
    int tem=-1;
    int test;
    for(int i=0;i<numConj;i++)
    {
        if(clause[i]==1)
        {
            for(int j=0;j<numVariable;j++)
            {
                if(conj[i][j])
                {
                    tem=j;
                    test=conj[i][j];
                    break;
                }
            }
        }
    }
    if(tem==-1)
    {
        return;
    }
    for(int i=0;i<numConj;i++)
    {
        if(conj[i][tem]*test==1)
        {
            deleClause(i);
        }
        if(conj[i][tem]*test==-1)
        {
            clause[i]--;
            conj[i][tem]=0;
            timVariable[tem]--;
        }
    }
    isolate();
}

bool Dpll::clearall()
{
    for(int i=0;i<numConj;i++)
    {
        if(clause[i]!=-1)
        {
            return false;
        }
    }
    return true;
}

bool Dpll::start()
{
    isolate();
    single();
    if(clearall())
    {
        return true;
    }
    if(emptyClause())
    {
        return false;
    }
    int no;//to assign value;
    for(int i=0;i<numVariable;i++)
    {
        if(timVariable[i])
        {
            no=i;
            break;
        }
    }
    return judge(no,0)||judge(no,1);
}

void Dpll::change(int noVa,bool val)
{
    for(int i=0;i<numConj;i++)
    {
        if(conj[i][noVa]==1)
        {
            if(val)
            {
                deleClause(i);
            }
            else
            {
                clause[i]--;
                conj[i][noVa]=0;
                timVariable[noVa]--;
            }
        }
        if(conj[i][noVa]==-1)
        {
            if(val)
            {
                clause[i]--;
                conj[i][noVa]=0;
                timVariable[noVa]--;
            }
            else
            {
                deleClause(i);
            }
        }
    }
}

bool Dpll::judge(int noVa,bool val)
{
    Dpll sub=*this;
    sub.change(noVa,val);
    return sub.start();
}
