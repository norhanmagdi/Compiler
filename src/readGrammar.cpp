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
    /* for(int i=0;i<lines.size();i++)
        cout<<lines[i]<<endl;*/
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
        grammar_set.back().second=grammar_set.back().second+" "+line.substr(0, string::npos);
    }

}
void readGrammar:: splitGrammar() {
   // cout<<endl;
  //  cout<<"new grammar"<<endl;
    for (const auto &g : grammar_set) {
       //  cout<<g.first<<" "<<g.second<<endl;
         pair <string,vector<string>> temp;
         temp.first=trim(g.first);
         string str="",terminal="";
         bool first=false;
         vector<string>rhs;
         string r=std::move(g.second);
        // cout<<r<<endl;
         for (auto i : r){
         //   cout<<i<<",";
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

    }
}
unordered_set<string> readGrammar::getTerminals(){
    return this->terminals;
}
unordered_set<string> readGrammar::getNonTerminals(){
    return this->non_terminals;
}
void readGrammar::setNonTerminals(unordered_set<string> t){
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


void readGrammar:: writeFile(vector<pair<string,vector<string>>> finalGrammar){
    ofstream myfile;
    myfile.open ("modified grammar.txt");
    for(const auto &g : finalGrammar){
            myfile<<g.first<<" = ";
            for(const auto &k : g.second){
                if(k==g.second.back())
                    myfile<<k<<"\n";
                else
                    myfile<<k<<" | ";
            }

    }
    myfile.close();
}
vector<pair<string,vector<string>>>readGrammar::solveLeftRecursion(pair<string,vector<string>> term) {
    vector<pair<string,vector<string>>>ans;
    pair<string,vector<string>> newTerm,modifiedTerm;
    newTerm.first=term.first+ "'";
    modifiedTerm.first=term.first;
    vector<string> newRHS,modifiedRHS;
    for(auto p: term.second){
//        cout<<"solving "<<p<<endl;
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
//        cout<<term.first<<",,"<<p<<endl;
        if(p.substr(0, p.find(' '))== term.first){
            return true;
        }
    }
    return false;
}
pair<string,vector<string>> readGrammar::indirectLeftRec(pair<string,vector<string>> termi,pair<string,vector<string>> termj) {
   // cout<<"replacement"<<termi.first<<termj.first<<endl;
    pair<string,vector<string>> newTerm,modifiedTerm;
    newTerm.first=termi.first;
    vector<string> newRHS;
    vector<string>temp = termi.second;
    for(auto p : temp){
        if(p.substr(0, p.find(' '))== termj.first){
            p=trim(p.erase(0,p.find(' ')));
          //  cout<<"p"<<p<<endl;
           // newRHS.push_back(p+" "+newTerm.first);
            for(auto pr : termj.second){
              //  cout<<pr+" "+p<<endl;
                newRHS.push_back(pr+" "+p);
            }

        }else{
            newRHS.push_back(p);
           // cout<<p<<endl;
        }
    }
    newTerm.second=newRHS;
    return newTerm;
}
void readGrammar::leftRecursion( vector<pair<string,vector<string>>> terms) {
    vector<pair<string,vector<string>>>result{};
    pair<string,vector<string>> newTerm;
    for(int i = 0; i < terms.size();i++){
        newTerm=terms[i];
        for(int j = 0; j < i;j++){
            if(containLeftRecursion(terms[j])){
                vector<pair<string,vector<string>>>ans=solveLeftRecursion(terms[j]);
                newTerm=indirectLeftRec(newTerm,ans[0]);

            }else{
                newTerm=indirectLeftRec(newTerm,terms[j]);
            }

        }
        //result.push_back(terms[i]);
        if(containLeftRecursion(newTerm)){
            vector<pair<string,vector<string>>>ans=solveLeftRecursion(newTerm);
            result.insert(result.end(), ans.begin(), ans.end());
        }else{
            result.push_back(newTerm);
        }
    }
    setLeftRecGrammar(result);
}
bool readGrammar::containLeftFactoring(pair<string,vector<string>> term){
    set<string> firstTerms;
    for(auto p: term.second){
        string t=p.substr(0, p.find(' '));
        if(firstTerms.find(t)!= firstTerms.end()){
            return true;
        }else {
            firstTerms.insert(t);
        }
    }
    return false;
}
vector<pair<string,vector<string>>>readGrammar::solveLeftFactoring(pair<string,vector<string>> term) {
    vector<pair<string,vector<string>>>ans;
    unordered_map<string,vector<string>> repeatedTerms;
    set<string> firstTerms;
    pair<string,vector<string>> modifiedTerm,extraTerm;
    modifiedTerm.first=term.first;
    vector<string> modifiedRHS;

    for(auto p: term.second){
        string t=p.substr(0, p.find(' '));
        if(firstTerms.find(t)!= firstTerms.end()){
            if(trim(p)==t)
                p="eps";
            else
                p=trim(p.erase(0,p.find(' ')));
            repeatedTerms[t].push_back(p);

        }else {
            firstTerms.insert(t);
            string np;
            if(trim(p)==t)
                np="eps";
            else
                np=trim(p.erase(0,p.find(' ')));
            vector<string> temp={np};
            repeatedTerms.insert({t,temp});
        }

    }
 /*   cout<<"first terms:"<<endl;
    for(auto i: firstTerms){
        cout<<i<<",,";
    }
     cout<<"repeat terms:"<<endl;
    for(auto i: repeatedTerms){
        cout<<i.first<<"::";

        for(auto j: i.second){
            cout<<j<<",,";
        }
        cout<<endl;
    }*/
    for(auto i: repeatedTerms){
            if(i.second.size()==1){
                if(i.second[0]=="eps")
                    modifiedRHS.push_back(i.first);
                else
                    modifiedRHS.push_back(i.first+" "+i.second[0]);

            }else{
                string temp=trim(i.second[0].substr(0, i.second[0].find(' ')));
                int c=0;
                for(auto j:i.second){
                    if(trim(j.substr(0, j.find(' ')))==temp)
                        c++;
                }
                if(c==i.second.size()){
                    vector<string> ve;
                    for(auto j :i.second)
                        ve.push_back(trim(j.erase(0,j.find(' '))));
                    i.second=ve;
                    temp=" "+temp+" ";
                }else
                    temp=" ";
                vector<string>extraRHS;
                extraTerm.first=term.first+"'";
                non_terminals.insert(extraTerm.first);
                for(int i=0;i<ans.size();i++)
                    extraTerm.first=extraTerm.first+"'";
                for(auto j: i.second)
                    extraRHS.push_back(j);
                modifiedRHS.push_back(i.first+temp+extraTerm.first);
                extraTerm.second=extraRHS;

                if(containLeftFactoring(extraTerm)){
                    vector<pair<string,vector<string>>> extraAns=solveLeftFactoring(extraTerm);
                    ans.insert(ans.end(), extraAns.begin(), extraAns.end());
                }else
                    ans.push_back(extraTerm);

            }


    }
    modifiedTerm.second=modifiedRHS;
    ans.insert(ans.begin(),modifiedTerm);
    return ans;
}
void readGrammar::leftFactoring( vector<pair<string,vector<string>>> terms) {

    vector<pair<string,vector<string>>>result{};
    for(int i = 0; i < terms.size();i++){
        if(containLeftFactoring(terms[i])){
            vector<pair<string,vector<string>>>ans=solveLeftFactoring(terms[i]);
            result.insert(result.end(), ans.begin(), ans.end());

        }else{
            result.push_back(terms[i]);
        }

    }

   setModifiedGrammar(result);
   setFirstNonTerminal(result.front().first);
}
vector<pair<string,vector<string>>>readGrammar::getLeftRecGrammar(){
    return this->leftRecGrammar;
}
void readGrammar::setLeftRecGrammar(vector<pair<string,vector<string>>> leftRecGrammar){
    this->leftRecGrammar=leftRecGrammar;
}
vector<pair<string,vector<string>>>readGrammar::getModifiedGrammar(){
    return this->modifiedGrammar;
}

void readGrammar::setModifiedGrammar(vector<pair<string,vector<string>>> modifiedGrammar){
    this->modifiedGrammar=modifiedGrammar;
}
string readGrammar::getFirstNonTerminal(){
    return this->firstNonTerminal;
}
void readGrammar::setFirstNonTerminal(string fnt){
    this->firstNonTerminal=fnt;
}
