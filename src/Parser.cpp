//
// Created by hp on 06/05/2021.
//

#include "../include/Parser.h"

using namespace std;

vector<string> RULES_SET;
set<string> keyWords;
set<char> puncs;
map<string ,string> REs;
map<string ,string> RDs;
vector<string> RDKeys;

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

    for (const auto& keyWord : keyWords){
        cout << keyWord << nLINE;
    }
}

void Parser:: save_puncs(const string& line){
    for (auto sym : MAIN_PUNCS){
        if (line.find(sym) != string::npos){
            puncs.insert(sym);
        }
    }
    for (auto keyWord : puncs){
        cout << keyWord << nLINE;
    }
}

void Parser:: save_RE (const string& line , int sep_indx){
    string name = line.substr(0, sep_indx);
    string expr = line.substr(sep_indx + 1, string::npos);
    name.erase(remove(name.begin(), name.end(), ' '), name.end());
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    REs[name] = expr;
    for (const auto& pr : REs)
        cout << pr.fp << SPACE << SPACE << pr.sp << nLINE;
}

void Parser:: save_RD (const string& line , int sep_indx){
    string name = line.substr(0, sep_indx);
    string expr = line.substr(sep_indx + 1, string::npos);
    name.erase(remove(name.begin(), name.end(), ' '), name.end());
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());

    RDKeys.push_back(name);
    RDs[name] = expr;
    for (const auto& pr : RDs)
        cout << pr.fp << SPACE << SPACE << pr.sp << nLINE;
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

void Parser:: parse(){
    read_file();
    for(const auto& line : RULES_SET){
        cout << line << nLINE;
        parse_Line(line);
        cout << SEPARATOR;cout << SEPARATOR;cout << SEPARATOR;
    }
    cout << SEPARATOR;cout << SEPARATOR;cout << SEPARATOR;
    vector<string> h = divide_RE("digit+|digit+.digits(\\L|Edigits)");
    cout << SEPARATOR;cout << SEPARATOR;cout << SEPARATOR;
    to_postfix(h);
    cout << SEPARATOR;cout << SEPARATOR;cout << SEPARATOR;
}

bool Parser:: sort_by_length(const string& s1, const string& s2){
    return s1.length() > s2.length();
}

vector<string> Parser:: divide_RE (string re){
    vector<string> expressionTokens;
    vector<string> expression(re.size());

    sort(RDKeys.begin(), RDKeys.end(), sort_by_length);
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
        cout << s << nLINE;
        if (!expressionTokens.empty() &&
            expressionTokens[expressionTokens.size()-1] != "|" &&
            expressionTokens[expressionTokens.size()-1] != "-" &&
            expressionTokens[expressionTokens.size()-1] != ")" &&
            expressionTokens[expressionTokens.size()-1] != "(" &&
            RE_SYMPOLS.find(s) == RE_SYMPOLS.end())

            expressionTokens.emplace_back("$");

        expressionTokens.push_back(s);
    }
    for (const auto& token : expressionTokens) {
        cout << token << nLINE;
    }

    return expressionTokens;
}

vector<string> Parser:: to_postfix(const vector<string>& exprVec){
    stack <string> stk;
    stk.push("#");
    vector<string> postfix;

    for(const auto& it : exprVec) {
        cout << it << nLINE;
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
            cout << "STCK TOP" << stk.top() << "OTH" << it << nLINE;
            if(PRECEDENCE[it] > PRECEDENCE[stk.top()])
                stk.push(it);
            else {
                cout << "HERE" << nLINE;
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
    cout << "OUTPUT" << nLINE;
    for (const auto& po : postfix) {
        cout << po << nLINE;
    }
    return postfix;
}
