#include "../include/LL1_parser.h"
#include <stack>

LL1_parser:: LL1_parser(string first_NonTerminal, vector<pair<string,vector<string>>>* Grammar, unordered_set<string>* Terminals, unordered_set<string>* Nonterminals){

    //initialize pointer to first non terminal
    this->frist_nonterminal = first_NonTerminal;
    this->valid_parser = true;

    //Initialize the object that creates first and follow sets used in the creation of the table
    ParseTable * foundation_of_table = new ParseTable(*Terminals,*Nonterminals,*Grammar,first_NonTerminal);            
    unordered_map<string,unordered_set<string>> first_set = foundation_of_table->getFirstSet();
    unordered_map<string,unordered_set<string>> follow_set = foundation_of_table->getFollowSet();

    cout << endl;
    cout << "Productions " << endl;

    for(auto x: *Grammar){
        cout << x.first << " --> ";
        for(auto y : x.second){
            cout  << y << " | ";
        }
        cout  << endl;
    }

    cout << endl;
    cout << "First Set" << endl;        
    //for debugging
    foundation_of_table->print_firstSet();
    cout << "*************************" << endl;
    cout << endl;
    cout << "Follow Set" << endl;      
    foundation_of_table->print_followSet();
    cout << "*************************" << endl;

    //create parsing table and using first and follow sets, and the grammar. Then initialize a pointer to the created table.
    table * created_table = new table(first_set,follow_set,*Grammar,*Terminals);
    this->parseing_table = created_table;
    if(!this->parseing_table->is_valid()){
        cout<<"ERROR"<<endl;
        this->parseing_table->delete_table();
        delete(this->parseing_table);
        this->valid_parser = false;
            cout<<"Error: Grammar is not LL1, please modify grammar by removing any ambiguity from grammar."<<endl;
    }

    cout<< endl;
    cout << "Table" << endl;
    parseing_table->print_table();

    //initialize pointers to sets of terminals and nonterminals
    this->nonterminals = Nonterminals;
    this->terminals = Terminals;

}

vector<string> errors_vector;

bool LL1_parser:: validate_syntax(vector<string> input){

    //if grammar has ambiguity, the table is invalid and also the parser
    if(!valid_parser)
        return false;

    //Garantees that at the end of input stream there is a '$'
    int input_size = input.size();
    if(input.at(input_size-1) != "$"){
        input.push_back("$");
        input_size++;
    }

    //Initialize stack
    stack<string> parsing_stack;
    parsing_stack.push("$");
    parsing_stack.push(frist_nonterminal);

    int current_token = 0;

    bool error = false;

    while(parsing_stack.top() != "$" && current_token < input_size){
        //if top of the stack is a terminal
        if(terminals->find(parsing_stack.top()) != terminals->end()){
            if(parsing_stack.top() == input.at(current_token)){
                current_token++;
                parsing_stack.pop();
                errors_vector.push_back("match"); // Khadija
            }
            else{
                error = true;
                // Add the terminal
                errors_vector.push_back("mismatch"); // Khadija
                input.insert(input.begin(), parsing_stack.top()); // Khadija
            }
        }
            //if top of the stack is a non terminal
        else if(nonterminals->find(parsing_stack.top()) != nonterminals->end()){
            //get from the table the equavilent production of this nonterminal with the given terminal as input
            string production = parseing_table->get_production(parsing_stack.top(),input.at(current_token));
            if(production == "ERROR" || production == "synch"){
                error  = true;
                parsing_stack.pop(); // Khadija
                errors_vector.push_back("Synch"); // Khadija
                continue;
            }
            else if (production.empty()) { // Khadija
                error  = true; // Khadija
                errors_vector.push_back("Empty"); // Khadija
                continue;
            }
            cout<< parsing_stack.top()<<" --> "<<production<<endl;
            //pop non terminal
            parsing_stack.pop();

            //check that production is not epsilon, and add it to the stack
            if(production.compare("eps")){
                //add to the stack its possible production terms
                vector<string>* terms_of_production = split_string(production);
                for( int i = terms_of_production->size()-1 ; i >= 0 ; i-- ){
                    parsing_stack.push(terms_of_production->at(i));
                }
            }
        }
        else{
            cout<<"Error: Undefined term!"<<endl;
            return false;
        }
    }

    if(error){
        cout<<"Error: Could not match input."<<endl;
        return false;
    }

    cout<<"Process terminated successfully"<<endl;
    return true;
}

void LL1_parser::is_valid_input(vector<string> input){
    int i = 0;
    cout << "***** STARTING SYNTAX CHECKING BY TOKEN *****" << endl;
    for(auto token: input){

        i++;
        vector<string>* input_vector = split_string(token);
        cout << "TOKEN #" << i << " :- " << token << endl;
        bool passed = validate_syntax(*input_vector);
        if(!passed){
            cout << "PROCESS INTERRUPTED DUE TO INVALID INPUT" << endl;
            break;
        }

    }
    cout << "***** PROCESS TERMINATED *****" << endl;
}

void LL1_parser:: print_table(){
    if(this->valid_parser){
        this->parseing_table->print_table();
    }
}