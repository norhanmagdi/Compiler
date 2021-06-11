#include <iostream>
#include "../include/ParseTable.h"
#include "../include/table.h"
#include "../include/LL1_parser.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_set<string> terminals;
    terminals.insert("+");
    terminals.insert("*");
    terminals.insert("(");
    terminals.insert(")");
    terminals.insert("id");

    unordered_set<string> non_terminals;
    non_terminals.insert("E");
    non_terminals.insert("E'");
    non_terminals.insert("T");
    non_terminals.insert("T'");
    non_terminals.insert("F");

    vector<pair<string, vector<string>>> split_grammar_set;

    vector<string> temp;
    temp.push_back("T E'");
    pair<string, vector<string>> temp1;
    temp1.first = "E";
    temp1.second = temp;
    split_grammar_set.push_back(temp1);

    vector<string> temp2;
    temp2.push_back("+ T E'");
    temp2.push_back("eps");
    pair<string, vector<string>> temp3;
    temp3.first = "E'";
    temp3.second = temp2;
    split_grammar_set.push_back(temp3);

    vector<string> temp4;
    temp4.push_back("F T'");
    pair<string, vector<string>> temp5;
    temp5.first = "T";
    temp5.second = temp4;
    split_grammar_set.push_back(temp5);

    vector<string> temp6;
    temp6.push_back("* F T'");
    temp6.push_back("eps");
    pair<string, vector<string>> temp7;
    temp7.first = "T'";
    temp7.second = temp6;
    split_grammar_set.push_back(temp7);

    vector<string> temp8;
    temp8.push_back("( E )");
    temp8.push_back("id");
    pair<string, vector<string>> temp9;
    temp9.first = "F";
    temp9.second = temp8;
    split_grammar_set.push_back(temp9);

    ParseTable* pt = new ParseTable(terminals, non_terminals, split_grammar_set,"E");
    unordered_map<string, unordered_set<string>> first_set = pt->getFirstSet();
    unordered_map<string, unordered_set<string>> follow_set = pt->getFollowSet();

    cout << "first set\n";

    for (auto print : first_set) {
        cout << print.first << " -> ";
        for (auto st : print.second) {
            cout << st << " ";
        }
        cout << "\n";
    }
    cout << "follow set\n";

    for (auto print : follow_set) {
        cout << print.first << " -> ";
        for (auto st : print.second) {
            cout << st << " ";
        }
        cout << "\n";
    }

    cout << "*************" <<endl;

    LL1_parser * parser = new LL1_parser("E",&split_grammar_set,&terminals,&non_terminals);

    vector<string> input;
    input.push_back("id + id"); 

    parser->is_valid_input(input);


}
