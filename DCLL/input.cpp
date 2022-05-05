#include "input.h"

void Formula::getVariable(string a)
{
    int i=-1,j;
    string temp;
    numVariable=0;
    while(a[++i])
    {
        if(a[i]=='(')continue;
        j=i;
        while(a[++i]!=')'&&a[++i]!='|'){}
        temp=a.substr(j,i-j);
        bool newVariable=true;
        for(int k=0;k<numVariable;k++)
        {
            if(temp==variable[k])
            {
                newVariable=false;
                break;
            }
        }
        if(newVariable)
        {
            variable.push_back(temp);
            numVariable++;
        }
        if(a[i]==')')
        {
            if(a[++i]){continue;}
            else{break;}
        }
    }
}

void Formula::input(string a)
{
    numConj=0;
    for(int i=0;a[i];i++)
    {
        if(a[i]=='&')
        {
            numConj++;
        }
    }
    conj=new int*[numConj];
    getVariable(a);
}