#ifndef SCANNER_H
#define SCANNER_H
#include <iostream>
#include <bits/stdc++.h>
#include "DFA.h"

using namespace std;

class Scanner
{
    public:
        Scanner(DFA* rulesDFA, DFA* RDDFA);
        virtual ~Scanner();
        vector<string> scanInput(string &inputFile);
        string scanWord(string word);

    protected:

    private:
        pair<Node*, int> checkRE (Node* current, int inputIndx);
        vector<string> tokens;
        GLOBAL *global = global->getInstance();
        map <Node* , map<string , Node*>> rulesDFATable;
        map <Node* , map<string , Node*>> RDDFATable;
        DFA* rulesDFA;
        DFA* RDDFA;

    void toStrinsVector(string word);

    pair<Node *, int> checkRD(Node *current, int chrIndx, string word);
};

#endif // SCANNER_H
