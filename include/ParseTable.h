#ifndef PHASE2_PARSETABLE_H
#define PHASE2_PARSETABLE_H
#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;

class ParseTable{
public:
    ParseTable(unordered_set<string> terminals, unordered_set<string> non_terminals,
               vector<pair<string, vector<string>>> split_grammar_set, string first_Nonterminal);

    unordered_map<string, unordered_set<string>> getFirstSet();
    unordered_map<string, unordered_set<string>> getFollowSet();

    void print_firstSet();
    void print_followSet();

protected:

private:
    string first_nonterminal;
    bool not_marked;
    unordered_set<string> terminals;
    unordered_set<string> non_terminals;
    vector<pair<string,vector<string>>> split_grammar_set;
    vector<pair<string,vector<string>>> split_first_set;
    unordered_map<string, unordered_set<string>> first_set;
    unordered_map<string, unordered_set<string>> follow_set;
    void first();
    void firstEach(const pair<string,vector<string>>& productions);
    void checkEps(pair<string,vector<string>> productions);
    void follow();
    void followOne(const pair<string,vector<string>>& productions);
    void followTwo(const pair<string,vector<string>>& productions);
    vector<string> split(string production);
};

#endif //PHASE2_PARSETABLE_H
