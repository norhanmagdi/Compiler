#ifndef __LL1_PARSER__
#define __LL1_PARSER__

#include "../include/table.h"
#include "../include/ParseTable.h"


class LL1_parser{


public:
    LL1_parser(string first_NonTerminal,vector<pair<string,vector<string>>>* Grammar,
    unordered_set<string>* Terminals, unordered_set<string>* Nonterminals);
    void is_valid_input(vector<string> input);
    void print_table();


private:
    table * parseing_table;
    string frist_nonterminal;
    unordered_set<string> * terminals;
    unordered_set<string> * nonterminals;
    bool validate_syntax(vector<string> input);
    bool valid_parser;

};

#endif