#include "table.h"
#ifndef __LL1_PARSER__
#define __LL1_PARSER__

class LL1_parser{

    public:
        LL1_parser(string first_NonTerminal, unordered_map<string, unordered_set<string>*>* first_set,
            unordered_map<string, unordered_set<string>*>* follow_set,vector<pair<string,vector<string>*>>* Grammar,
            unordered_set<string>* Terminals, unordered_set<string>* Nonterminals);
        bool is_valid_input(vector<string> input);

    private:
        table * parseing_table;
        string frist_nonterminal;
        unordered_set<string> * terminals;
        unordered_set<string> * nonterminals;
        bool validate_syntax(vector<string> input);
        bool valid_parser;

};

#endif