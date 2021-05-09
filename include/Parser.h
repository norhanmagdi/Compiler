//
// Created by hp on 06/05/2021.
//

#ifndef MAIN_CPP_PARSER_H
#define MAIN_CPP_PARSER_H

#include <bits/stdc++.h>
#include <regex>

#define SPACE " "
#define nLINE '\n'
#define SEPARATOR "--------------------------------------\n"
#define sp second
#define fp first

using namespace std;

class Parser
{
public:
    Parser() {};
    const set<string> RE_SYMPOLS = { "^" ,"|" ,"+" ,"*" ,"(" ,")","$"}; /* Where $ : equivilant to AND , ^ is equivilant to - */
    map<string, vector<string>> parse();

protected:

private:
    const char* RULES_FILE = "rules.in";
    const set<char> MAIN_PUNCS = { '{' ,'}' ,',' ,';' ,'(' ,')'};
    map<string , int>PRECEDENCE = {{"^", 4},
                                   {"|", 2},
                                   {"$", 3},
                                   {"+", 5},
                                   {"*", 6},
                                   {"(", 0},
                                   {")", 0}};

    void read_file();
    void parse_Line(string line);
    void save_puncs(const string& line);
    vector<string> divide_RE (string re);
    map<string, vector<string>> postfixREs;
    map<string, vector<string>> postfixRDs;
    static void save_keyWords(string line);
    static void save_RE (const string& line , int sep_indx);
    static void save_RD (const string& line , int sep_indx);
    vector<string> to_postfix(const vector<string>& exprVec);
    static bool sort_by_length(const string& s1, const string& s2);
};

#endif //MAIN_CPP_PARSER_H
