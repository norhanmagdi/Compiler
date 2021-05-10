#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <bits/stdc++.h>
#include "DFA.h"

using namespace std;

class Scanner
{
    public:
        Scanner(DFA* dfa);
        virtual ~Scanner();
        void scanInput(string &inputFile);
        vector<pair<string,string>> scanWord(string word);

    protected:

    private:
        vector<pair<string, string>> tokens;
        GLOBAL *global = global->getInstance();
        DFA* finalDFA;
};

#endif // SCANNER_H
