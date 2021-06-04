#ifndef READGRAMMAR_H
#define READGRAMMAR_H
#include <iostream>
#include <bits/stdc++.h>
using namespace std;
class readGrammar
{
    public:
        readGrammar(){};
        void parseGrammar();
        set<string> getTerminals();
        set<string> getNonTerminals();
        set<string> terminals;
        set<string> non_terminals;
        void setNonTerminals(set<string> t);
        vector<pair<string,vector<string>>> get_splited_grammar_set();
        vector<pair<string,vector<string>>> leftRecursion(const vector<pair<string,vector<string>>> terms);
        bool containLeftRecursion(pair<string,vector<string>> term);
        vector<pair<string,vector<string>>> solveLeftRecursion(pair<string,vector<string>> term);
        void print();



    protected:

    private:
       // vector<pair<string,vector<string>>> grammar;
        vector<pair<string,vector<string>>> splited_grammar_set;

        void parseLine(string line);
        void readFile();
        void splitGrammar();

};

#endif // READGRAMMAR_H
