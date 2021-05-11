//
// Created by hp on 10/05/2021.
//

#include "../include/Convertor.h"


Convertor::~Convertor() {

}

NFA *Convertor::toNFA(const map<string, vector<string>>& RR) {
    vector<NFA*> mergedNFAS;
    for (const auto& postfixExpr : RR) {
        stack<NFA *> stck;
        vector<string> postfix = postfixExpr.second;
//        cout << postfixExpr.first << '\n';
        for (const auto& token : postfix) {
//            cout << token;
            if (global->RE_SYMPOLS.find(token) == global->RE_SYMPOLS.end()) {
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
        cout << '\n';
        (stck.top())->setTokenName(postfixExpr.first);
        mergedNFAS.push_back(stck.top());
//        stck.top()->printNFA();
        stck.pop();
    }
    NFA* merged = new NFA(mergedNFAS);
    return merged;
}

