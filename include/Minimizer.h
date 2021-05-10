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
    bool findState (const vector<vector<Node*>>& pp, Node* state);
    bool canBeCombined (vector<vector<Node*>>& partitions, Node *state1, Node *state2);
    void updateTable(vector<Node *> temp);
    map <Node* , map<string , Node*>> DFATable;
    vector<vector<Node*>> minimizePartition (vector<vector<Node*>> partitions);
};

#endif //MAIN_CPP_MINIMIZER_H
