//
// Created by hp on 06/05/2021.
//

#include "../include/Parser.h"

using namespace std;

vector<string> RULES_SET;
set<char> puncs;
map<string ,string> REs;
map<string ,string> RDs;
vector<string> RDKeys;
set<string> keyWords;

void Parser:: read_file(){
    freopen(RULES_FILE, "r", stdin);
    string input;
    while (getline(std::cin,input)){
        RULES_SET.push_back(input);
    }
}

void Parser:: save_keyWords(string line){
    line.erase(remove(line.begin(), line.end(), '{'), line.end());
    line.erase(remove(line.begin(), line.end(), '}'), line.end());
    stringstream ss(line);
    while (ss >> line)
        keyWords.insert(line);
}

void Parser:: save_puncs(const string& line){
    for (auto sym : MAIN_PUNCS){
        if (line.find(sym) != string::npos){
            puncs.insert(sym);
        }
    }
}

void Parser:: save_RE (const string& line , int sep_indx){
    string name = line.substr(0, sep_indx);
    string expr = line.substr(sep_indx + 1, string::npos);
    name.erase(remove(name.begin(), name.end(), ' '), name.end());
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    REs[name] = expr;
}

void Parser:: save_RD (const string& line , int sep_indx){
    string name = line.substr(0, sep_indx);
    string expr = line.substr(sep_indx + 1, string::npos);
    name.erase(remove(name.begin(), name.end(), ' '), name.end());
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
    replace( expr.begin(), expr.end(), '-', '^' );

    RDKeys.push_back(name);
    RDs[name] = expr;

}

void Parser:: parse_Line(string line){
    if (line[0] == '[') {
        cout << "Punctuations" << nLINE;
        save_puncs(line);
        return;
    }
    if (line[0] == '{') {
        cout << "KeyWord" << nLINE;
        save_keyWords(line);
        return;
    }
    int indx = 0;
    while ( indx < line.size() &&
            ((line[indx] >= 'a' && line[indx] <= 'z') ||
             (line[indx] >= 'A' && line[indx] <= 'Z')) ) indx ++;
    while (indx < line.size() && line[indx] == ' ') indx++;
    if (indx < line.size() && line[indx] == ':'){
        cout << "Regular Expression" << nLINE;
        save_RE (line, indx);
        return;
    }
    if (indx < line.size() && line[indx] == '='){
        cout << "Regular Definition" << nLINE;
        save_RD(line, indx);
        return;
    }

    cout << "NON-VALID RULE" << nLINE;
}

map<string, vector<string>> Parser:: parse() {
    read_file();
    for (const auto &line : RULES_SET) {
        cout << line << nLINE;
        parse_Line(line);
        cout << nLINE;
    }
    cout << "READ DONE AND MAIN PARSING DONE" << nLINE;
    cout << "Regular Definitions\n" << SEPARATOR;
    for (const auto& pr : RDs)
        cout << pr.fp << SPACE << SPACE << pr.sp << nLINE;
    sort(RDKeys.begin(), RDKeys.end(), sort_by_length); // Sorting for dividing NOTE : (DIGIT VS DIGITS)
    cout << SEPARATOR;
    cout << "Regular Expressions\n" << SEPARATOR;
    for (const auto& pr : REs)
        cout << pr.fp << SPACE << SPACE << pr.sp << nLINE;
    cout << SEPARATOR;
    cout << "Keywords\n" << SEPARATOR;
    for (auto keyWord : keyWords)
        cout << keyWord << SPACE;
    cout << SEPARATOR;
    cout << "Symbols\n" << SEPARATOR;
    for (auto punc : puncs)
        cout << punc << SPACE;

    cout << nLINE << SEPARATOR;
    cout << SEPARATOR;
    cout << SEPARATOR;
    cout << SEPARATOR;


    cout << "FOR EXPRESSIONS" << nLINE;
    for (const auto& regExpr : REs) {
        vector<string> h = divide_RE(regExpr.sp);
        cout << regExpr.fp << nLINE;
        h = to_postfix(h);
        for (const auto& hh : h) {
            cout << hh << SPACE;
        }
        cout << nLINE;
        postfixREs[regExpr.fp] = h;
    }
    cout << "FOR DEFINITIONS" << nLINE;
    for (const auto& regDef : RDs) {
        vector<string> h = divide_RE(regDef.sp);
        cout << regDef.fp << nLINE;
        h = to_postfix(h);
        for (const auto& hh : h) {
            cout << hh << SPACE;
        }
        cout << nLINE;
        postfixRDs[regDef.fp] = h;
    }
    cout << SEPARATOR;
    cout << SEPARATOR;
    cout << SEPARATOR;
    return postfixREs;
}

bool Parser:: sort_by_length(const string& s1, const string& s2){
    return s1.length() > s2.length();
}

vector<string> Parser:: divide_RE (string re){
    vector<string> expressionTokens;
    vector<string> expression(re.size());

    for(const auto& def : RDKeys){
        std::size_t found = re.find(def);
        while (found != string::npos){
            expression[found] = def;
            re[found] = '$';
            found = re.find(def);
        }
    }
    for (int i = 0; i < re.size(); ++i) {
        string s;
        if (!expression[i].empty()){
            s = expression[i];
            i += (int)expression[i].length() - 1;
        }
        else {
            if (re[i] == '\\') {
                s = re[i];
                s += re[++i];
            } else {
                s += re[i];
            }
        }
        if (!expressionTokens.empty() &&
            expressionTokens[expressionTokens.size()-1] != "|" &&
            expressionTokens[expressionTokens.size()-1] != "^" &&
            expressionTokens[expressionTokens.size()-1] != ")" &&
            expressionTokens[expressionTokens.size()-1] != "(" &&
            RE_SYMPOLS.find(s) == RE_SYMPOLS.end())

            expressionTokens.emplace_back("$");

        expressionTokens.push_back(s);
    }
    return expressionTokens;
}

vector<string> Parser:: to_postfix(const vector<string>& exprVec){
    stack <string> stk;
    stk.push("#");
    vector<string> postfix;

    for(const auto& it : exprVec) {
        if(RE_SYMPOLS.find(it) == RE_SYMPOLS.end())
            postfix.push_back(it);
        else if (it == "(")
            stk.push(it);
        else if(it == ")"){
            while(stk.top() != "#" && stk.top() != "(") {
                postfix.push_back(stk.top());
                stk.pop();
            }
            stk.pop();          //remove the '(' from stack
        }
        else {
            if(PRECEDENCE[it] > PRECEDENCE[stk.top()])
                stk.push(it);
            else {
                while(stk.top() != "#" && PRECEDENCE[it] <= PRECEDENCE[stk.top()]) {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                stk.push(it);
            }
        }
    }
    while(stk.top() != "#") {
        postfix.push_back(stk.top());
        stk.pop();
    }
    return postfix;
}
