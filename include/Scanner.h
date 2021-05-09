#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
class Node;
class Scanner
{
    public:
        Scanner();
        virtual ~Scanner();
        void scanInput(string &inputFile,DFA* dfa);
        vector<pair<string,string>> scanWord(string word);

    protected:

    private:
};

#endif // SCANNER_H
