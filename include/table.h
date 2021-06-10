#ifndef __TABLE__
#define __TABLE__

#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std;

vector<string>* split_string(string production);

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class table{
    public: 
        table(unordered_map<string,unordered_set<string>> first_set, unordered_map<string,unordered_set<string>> follow_set,
            vector<pair<string,vector<string>>> Grammar, unordered_set<string> Terminals);
        
         /*      To indicate whether the creation of the table was successful or not.    */
        bool is_valid();
        /*      Returns the production in the cell given as [nonterminal, terminal]. if the cell is empty returns "ERROR".  */
        string get_production(string nonterminal, string terminal);

        void print_table();

        void delete_table();

    
    private:
        bool check_terminal_production(string terminal, string production, string nonterminal, 
            unordered_set<string> Terminals, unordered_map<string, unordered_set<string>> first_set);
        bool valid_table;
        /*      [Non_Terminal][Terminal] -->    production      */
        unordered_map<pair<string,string>, string, hash_pair> parse_table;

};


#endif