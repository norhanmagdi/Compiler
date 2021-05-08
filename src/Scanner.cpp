#include "Scanner.h"

Scanner::Scanner()
{
    //ctor
}

Scanner::~Scanner()
{
    //dtor
}
void Scanner::scanInput(string &inputFile){
    string line;
    ifstream file(inputFile + ".txt");
    vector<string>words{};
    while(getline(file, line)){
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());
        words.insert(words.end(), results.begin(), results.end());
    }
    for(string s : words){
       scanWord(s);
    }

}
void Scanner::scanWord(string word){
    Node* startNode = dfa->getStartState();
    Node* currentNode = startNode;
    Node* nullNode = new Node(global->getNum(), false);
    Node* finalNode = nullNode;
    string maxToken;
    vector<string>tokens;
    bool findToken=false;
    int first=0,last=0;
    for(int i=0;i<word.size();i++){
        currentNode = dfa(currentNode, word[i]);
        if(currentNode->isEndState()){
            maxToken=currentNode->getTokenName();
            last=i;
            findToken=true;
            finalNode = currentNode;
            if(i== word.size()- 1)
                tokens.push_back(maxToken);
        }else if(currentNode->getTokenName() == "null" && findToken ){
            string newString = word.substr(first,last-first+1);
            tokens.push_back(maxToken);
            first = last + 1;
            i = last;
            finalNode = nullNode;
            currentNode = startNode;
        }
    }
}
