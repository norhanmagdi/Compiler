#include <bits/stdc++.h>
#include <regex>

#define SPACE " "
#define nLINE '\n'
#define SEPARATOR "--------------------------------------\n"
#define sp second
#define fp first
#include "include/readGrammar.h"


/* TODO */
/* 2a3adel l parser ennoh ygeeb postfix kolooo */
/* Postfix to automata solver */


int main() {
    cout <<"read grammar file\n";
    readGrammar rg;
    rg.parseGrammar();


    vector<pair<string,vector<string>>> newgrammar =rg.get_splited_grammar_set();
    cout<<"split grammar is"<<endl;
    for(const auto &g : newgrammar){
            cout<<g.first<<"::";
            for(const auto &k : g.second)
                cout<<k<<",,";
            cout<<endl;

   }
   vector<pair<string,vector<string>>> leftRecGrammar=rg.leftRecursion(newgrammar);
    cout<<"recursion"<<endl;
    for(const auto &g : leftRecGrammar){
            cout<<g.first<<"::";
            for(const auto &k : g.second)
                cout<<k<<",,";
            cout<<endl;

   }
   set<string> nter=rg.getNonTerminals();
    cout<<"non terminals are"<<endl;
     for (const auto &t : nter) {
       cout<<t<<endl;
    }
    set<string> ter=rg.getTerminals();
    cout<<"terminals are"<<endl;
     for (const auto &t : ter) {
       cout<<t<<endl;
    }
    cout<<"after modification"<<endl;
     vector<pair<string,vector<string>>> leftFacGrammar=rg.leftFactoring(leftRecGrammar);
      for(const auto &g : leftFacGrammar){
            cout<<g.first<<"::";
            for(const auto &k : g.second)
                cout<<k<<" | ";
            cout<<endl;

   }
   rg.writeFile(leftFacGrammar);

    /*cout << "TO Parser\n";
    Parser pars;
    GLOBAL *global = global->getInstance();
    map<string, vector<string>> REs = pars.parse();
    map<string, vector<string>> RDs = global->RDs;
    cout << "Parsing done \n\n";
//    for (auto s : global->inputSymbols) {
//        if (s[0] == '\\') {
//            global->inputSymbols.erase(s);
//            s = s.substr(1, string::npos);
//            cout << s << '\n'
//            global->inputSymbols.insert(s);
//        }
//    }
//    for (auto s : global->inputSymbols) {
//        cout << s << '\n';
//    }
    cout << "RULES NFA\n";
    Convertor* conv = new Convertor();
    NFA* rulesNFA = conv->toNFA(REs);
    rulesNFA->printNFA();
    cout << "RULES NFA DONE\n\n";

    cout << "RD NFA\n";
    Convertor* conv2 = new Convertor();
    NFA*  RDNFA = conv2->toNFA(RDs);
    RDNFA->printNFA();
    cout << "RD NFA DONE\n\n";

    cout << "RD DFA\n";
    DFA* RDDFA = new DFA(RDNFA, global->RDinputSymbols);
    RDDFA->printDFATable();
    cout << "RD DFA DONE\n\n";

    cout << "RULES DFA\n";
    DFA* rulesDFA = new DFA(rulesNFA, global->inputSymbols);
    rulesDFA->printDFATable();
    cout << "RULES DFA DONE\n\n";


    cout << "TO Scanner\n";
    Scanner* sc = new Scanner (rulesDFA, RDDFA);
    string inp = "k";
    sc->scanInput((string &) inp);
    cout << "Scanning done \n\n";*/
    return 0;
}

