#ifndef __TABLE__
#define __TABLE__

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>


using namespace std;


class table{
    public: 
        table(unordered_map<string, unordered_set<string>*>* first_set, unordered_map<string, unordered_set<string>*>* follow_set,
            vector<pair<string,vector<string>*>>* Grammar, unordered_set<string>* Terminals);
        
         /*      To indicate whether the creation of the table was successful or not.    */
        bool is_valid();
        /*      Returns the production in the cell given as [nonterminal, terminal]. if the cell is empty returns "ERROR".  */
        string get_production(string nonterminal, string terminal);
    
    private:
        bool check_terminal_production(string terminal, string production, string nonterminal, 
            unordered_set<string>* Terminals, unordered_map<string, unordered_set<string>*>* first_set);
        vector<string>* split_string(string production);
        bool valid_table;
        /*      [Non_Terminal][Terminal] -->    production      */
        unordered_map<pair<string,string>, string> parse_table;

};


#endif