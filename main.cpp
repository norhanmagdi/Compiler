#include <bits/stdc++.h>
#include <regex>

#define SPACE " "
#define nLINE '\n'
#define SEPARATOR "--------------------------------------\n"

using namespace std;

const char* RULES_FILE = "rules.in";
const set<char> RE_SYMPOLS = { '-' ,'|' ,'+' ,'*' ,'(' ,')'};
vector<string> RULES_SET;
set<string> keyWords;
set<string> puncs;

void read_file(){
    freopen(RULES_FILE, "r", stdin);
    string input;
    while (getline(std::cin,input)){
        RULES_SET.push_back(input);
    }
}

void save_keyWords(string line){
    line.erase(remove(line.begin(), line.end(), '{'), line.end());
    line.erase(remove(line.begin(), line.end(), '}'), line.end());
    stringstream ss(line);
    while (ss >> line)
        keyWords.insert(line);

    for (auto keyWord : keyWords){
        cout << keyWord << nLINE;
    }
}

void parse(string line){
    if (line[0] == '[') {
        cout << "Punctuations" << nLINE;
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
        return;
    }
    if (indx < line.size() && line[indx] == '='){
        cout << "Regular Definition" << nLINE;
        return;
    }

    cout << "NON-VALID RULE" << nLINE;
}

int main() {
    read_file();
    for(auto line : RULES_SET){
        cout << line << nLINE;
        parse(line);
        cout << SEPARATOR;
    }

    return 0;
}
