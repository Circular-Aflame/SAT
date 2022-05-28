#include "input.h"
#include "CDCL.h"
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
    //cout << solver.start();
    cout << endl;
    CDCL cdcl(a);
    bool ans = false;
    int node_id = unvisited;
    cdcl.get_ans(ans, node_id, 0);
    cout << ans << endl;
    return 0;
}