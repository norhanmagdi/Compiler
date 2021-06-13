

#include "..\include\Scanner.h"

Scanner::Scanner(DFA* rulesDFA, DFA* RDDFA)
{
    Scanner::rulesDFA = rulesDFA;
    Scanner::rulesDFATable = rulesDFA->DFATable;
    Scanner::RDDFA = RDDFA;
    Scanner::RDDFATable = RDDFA->DFATable;
    //ctor
}

Scanner::~Scanner()
{
    //dtor
}
vector<string> Scanner::scanInput(string &inputFile){
    string line;
    ifstream file(inputFile);
    vector<string>words{};
    while(getline(file, line)){
        istringstream iss(line);
        vector<string> results((istream_iterator<string>(iss)),istream_iterator<string>());
        words.insert(words.end(), results.begin(), results.end());
        // Replace eahc
    }
    for(string s : words){
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        string scanned = scanWord(s);
        if (scanned != "") {
            tokens.push_back(scanned);
        }
    }
    return tokens;
}
vector<string> inputString;
const pair<Node*, int> NULLACCEPTING = {nullptr, -1};
pair<Node*, int> acceptRD = NULLACCEPTING;
vector<bool> visitedNode(1000, false);
pair<Node*, int> acceptingRE = NULLACCEPTING;

string Scanner::scanWord(string word){

    word.erase(remove(word.begin(), word.end(), ' '), word.end());
    if (word.empty()) return "";
    for (const auto& keyWord : global->keyWords) {
        if (word.find(keyWord) == 0) {
            if (word.length() == keyWord.length() ||
                (word.length() > keyWord.length() &&
                global->puncs.find(word[keyWord.length()]) != global->puncs.end())) {
                cout << "Found " << keyWord << '\n'; // Is keyword
                scanWord(word.substr(keyWord.length(), word.length()));
                return keyWord;
            }
        }
    }

    for (auto pun : global->puncs) {
        int w = word.find(pun);
        if (w != string::npos) {
            string h;
            if (0 < w) {
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
            return string(1, pun);
        }
    }

    inputString.clear();
    toStrinsVector(word);
    pair<Node *, int> accepted = make_pair(new Node(-1, false), 0);
    if (!inputString.empty()) {
        visitedNode = vector<bool> (1000,false);
        acceptingRE = NULLACCEPTING;
        accepted = checkRE(rulesDFA->getStart(), 0);
        if (accepted != NULLACCEPTING) {
            cout << "Found " << accepted.first->getTokenName() << '\n';
        }
    }
    return accepted.first->getTokenName();
}
// Maximal munch
pair<Node*, int> Scanner::checkRE (Node* current, int inputIndx) {
    if (current == nullptr) return acceptingRE;
    if (current->isEndState()) acceptingRE = {current, inputIndx};
    if (inputIndx >= inputString.size()) {
        if (rulesDFATable[current]["L"] != nullptr)
            if (rulesDFATable[current]["L"]->isEndState())
                return acceptingRE = {rulesDFATable[current]["L"], inputIndx};
        return acceptingRE;
    }
    visitedNode[current->getName()] = true;
    for(auto edge : current->getAllEdges()) {
        if (!visitedNode[edge->getDestination()->getName()] && inputString[inputIndx] == edge->getCondition() ) {
                return checkRE(edge->getDestination(), ++inputIndx);
            }
        }
    return acceptingRE;
}


void Scanner::toStrinsVector (string word) {
    if  (word.empty()) return;
    for (const auto& rdinput : global->inputSymbols) {
        if (word.find(rdinput) == 0) {
            inputString.push_back(rdinput);
            toStrinsVector(word.substr(rdinput.length() ,string::npos));
            return;
        }
    }
    acceptRD = NULLACCEPTING;
    visitedNode = vector<bool> (1000,false);
    pair<Node*, int> accept = checkRD(RDDFA->getStart(), 0, word);
    if (accept != NULLACCEPTING) {
//        cout << "Found from str vec gen " << accept.first->getTokenName() << '\n';
        inputString.push_back(accept.first->getTokenName());
    }
    if (accept.second < word.length())
        toStrinsVector(word.substr(accept.second, string::npos));
}

pair<Node*, int> Scanner::checkRD (Node* current, int chrIndx, string word) {
    if (current == nullptr) return acceptRD;
    if (current->isEndState()) acceptRD = {current, chrIndx};
    if (chrIndx >= word.length()) return acceptRD;
    visitedNode[current->getName()] = true;
    for(auto edge : current->getAllEdges()) {
        if (!visitedNode[edge->getDestination()->getName()] && edge->getStartChar() != '+') {
            if (word[chrIndx] >= edge->getStartChar() && word[chrIndx] <= edge->getEndChar()) {
                return checkRD(edge->getDestination(), ++chrIndx, word);
            }
        }
    }
    return acceptRD;
}
