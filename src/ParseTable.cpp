#include "../include/ParseTable.h"

ParseTable::ParseTable(unordered_set<string> terminals, unordered_set<string> non_terminals, 
    vector<pair<string, vector<string>>> split_grammar_set, string first_Nonterminal){ //constructor
    this->terminals = terminals;
    this->non_terminals = non_terminals;
    this->split_grammar_set = split_grammar_set;
    this->first_nonterminal = first_Nonterminal;

    this->not_marked = true;

    first();
    follow();

}

void ParseTable::first(){ //get first set of the grammar
    for (const auto& productions : split_grammar_set) { //each productions line of the grammar
        if (first_set.find(productions.first) == first_set.end()) { //if the first set not already done
            firstEach(productions); //get first set of the productions
        }
    }
    for (const auto& productions : split_grammar_set) { //each productions line of the grammar
        checkEps(productions); //check if it needs an eps in the first set
    }
}

void ParseTable::firstEach(const pair<string,vector<string>>& productions) { //get first set
    for (const auto& production:productions.second) { //for each production
        vector<string> elements = split(production); //split the production to strings
        if (elements[0] == "eps") { //if the production is eps
            if (first_set[productions.first].find(elements[0]) == first_set[productions.first].end()) { //if the first set doesn't already has eps
                first_set[productions.first].insert(elements[0]); //add eps
            }
        }
        else if (terminals.find(elements[0]) != terminals.end()) { //if the first of the production is terminal
            if (first_set[productions.first].find(elements[0]) == first_set[productions.first].end()) { //if the first set doesn't already has this terminal
                first_set[productions.first].insert(elements[0]); //add the terminal
            }
        }
        else if (non_terminals.find(elements[0]) != non_terminals.end()) { //if the first of the production is non terminal
            if (first_set.find(elements[0]) != first_set.end()) { //if there already is a first set for this non terminal
                for (const auto& element : first_set[elements[0]]) { //for each element already in the first set in this non terminal
                    if (first_set[productions.first].find(element) == first_set[productions.first].end()) { //if this element is not in the first set of the original non terminal
                        first_set[productions.first].insert(element); //add the element to the first set of the original non terminal
                    }
                }
            }
            else { //if the first set of this non terminal not calculated yet
                for (const auto& pair : split_grammar_set) { //for each pair in the grammar set
                    if (pair.first == elements[0]) { //if the LHS is the first
                        firstEach(pair); //calculate recursively the first set of this new non terminal before adding it to the original non terminal
                        if (first_set.find(elements[0]) != first_set.end()) { //if the first set of the non terminal exists
                            for (const auto& element : first_set[elements[0]]) { //for each element in the first set of that non terminal
                                if (first_set[productions.first].find(elements[0]) == first_set[productions.first].end()) { //if the element doesn't already exist in the first set
                                    first_set[productions.first].insert(element); //add the element
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
        else {
            //error
        }
    }
}

void ParseTable::checkEps(pair<string,vector<string>> productions){ //check if the first set is missing eps
    bool eps = false;
    vector<string> elements = split(productions.second[0]); //split the production to strings
    string first = elements[0]; //first element of the production
    while (non_terminals.find(first) != non_terminals.end()) { //loop until the first element is non terminal
        if (first_set[first].find("eps") != first_set[first].end()) { //if the first set of that non terminal has eps
            eps = true; //boolean that all non terminals has eps production yet
            for (auto set : split_grammar_set) { //for each set in the grammar set
                if (set.first == first) { //if the LHS equal to that first element
                    elements = split(set.second[0]); //split the production to strings
                    first = elements[0]; //the new first for the next loop
                    break;
                }
            }
        }
        else { //it doesn't have eps as a production
            eps = false;
            break;
        }
    }
    if (eps) { //that non terminal should have an eps
        if (first_set[productions.first].find("eps") == first_set[productions.first].end()) { //if it doesn't already have eps
            first_set[productions.first].insert("eps");//add it
        }
    }
}

void ParseTable::follow(){
    for (const auto& productions : split_grammar_set) {
        if(!productions.first.compare(this->first_nonterminal) && this->not_marked){
            follow_set[productions.first].insert("$");
            this->not_marked = false;
        }
        followOne(productions);
    }
    for (const auto& productions : split_grammar_set) {
        followTwo(productions);
    }
}

void ParseTable::followOne(const pair<string,vector<string>>& productions){
    for (const auto& production : productions.second) {
        vector<string> elements = split(production);
        for (int i = 0 ; i < elements.size()-1; i++) {
            if (non_terminals.find(elements[i]) != non_terminals.end()) {
                if (terminals.find(elements[i+1]) != terminals.end()) {
                    if (follow_set[elements[i]].find(elements[i+1]) == follow_set[elements[i]].end()) {
                        follow_set[elements[i]].insert(elements[i+1]);
                    }
                }
                else if (non_terminals.find(elements[i+1]) != non_terminals.end()) {
                    for (auto element : first_set[elements[i+1]]) {
                        if (element != "eps") {
                            follow_set[elements[i]].insert(element);
                        }
                    }
                }
            }
        }
    }
}

void ParseTable::followTwo(const pair<string,vector<string>>& productions){
    for (const auto& production : productions.second) {
        vector<string> elements = split(production);
        if (non_terminals.find(elements[elements.size()-1]) != non_terminals.end()) {
            for (auto element : follow_set[productions.first]) {
                if (follow_set[elements[elements.size()-1]].find(element) == follow_set[elements[elements.size()-1]].end()) {
                    follow_set[elements[elements.size()-1]].insert(element);
                }
            }
            bool eps = true;
            for (int i = elements.size()-2; i >= 0; i--) {
                if (!eps) {
                    break;
                }
                if(terminals.find(elements.at(i)) != terminals.end()){
                    eps = false;
                    continue;
                }
                else{
                    if(non_terminals.find(elements.at(i)) != non_terminals.end()){
                        if(first_set[elements.at(i+1)].find("eps") != first_set[elements.at(i+1)].end()){
                            for (auto element : follow_set[productions.first]) {
                                follow_set[elements[i]].insert(element);
                            }
                        }
                        else{
                            eps = false;
                            continue;
                        }
                    }
                    else{
                        eps = false;
                        continue;
                    }
                }  
            }
        }
    }
}

vector<string> ParseTable::split(string production){ //split by space
    vector<string> elements;
    elements.push_back("");
    for (auto ch : production) {
        if (ch == ' ') {
            elements.push_back("");
        }
        else {
            elements.back()+=ch;
        }
    }
    return elements;
}

unordered_map<string, unordered_set<string>> ParseTable::getFirstSet() {
    return this->first_set;
}

unordered_map<string, unordered_set<string>> ParseTable::getFollowSet() {
    return this->follow_set;
}