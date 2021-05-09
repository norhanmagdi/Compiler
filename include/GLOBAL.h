//
// Created by hp on 07/05/2021.
//

#ifndef MAIN_CPP_GLOBAL_H
#define MAIN_CPP_GLOBAL_H
#include <bits/stdc++.h>

using namespace std;

class GLOBAL {
private:
    GLOBAL() { num = 0;}
    virtual ~GLOBAL() {}
    int num;

protected:

public:
    static GLOBAL* getInstance();
    static const int MAX_NUM = 1000;
    int getNumNow();
    int getNum();
    vector<string> inputSymbols;
    string transitionTable[MAX_NUM][MAX_NUM];
};


#endif //MAIN_CPP_GLOBAL_H
