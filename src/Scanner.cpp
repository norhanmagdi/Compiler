#include "Scanner.h"

Scanner::Scanner()
{
    //ctor
}

Scanner::~Scanner()
{
    //dtor
}
void Scanner::scanInput(string &inputFile,DFA* dfa){
    string line;
    ifstream file(inputFile + ".txt");
    vector<string>words{};
    while(getline(file, line)){
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());
        words.insert(words.end(), results.begin(), results.end());
    }
    for(string s : words){
       scanWord(s,DFA* dfa);
    }

}
vector<pair<string,string>> Scanner::scanWord(string word,DFA* dfa){
    Node* startNode = dfa->getStart();
    Node* currentNode = startNode;
    Node* nullNode = new Node(global->getNum(), false);
    Node* finalNode = nullNode;
    string maxToken;
    vector<pair<string,string>>tokens{};
    bool findToken=false;
    int first=0,last=0;
    string inputChar;
    for(int i=0;i<word.size();i++){
        inputChar.push_back(word[i]);
        currentNode = dfa->DFATabled[currentNode][inputChar];
        if(currentNode->isEndState()){
            maxToken=currentNode->getTokenName();
            last=i;
            findToken=true;
            finalNode = currentNode;
            if(i== word.size()- 1){
                string newString  =word.substr(first,last-first+1);
                tokens.push_back(newString ,maxToken);
            }

        }else if(currentNode->getTokenName() == "null" && findToken ){
            string newString = word.substr(first,last-first+1);
            tokens.push_back(newString ,maxToken);
            first = last + 1;
            i = last;
            finalNode = nullNode;
            currentNode = startNode;
        }
    }
    return tokens;
}

