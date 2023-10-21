#include "common.h"

using namespace Minisat;

bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var variables[1000];
    int i, j;
    for (i = 0; i < m; ++i)
        variables[i] = solver.newVar();

    // your solution start from here.
    // TODO: your code here

    //variables[i]means i buttons
    //states[i]saves each stone's state
    //button[i][2]saves each button is in control of no.button[i][0]/button[i][1] stone
    int stones[1000][2] = {0};//no.i stone is controled by 1/2 buttons
    for (i = 1; i <= m; i++){
        for (j = 0; j < 2; j++){
            ( stones[button[i-1][j]][0] ? stones[button[i-1][j]][1] : stones[button[i-1][j]][0] ) = i;
        }
    } 
    for( i = 1; i <= n; i++){
        if (states[i-1] == 0){//underwater
            if (stones[i][1] == 0){//only controled by 1 button
                solver.addClause(mkLit(variables[stones[i][0] - 1]));
            }
            else {//controled by 2 buttons
                solver.addClause(~mkLit(variables[stones[i][0] - 1]), ~mkLit(variables[stones[i][1] - 1]));
                solver.addClause(mkLit(variables[stones[i][0] - 1]), mkLit(variables[stones[i][1] - 1]));
            }
        }
        if (states[i-1] == 1){//overwater
            if (stones[i][1] == 0){//only controled by 1 button
                solver.addClause(~mkLit(variables[stones[i][0] - 1]));
            }
            else {//controled by 2 buttons
                solver.addClause(~mkLit(variables[stones[i][0] - 1]), mkLit(variables[stones[i][1] - 1]));
                solver.addClause(mkLit(variables[stones[i][0] - 1]), ~mkLit(variables[stones[i][1] - 1]));
            }
        }
    }

    // your solution end here.
    // solve SAT problem
    auto sat = solver.solve();
    if (sat)
    {
        for (i = 0; i < m; ++i)
            answer[i] = (solver.modelValue(variables[i]) == l_True);
        return true;
    }
    return false;
}
