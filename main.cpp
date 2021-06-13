#include <bits/stdc++.h>
#include <regex>

#define SPACE " "
#define nLINE '\n'
#define SEPARATOR "--------------------------------------\n"
#define sp second
#define fp first

#include "include/Parser.h"
#include "include/Edge.h"
#include "include/Node.h"
#include "include/GLOBAL.h"
#include "include/NFA.h"
#include "include/Scanner.h"
#include "include/DFA.h"
#include "include/Convertor.h"
#include "include/Minimizer.h"
#include "include/readGrammar.h"
#include "include/LL1_parser.h"

/* TODO */
/* 2a3adel l parser ennoh ygeeb postfix kolooo */
/* Postfix to automata solver */


int main() {
    cout << "TO Parser\n";
    Parser pars;
    GLOBAL *global = global->getInstance();
    map<string, vector<string>> REs = pars.parse();
    map<string, vector<string>> RDs = global->RDs;
    cout << "Parsing done \n\n";
    set <string> ss;
    for (auto s : global->inputSymbols) {
        cout << s << '\n';
        if (s == "\\=") {
            cout << "lllllll " << s << nLINE;
        }
        if (s[0] == '\\') {
            cout << s ;
//            global->inputSymbols.erase(s);
            s = s.substr(1, string::npos);
            cout << " became " << s << '\n';
            ss.insert(s);
            cout << s << nLINE;
        }
        else ss.insert(s);
    }
    global->inputSymbols = set<string> (ss);
    cout << "***************************\n";
    for (auto s : global->inputSymbols) {
        cout << s << '\n';
    }
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

    cout << "Minimizer in\n";
    Minimizer* m = new Minimizer (RDDFA->DFATable);
    RDDFA->DFATable = m->minimize();
    RDDFA->printDFATable();
    cout << "Minimizer Done\n\n";

    cout << "Minimizer in\n";
    Minimizer* r = new Minimizer (rulesDFA->DFATable);
    rulesDFA->DFATable = r->minimize();
    rulesDFA->printDFATable();
    cout << "Minimizer Done\n\n";

    cout << "TO Scanner\n";
    Scanner* sc = new Scanner (rulesDFA, RDDFA);
    string inp = "TestProgram.in";
    vector<string> tokens = sc->scanInput((string &) inp);
    cout << "Scanning done \n\n";

    cout <<"read grammar file\n";
    readGrammar rg;
    rg.parseGrammar();
    vector<pair<string,vector<string>>> newgrammar =rg.get_splited_grammar_set();
    rg.leftRecursion(newgrammar);
    vector<pair<string,vector<string>>> leftRecGrammar=rg.getLeftRecGrammar();
    cout<<"after left recursion"<<endl;
    for(const auto &g : leftRecGrammar){
        cout<<g.first<<"::";
        for(const auto &k : g.second)
            cout<<k<<",,";
        cout<<endl;
    }

    cout<<"after modification"<<endl;
    rg.leftFactoring(leftRecGrammar);
    cout << "L MAIN DEH\n";
    unordered_set<string> nter=rg.getNonTerminals();
    unordered_set<string> ter=rg.getTerminals();
    vector<pair<string,vector<string>>> leftFacGrammar=rg.getModifiedGrammar();
    cout<<"grammar"<<endl;
    for(const auto &g : leftFacGrammar){
        cout<<g.first<<"::";
        for(const auto &k : g.second)
            cout<<k<<" | ";
        cout<<endl;

    }

    cout<<"non terminals are"<<endl;
    for (const auto &t : nter) {
        cout<<t<<endl;
    }

    cout<<"terminals are"<<endl;
    for (const auto &t : ter) {
        cout<<t<<endl;
    }
    string firstNonTerminal=rg.getFirstNonTerminal();
    cout<<"first non terminal is : "<<firstNonTerminal<<endl;
    rg.writeFile(leftFacGrammar);
    cout <<"read grammar done\n";

    LL1_parser* ll1Parser = new LL1_parser(firstNonTerminal, &leftFacGrammar, &ter, &nter);
//    ll1Parser->is_valid_input(tokens);

    return 0;
}

