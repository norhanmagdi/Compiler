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

/* TODO */
/* 2a3adel l parser ennoh ygeeb postfix kolooo */
/* Postfix to automata solver */


int main() {
    Parser pars;
    GLOBAL *global = global->getInstance();
    map<string, vector<string>> REs = pars.parse();
    map<string, vector<string>> RDs = global->RDs;
    cout << "Parsing done \n";
    Convertor conv;
    NFA* merged = conv.toNFA(RDs);
    merged->printNFA();
    DFA* dfa = new DFA(merged);
    dfa->printDFATable();

//    Scanner* sc = new Scanner (new DFA());
//    cout << "From scanner\n";
//    string inp = "k";
//    sc->scanInput((string &) inp);

    vector<NFA*> mergedNFAS;
    /*
    for (auto postfixExpr : REs) {
        stack<NFA *> stck;
        vector<string> postfix = postfixExpr.sp;
        cout << postfixExpr.fp << nLINE;
        for (auto token : postfix) {
            cout << token;
            if (pars.RE_SYMPOLS.find(token) == pars.RE_SYMPOLS.end()) {
                stck.push(new NFA("SINGLE", token));
                continue;
            }

            NFA *val1 = stck.top();
            stck.pop();
            if (token == "+")
                stck.push(new NFA("PCLOSURE", val1));
            else if (token == "*")
                stck.push(new NFA("CClosure", val1));
            else {
                NFA *val2 = stck.top();
                stck.pop();
                if (token == "$")
                    stck.push(new NFA("AND", val2, val1));
                if (token == "|")
                    stck.push(new NFA("OR", val1, val2));
                if (token == "^")
                    stck.push(new NFA ("RANGE", val1, val2));
            }
        }
        cout << nLINE;
        (stck.top())->setTokenName(postfixExpr.fp);
        mergedNFAS.push_back(stck.top());
        stck.pop();
    }
    NFA* merged = new NFA(mergedNFAS);
//    merged->printNFA();

    DFA* dfa = new DFA(merged);
    dfa->printDFATable();
     */
   /* for (auto postfixExpr : RDs) {
        stack<NFA *> stck;
        vector<string> postfix = postfixExpr.sp;
        cout << postfixExpr.fp << nLINE;
        for (auto token : postfix) {
            cout << token;
            if (pars.RE_SYMPOLS.find(token) == pars.RE_SYMPOLS.end()) {
                stck.push(new NFA("SINGLE", token));
                continue;
            }

            NFA *val1 = stck.top();
            stck.pop();
            if (token == "+")
                stck.push(new NFA("PCLOSURE", val1));
            else if (token == "*")
                stck.push(new NFA("CClosure", val1));
            else {
                NFA *val2 = stck.top();
                stck.pop();
                if (token == "$")
                    stck.push(new NFA("AND", val2, val1));
                if (token == "|")
                    stck.push(new NFA("OR", val1, val2));
                if (token == "^")
                    stck.push(new NFA ("RANGE", val2, val1));
            }
        }
        cout << nLINE;
        (stck.top())->setTokenName(postfixExpr.fp);
        mergedNFAS.push_back(stck.top());
        stck.top()->printNFA();
        stck.pop();
    }*/
//    NFA* merged = new NFA(mergedNFAS);
//    merged->printNFA();
//    DFA* dfa = new DFA(merged);
//    dfa->printDFATable();
    return 0;
}

