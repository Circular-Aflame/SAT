#include "input.h"

void Formula::getVariable(string a)
{
    int i=-1,j;
    string temp;
    numVariable=0;
    while(a[++i])
    {
        if(a[i]=='('||a[i]=='!')continue;
        j=i;
        while(a[++i]!=')'&&a[i]!='|'){}
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

void Formula::getConj(string a)
{
    int i=-1,j;
    int item=0;//the number of current conj
    string temp;
    while(a[++i])
    {
        if(a[i]=='('||a[i]=='!')continue;
        j=i;
        while(a[++i]!=')'&&a[i]!='|'){}
        temp=a.substr(j,i-j);
        for(int k=0;k<numVariable;k++)
        {
            if(temp==variable[k])
            {
                if(j>0&&a[j-1]=='!')
                {
                    conj[item][k]=-1;
                }
                else
                {
                    conj[item][k]=1;
                }
                break;
            }
        }
        if(a[i]==')')
        {
            if(a[++i])
            {
                item++;
                continue;
            }
            else{break;}
        }
    }
}

void Formula::input(string a)
{
    numConj=1;
    for(int i=0;a[i];i++)
    {
        if(a[i]=='&')
        {
            numConj++;
        }
    }
    conj=new int*[numConj];
    getVariable(a);
    for(int i=0;i<numConj;i++)
    {
        conj[i]=new int[numVariable]();
    }
    getConj(a);
}

void Formula::calcu()
{
    numValue=1<<numVariable;
    value=new bool[numValue]();
    bool* test;
    bool temp,part;
    for(int i=0;i<numValue;i++)
    {
        test=new bool[numVariable];
        for(int j=0;j<numVariable;j++)
        {
            test[j]=i&(1<<(numVariable-1-j));
        }
        //calculate the value of the formula
        temp=1;
        for(int k=0;k<numConj;k++)
        {
            part=0;
            for(int h=0;h<numVariable;h++)
            {
                if(conj[k][h]==-1)
                {
                    part=part|(!test[h]);
                }
                if(conj[k][h]==1)
                {
                    part=part|test[h];
                }
            }
            temp=temp&part;
            if(!temp)break;//boundary
        }
        if(temp)
        {
            value[i]=1;
        }

    }
}

void Formula::output()
{
    cout<<origin;
}

void Formula::stdoutput()
{
    cout<<"True assignment values:";
    for(int i=0;i<numValue;i++)
    {
        if(value[i])
        {
            cout<<" "<<i;
        }
    }
    cout<<endl;
}

void Formula::showVariable()
{
    for(int i=0;i<numVariable;i++)
    {
        cout<<variable[i]<<" ";
    }
    cout<<endl;
