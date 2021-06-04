#include "readGrammar.h"
#include <bits/stdc++.h>

using namespace std;

vector<string> lines;
vector<pair<string,string>> grammar_set;
//vector<pair<string,vector<string>>> splited_grammar_set;
int i=0;
std::string trim(const std::string &s)
{
    auto start = s.begin();
    while (start != s.end() && std::isspace(*start)) {
        start++;
    }

    auto end = s.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}
void readGrammar:: readFile(){
     freopen ("grammar.txt","r",stdin);
     string input;
     while (getline(std::cin,input))
        lines.push_back(trim(input));
     for(int i=0;i<lines.size();i++)
        cout<<lines[i]<<endl;
}
void readGrammar:: parseLine(string line) {
    if (line[0]=='#'){
        pair <string,string> temp;
        int sepIndx=0;
        while(sepIndx<line.size()&&line[sepIndx]!='=')
            sepIndx++;
        temp.first=line.substr(1, sepIndx-1);
        temp.second=line.substr(sepIndx+1, string::npos);
        non_terminals.insert(trim(temp.first));
        grammar_set.push_back(temp);
    }else{
        grammar_set.back().second=grammar_set.back().second+" "+line.substr(1, string::npos);
    }

}
void readGrammar:: splitGrammar() {
    cout<<endl;
    cout<<"new grammar"<<endl;
    for (const auto &g : grammar_set) {
         cout<<g.first<<" "<<g.second<<endl;
         pair <string,vector<string>> temp;
         temp.first=trim(g.first);
         string str="",terminal="";
         bool first=false;
         vector<string>rhs;
         string r=std::move(g.second);
         cout<<r<<endl;
         for (auto i : r){
            cout<<i<<",";
            if(i=='\''&&!first){
               // cout<<"find ' at "<<i<<endl;
                first=true;
            }else if(i=='\''&&first){
                terminals.insert(trim(terminal));
                terminal="";
                first=false;
            }else if(i=='|'&&!str.empty()){
                if(str == "\\L"){
                    rhs.push_back("eps");
                }else{
                    rhs.push_back(trim(str));
                }
                str="";
            }else {
                if(first)
                    terminal+=i;
                str+=i;
            }
         }
         if(!str.empty())
            rhs.push_back(trim(str));
         temp.second=rhs;
         splited_grammar_set.push_back(temp);
        /* cout<<endl;
         for(const auto &g : splited_grammar_set){
            cout<<g.first<<endl;
            for(const auto &k : g.second)
                cout<<k<<endl;

         }
*/

    }
}
set<string> readGrammar::getTerminals(){
    return this->terminals;
}
set<string> readGrammar::getNonTerminals(){
    return this->non_terminals;
}
void readGrammar::setNonTerminals(set<string> t){
    this->non_terminals =t;
}
vector<pair<string,vector<string>>> readGrammar::get_splited_grammar_set(){
    return this->splited_grammar_set;
}
void readGrammar:: parseGrammar() {
    readFile();
    for (const auto &line : lines) {
        parseLine(line);
    }
    splitGrammar();

}


void readGrammar:: print(){
}
vector<pair<string,vector<string>>>readGrammar::solveLeftRecursion(pair<string,vector<string>> term) {
    vector<pair<string,vector<string>>>ans;
    pair<string,vector<string>> newTerm,modifiedTerm;
    newTerm.first=term.first+ "'";
    modifiedTerm.first=term.first;
    vector<string> newRHS,modifiedRHS;
    for(auto p: term.second){
        cout<<"solving "<<p<<endl;
        if(p.substr(0, p.find(' '))== term.first){
            p=trim(p.erase(0,p.find(' ')));
            newRHS.push_back(p+" "+newTerm.first);
            non_terminals.insert(trim(newTerm.first));


        }else if(p!="eps"){
            modifiedRHS.push_back(p+" "+newTerm.first);

        }
    }
    newRHS.push_back("eps");
    newTerm.second=newRHS;
    modifiedTerm.second=modifiedRHS;
    ans.push_back(modifiedTerm);
    ans.push_back(newTerm);
    return ans;
}

bool readGrammar::containLeftRecursion(pair<string,vector<string>> term) {
    for(auto p: term.second){
        cout<<term.first<<",,"<<p<<endl;
        if(p.substr(0, p.find(' '))== term.first){
            return true;
        }
    }
    return false;
}
pair<string,vector<string>> replaceProductionWith(pair<string,vector<string>> termi,pair<string,vector<string>> termj) {
    cout<<"replacement"<<termi.first<<termj.first<<endl;
    pair<string,vector<string>> newTerm,modifiedTerm;
    newTerm.first=termi.first;
    vector<string> newRHS;
    vector<string>temp = termi.second;
    for(auto p : temp){
        if(p.substr(0, p.find(' '))== termj.first){
            p=trim(p.erase(0,p.find(' ')));
            cout<<"p"<<p<<endl;
           // newRHS.push_back(p+" "+newTerm.first);
            for(auto pr : termj.second){
                cout<<pr+" "+p<<endl;
                newRHS.push_back(pr+" "+p);
            }

        }else{
            newRHS.push_back(p);
            cout<<p<<endl;
        }
    }
    newTerm.second=newRHS;
    return newTerm;
}
vector<pair<string,vector<string>>> readGrammar::leftRecursion( vector<pair<string,vector<string>>> terms) {
    vector<pair<string,vector<string>>>result{};
    pair<string,vector<string>> newTerm;
    for(int i = 0; i < terms.size();i++){
        newTerm=terms[i];
        for(int j = 0; j < i;j++){
            cout<<i<<j<<endl;
            cout<<terms[i].first<<endl;
            cout<<terms[j].first<<endl;
            newTerm=replaceProductionWith(terms[i],terms[j]);
            cout<<"new"<<newTerm.second[1]<<endl;
        }
        //result.push_back(terms[i]);
        if(containLeftRecursion(newTerm)){
            cout<<"find the recursion"<<endl;
            vector<pair<string,vector<string>>>ans=solveLeftRecursion(newTerm);

        result.push_back(ans[0]);
        result.push_back(ans[1]);
        }else{
            result.push_back(newTerm);
        }
    }
    return result;
}
