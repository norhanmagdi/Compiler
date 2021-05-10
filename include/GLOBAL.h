//
// Created by hp on 07/05/2021.
//

#ifndef MAIN_CPP_GLOBAL_H
#define MAIN_CPP_GLOBAL_H
#include <bits/stdc++.h>
//#include "Node.h"

using namespace std;
//class Node;
class GLOBAL {
private:
    GLOBAL() { num = 0;}
    virtual ~GLOBAL() {}
    int num;

protected:

public:
    static GLOBAL* getInstance();
    set<string> keyWords;
    set<char> puncs;
    static const int MAX_NUM = 1000;
    int getNumNow();
    int getNum();
    int NFAStates;
    set<string> inputSymbols;
    string transitionTable[MAX_NUM][MAX_NUM];
//    map <Node* , map<string , vector<Node*>>> NFATable;
};


#endif //MAIN_CPP_GLOBAL_H
