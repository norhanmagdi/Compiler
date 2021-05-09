//
// Created by hp on 09/05/2021.
//

#ifndef MAIN_CPP_MINIMIZER_H
#define MAIN_CPP_MINIMIZER_H

#include "../include/DFA.h"

class DFA;
class Minimizer {
public:
    Minimizer () {};
    void minimize();
protected:
private:
    bool findState (const vector<vector<DFA::DState*>>& pp, DFA::DState* state);
    bool canBeCombined (vector<vector<DFA::DState*>>& partitions, DFA::DState *state1, DFA::DState *state2);
    void updateTable(vector<DFA::DState *> temp);
    map <DFA::DState* , map<string , DFA::DState*>> DFATable;
    vector<vector<DFA::DState*>> minimizePartition (vector<vector<DFA::DState*>> partitions);
};

#endif //MAIN_CPP_MINIMIZER_H
