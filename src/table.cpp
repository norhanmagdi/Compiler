#include <vector>
#include "../include/table.h"

/* The creation of the table happens in the constructor of this class. */
table::table(unordered_map<string, unordered_set<string>> first_set, unordered_map<string, unordered_set<string>> follow_set,
             vector<pair<string,vector<string>>> Grammar, unordered_set<string> Terminals){
    this->valid_table = true;
    //First step: transform Grammar into a map in ordered to make it easier to search for keys
    unordered_map<string,vector<string>> * gram = new unordered_map<string,vector<string>>();
    for(auto grammar_rule: Grammar){
        gram->insert(grammar_rule);
    }

    //Second step: we need to go through all the elements of the first_set and fill the table with the suitable production rule
    for(auto entry_in_first_set: first_set){
        if(gram->find(entry_in_first_set.first) == gram->end()){
            cout << "ERROR1: Invalid term to grammar." << endl;
            this->valid_table = false;
            break;
        }
        vector<string> vector_of_productions = (gram->find(entry_in_first_set.first))->second;
        bool has_epsilon = false;
        for(auto terminal: entry_in_first_set.second){
            bool found = false;
            for(auto production: vector_of_productions){
                //if terminal comes from this production add them to the table
                if(terminal.compare("eps") && production.compare("eps") && check_terminal_production(terminal,production,Terminals)){
                    pair<string,string> p = make_pair(entry_in_first_set.first,terminal);
                    if(parse_table.find(p) != parse_table.end()){
                        /*
                        This cell in the table already has a value, hence ambiguous grammar -Not LL(1)-.
                        */
                        cout << entry_in_first_set.first << "+" << terminal <<" --> " <<parse_table[p] << " but also " << production << endl;  
                        cout<< "ERROR2: Multiple parsing paths detected. Not LL1." << endl;
                        this->valid_table = false;
                        break;
                    }
                    this->parse_table[p] = production;
                    found = true;
                    break;
                }
                //if terminal t is epsilon,then for each terminal in follow set combine it with nonterminal n and give them this production in the table
                if(!production.compare("eps")){
                    has_epsilon = true;
                }
            }
            if(!found){
                for(auto production: vector_of_productions){
                //if terminal comes from this production add them to the table
                if(terminal.compare("eps") && production.compare("eps") && check_nonterminal_production(terminal,entry_in_first_set.first,first_set)){
                    pair<string,string> p = make_pair(entry_in_first_set.first,terminal);
                    if(parse_table.find(p) != parse_table.end()){
                        break;
                    }
                    this->parse_table[p] = production;
                    found = true;
                    break;
                }
            }
        }
    }
        if(has_epsilon){
            for(auto terminal_in_follow_set : (follow_set.find(entry_in_first_set.first))->second){
                pair<string,string> p = make_pair(entry_in_first_set.first,terminal_in_follow_set);
                if(parse_table.find(p) != parse_table.end()){
                    /*
                    This cell in the table already has a value, hence ambiguous grammar -Not LL(1)-.
                    */
                    cout<< "ERROR3: Multiple parsing paths detected. Not LL1." << endl;
                    this->valid_table = false;
                    break;
                }
                this->parse_table[p] = "eps";
            }
        }
        else{
            //for synchronization in case of error
            for(auto terminal_in_follow_set : (follow_set.find(entry_in_first_set.first))->second){
                pair<string,string> p = make_pair(entry_in_first_set.first,terminal_in_follow_set);
                if(parse_table.find(p) != parse_table.end()){
                    continue;
                }
                this->parse_table[p] = "synch";
            }
        }
    }
}

bool table:: check_terminal_production(string terminal, string production,unordered_set<string> Terminals){
    vector<string>* terms_of_production = split_string(production);
    if(Terminals.find(terms_of_production->at(0)) != Terminals.end()){
        if(!terminal.compare(terms_of_production->at(0)))
            return true;
        else
            return false;
    }
    return false;
}

bool table:: check_nonterminal_production(string terminal, string nonterminal, unordered_map<string, unordered_set<string>> first_set){
    unordered_set<string> nonTerminal_first_set = (first_set.find(nonterminal))->second;
    for(auto entry: nonTerminal_first_set){
        if(!entry.compare(terminal))
            return true;
    }
    return false;
}

bool table:: is_valid(){
    return valid_table;
}

string table:: get_production(string nonterminal, string terminal){
    pair<string,string> p = make_pair(nonterminal,terminal);
    if(parse_table.find(p) == parse_table.end()){
        return "ERROR: Empty cell in the table.";
    }
    return parse_table.find(p)->second;
}

vector<string>* split_string(string production){
    int index = 0;
    int size = production.size();
    vector<string>* array_of_terms = new vector<string>();
    while(index < size){
        string str = "";
        while(index < size && production.at(index) != ' '){
            str = str + production.at(index++);
        }
        if(str != ""){
            array_of_terms->push_back(str);
        }
        index++;
    }
    return array_of_terms;
}

void table:: print_table(){
    if(!this->valid_table){
        cout<< "Invalid table"<<endl;
        return;
    }

    for(auto entry: this->parse_table){
        cout << "[" << entry.first.first << "]" << "[" << entry.first.second << "]" << "-->" << entry.second << endl;
    }

}

void table:: delete_table(){
    delete(&this->parse_table);
    delete(&this->valid_table);
    delete(this);
}