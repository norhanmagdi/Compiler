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
    string inp = "k";
    sc->scanInput((string &) inp);
    cout << "Scanning done \n\n";
    return 0;
}

