#include "input.h"

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
    return 0;
}