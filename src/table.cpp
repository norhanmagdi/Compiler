#include <vector>
#include "table.h"

/* The creation of the table happens in the constructor of this class. */
table::table(unordered_map<string, unordered_set<string>*>* first_set, unordered_map<string, unordered_set<string>*>* follow_set,
    vector<pair<string,vector<string>*>>* Grammar, unordered_set<string>* Terminals){
        this->valid_table = true;
        //First step: transform Grammar into a map in ordered to make it easier to search for keys
        unordered_map<string,vector<string>*>* gram = new unordered_map<string,vector<string>*>();
        for(auto grammar_rule: *Grammar){
            gram->insert(grammar_rule);
        }

        //Second step: we need to go through all the elements of the first_set and fill the table with the suitable production rule
        for(auto entry_in_first_set: *first_set){
            if(gram->find(entry_in_first_set.first) == gram->end()){
                cout << "ERROR" << endl;
                this->valid_table = true;
                break;
            }
            vector<string>* vector_of_productions = (gram->find(entry_in_first_set.first))->second;
            for(auto terminal: *entry_in_first_set.second){
                for(auto production: *vector_of_productions){
                    //if terminal comes from this production add them to the table
                    if(terminal != "eps" && check_terminal_production(terminal,production,entry_in_first_set.first,Terminals,first_set)){
                        pair pair = make_pair(entry_in_first_set.first,terminal);
                        if(parse_table.find(pair) != parse_table.end()){
                            /*
                            This cell in the table already has a value, hence ambiguous grammar -Not LL(1)-.
                            */
                           cout<< "ERROR" << endl;
                           this->valid_table = true;
                           break;
                        }
                        this->parse_table[pair] = production;
                    }
                    //if terminal t is epsilon,then for each terminal in follow set combine it with nonterminal n and give them this production in the table  
                    if(terminal == "eps"){
                        for(auto terminal_in_follow_set : *(follow_set->find(entry_in_first_set.first))->second){
                            pair pair = make_pair(entry_in_first_set.first,terminal_in_follow_set);
                            if(parse_table.find(pair) != parse_table.end()){
                                /*
                                This cell in the table already has a value, hence ambiguous grammar -Not LL(1)-.
                                */
                                cout<< "ERROR" << endl;
                                this->valid_table = true;
                                break;
                            }
                            this->parse_table[pair] = "eps";
                        }
                    }
                }
            }
        }
}

bool table:: check_terminal_production(string terminal, string production,string nonterminal, unordered_set<string>* Terminals, unordered_map<string, unordered_set<string>*>* first_set){
   int terminal_index = 0;
   int production_index = 0;
   vector<string>* terms_of_production = split_string(production);
   if(Terminals->find(terms_of_production->at(0)) != Terminals->end()){
        if(terminal == terms_of_production->at(0))
            return true;
        else 
            return false;
   }
   unordered_set<string>* nonTerminal_first_set = (first_set->find(nonterminal))->second;
   for(auto entry: *nonTerminal_first_set){
       if(entry == terminal)
        return true;
   }
   return false;
}

bool table:: is_valid(){
    return valid_table;
}

string table:: get_production(string nonterminal, string terminal){
    pair pair = make_pair(nonterminal,terminal);
    if(parse_table.find(pair) == parse_table.end()){
        return "ERROR";
    }
    return parse_table.find(pair)->second;
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