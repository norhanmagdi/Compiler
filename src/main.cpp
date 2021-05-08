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
#include "include/NFA.h"

/* TODO */
/* 2a3adel l parser ennoh ygeeb postfix kolooo */
/* Postfix to automata solver */

int main() {
    Parser pars;
    map<string, vector<string>> REs = pars.parse();
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
                    stck.push(new NFA("AND", val1, val2));
                if (token == "|")
                    stck.push(new NFA("OR", val1, val2));
            }
        }
        cout << postfixExpr.fp << nLINE << SEPARATOR;
        (stck.top())->printNFA();
        cout << SEPARATOR;
    }
    return 0;
}

