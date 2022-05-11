#include "input.h"
#include "dcll.h"

int main()
{
    Formula form;
    string a;
    cin>>a;
    form.input(a);
    form.output();
    form.showVariable();
    form.calcu();
    form.stdoutput();

    Dcll solver(a);
    cout<<solver.start();

    return 0;