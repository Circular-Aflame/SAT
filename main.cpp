#include "input.h"
#include "dpll.h"

int main()
{
    Formula form;
    string a;
    cin >> a;
    form.input(a);
    form.output();
    form.showVariable();
    form.calcu();
    form.stdoutput();

    Dpll solver(a);
    cout << solver.start();

    return 0;
}