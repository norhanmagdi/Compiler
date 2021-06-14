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
    unordered_set<string> getTerminals();
    unordered_set<string> getNonTerminals();
    vector<pair<string,vector<string>>> getLeftRecGrammar();
    vector<pair<string,vector<string>>> getModifiedGrammar();
    void setLeftRecGrammar(vector<pair<string,vector<string>>> leftRecGrammar);
    void setModifiedGrammar(vector<pair<string,vector<string>>> modifiedGrammar);
    void setNonTerminals(unordered_set<string> t);
    string getFirstNonTerminal();
    void setFirstNonTerminal(string fnt);
    vector<pair<string,vector<string>>> get_splited_grammar_set();
    void leftRecursion(const vector<pair<string,vector<string>>> terms);
    void leftFactoring(const vector<pair<string,vector<string>>> terms);
    bool containLeftRecursion(pair<string,vector<string>> term);
    vector<pair<string,vector<string>>> solveLeftRecursion(pair<string,vector<string>> term);
    pair<string,vector<string>>indirectLeftRec(pair<string,vector<string>> termi,pair<string,vector<string>> termj);
    vector<pair<string,vector<string>>>solveLeftFactoring(pair<string,vector<string>> term);
    void writeFile(vector<pair<string,vector<string>>> finalGrammar);
    bool containLeftFactoring(pair<string,vector<string>> term);



protected:

private:
    // vector<pair<string,vector<string>>> grammar;
    vector<pair<string,vector<string>>> splited_grammar_set;

    void parseLine(string line);
    void readFile();
    void splitGrammar();
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    vector<pair<string,vector<string>>> leftRecGrammar;
    vector<pair<string,vector<string>>> modifiedGrammar;
    string firstNonTerminal;

};

#endif // READGRAMMAR_H
