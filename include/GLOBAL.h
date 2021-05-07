//
// Created by hp on 07/05/2021.
//

#ifndef MAIN_CPP_GLOBAL_H
#define MAIN_CPP_GLOBAL_H
#include <bits/stdc++.h>

using namespace std;

class GLOBAL {
private:
    static const int MAX_NUM = 1000;
    int num;

public:
    GLOBAL() {num = 1;}
    int getNumNow();
    int getNum();
    string transitionTable[MAX_NUM][MAX_NUM];

protected:
};

#endif //MAIN_CPP_GLOBAL_H
