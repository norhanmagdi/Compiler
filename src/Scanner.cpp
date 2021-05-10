

#include "..\include\Scanner.h"

Scanner::Scanner(DFA* dfa)
{
    finalDFA = dfa;
    //ctor
}

Scanner::~Scanner()
{
    //dtor
}
void Scanner::scanInput(string &inputFile){
    string line;
    ifstream file("TestProgram.in");
    vector<string>words{};
    while(getline(file, line)){
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());
        words.insert(words.end(), results.begin(), results.end());
        // Replace eahc
    }
    for(string s : words){
        scanWord(s);
    }
}

vector<pair<string,string>> Scanner::scanWord(string word){
//    cout << "IN " << word << '\n';
    vector<pair<string,string>> V;
    for (const auto& keyWord : global->keyWords) {
        int i =0;
        if (word.find(keyWord) == 0) {
            if (word.length() == keyWord.length() ||
                (word.length() > keyWord.length() &&
                global->puncs.find(word[keyWord.length()]) != global->puncs.end())) {
                cout << "Found " << keyWord << '\n'; // Is keyword
                scanWord(word.substr(keyWord.length(), word.length()));
                return V;
            }
        }
    }

    for (auto pun : global->puncs) {
        int w = word.find(pun);
        if (w != string::npos) {
            string h;
            if (0 < w-1) {
                h = word.substr(0, w);
                if (!h.empty())
                    scanWord(h);
            }
            cout << "Found " << pun << '\n';
            if (w+1 < word.length()) {
                h = word.substr(w + 1, word.length());
                if (!h.empty())
                    scanWord(h);
            }
            return V;
        }
    }




//    Node* startNode = finalDFA->getStart();
//    Node* currentNode = startNode;
//    Node* nullNode = new Node(global->getNum(), false);
//    Node* finalNode = nullNode;
//    string maxToken;
//    vector<pair<string,string>>tokens{};
//    bool findToken=false;
//    int first=0,last=0;
//    string inputChar;
//    for(int i=0;i<word.size();i++){
//        inputChar.push_back(word[i]);
//        currentNode = finalDFA->DFATable[currentNode][inputChar];
//        if(currentNode->isEndState()){
//            maxToken=currentNode->getTokenName();
//            last=i;
//            findToken=true;
//            finalNode = currentNode;
//            if(i == word.size()- 1){
//                string newString  =word.substr(first,last-first+1);
//                tokens.push_back(make_pair(newString ,maxToken));
//            }
//
//        }else if(currentNode->getTokenName() == "null" && findToken ){
//            string newString = word.substr(first,last-first+1);
//            tokens.push_back(make_pair(newString ,maxToken));
//            first = last + 1;
//            i = last;
//            finalNode = nullNode;
//            currentNode = startNode;
//        }
//    }
    return tokens;
}
