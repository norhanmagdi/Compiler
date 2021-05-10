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
#include "include/DFA.h"

/* TODO */
/* 2a3adel l parser ennoh ygeeb postfix kolooo */
/* Postfix to automata solver */


int main() {
    Parser pars;
    pars.parse();
    map<string, vector<string>> REs = pars.parse();
    vector<NFA*> mergedNFAS;
    for (auto postfixExpr : REs) {
        stack<NFA *> stck;
        vector<string> postfix = postfixExpr.sp;
        cout << postfixExpr.fp << nLINE;
        for (auto token : postfix) {
            cout << token << nLINE;
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
        (stck.top())->setTokenName(postfixExpr.fp);
        mergedNFAS.push_back(stck.top());
        stck.pop();
    }
    NFA* merged = new NFA(mergedNFAS);
    merged->printNFA();
    DFA* dfa = new DFA(merged);
    GLOBAL *global = global->getInstance();
    cout << SEPARATOR;
    int numOfNodes = global->getNumNow();
    for (int i = 0; i < numOfNodes; ++i) {
        cout << "  " << i;
    }
    cout << '\n';
    for (int i = 0; i < numOfNodes; ++i) {
        cout << i << "  ";
        for (int j = 0; j < numOfNodes; ++j) {
            cout << " " << global->transitionTable[i][j] << "  ";
        }
        cout << '\n';
    }
    cout << SEPARATOR << SEPARATOR << nLINE;
    cout << "DFATABLE\n";
    dfa->printDFATable();

//    vector<NFA*> mergedNFAS;
//    GLOBAL *global = global->getInstance();
//    for (auto postfixExpr : pars.postfixRDs) {
//        stack<NFA *> stck;
//        vector<string> postfix = postfixExpr.sp;
//        cout << "KK : " << postfixExpr.fp << nLINE;
//        for (auto token : postfix) {
//            cout << "HH " << token << nLINE;
//            if (pars.RE_SYMPOLS.find(token) == pars.RE_SYMPOLS.end()) {
//                cout << "single" << nLINE;
//                stck.push(new NFA("SINGLE", token));
//                continue;
//            }
//
//            NFA *val1 = stck.top();
//            stck.pop();
//            if (token == "+")
//                stck.push(new NFA("PCLOSURE", val1));
//            else if (token == "*")
//                stck.push(new NFA("CClosure", val1));
//            else {
//                NFA *val2 = stck.top();
//                stck.pop();
//                if (token == "$")
//                    stck.push(new NFA("AND", val2, val1));
//                if (token == "|") {
//                    cout << "BBBBBBBBBBBBBBBBB\n";
//                    stck.push(new NFA("OR", val1, val2));
//                    cout << "ORED" << '\n';
//                }
//                if (token == "^") {
//                    cout << "LLLLLLLLLLLLLLLLLL\n";
//                    stck.push(new NFA("RANGE", val2, val1));
//                }
//
//            }
//        }
//        cout << "DONE" << '\n';
//        (stck.top())->setTokenName(postfixExpr.fp);
//        mergedNFAS.push_back(stck.top());
//        stck.pop();
//    }
//    NFA* mergedRD = new NFA(mergedNFAS);
//    mergedRD->printNFA();
//    DFA* dfaRD = new DFA(mergedRD);
//    cout << SEPARATOR;
//    int numOfNodes = global->getNumNow();
//    for (int i = 0; i < numOfNodes; ++i) {
//        cout << "  " << i;
//    }
//    cout << '\n';
//    cout << "Transition table \n";
//    for (int i = 0; i < numOfNodes; ++i) {
//        cout << i << "  ";
//        for (int j = 0; j < numOfNodes; ++j) {
//            cout << " " << global->transitionTable[i][j] << "  ";
//        }
//        cout << '\n';
//    }
    return 0;
}

