

#include "..\include\Scanner.h"

Scanner::Scanner(DFA* rulesDFA, DFA* RDDFA)
{
    Scanner::rulesDFA = rulesDFA;
    Scanner::rulesDFA->printDFATable();
    Scanner::rulesDFATable = rulesDFA->DFATable;
    Scanner::RDDFA = RDDFA;
    cout << "RD DFA \n";
    Scanner::RDDFA->printDFATable();
    cout << "RD DFA DONE \n";
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
        s.erase(remove(s.begin(), s.end(), ' '), s.end());
        scanWord(s);
    }
}
vector<string> inputString;
const pair<Node*, int> NULLACCEPTING = {nullptr, -1};
pair<Node*, int> acceptRD = NULLACCEPTING;
vector<bool> visitedNode(1000, false);
pair<Node*, int> acceptingRE = NULLACCEPTING;

vector<pair<string,string>> Scanner::scanWord(string word){
    word.erase(remove(word.begin(), word.end(), ' '), word.end());
    if (word.empty()) return vector<pair<string,string>>();
    vector<pair<string,string>> V;
    for (const auto& keyWord : global->keyWords) {
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

    inputString.clear();
    toStrinsVector(word);
    if (!inputString.empty()) {
//        for (auto hh : inputString)
//            cout << hh << " ";
//        cout << '\n';
        acceptingRE = NULLACCEPTING;
        pair<Node *, int> accepted = checkRE(rulesDFA->getStart(), 0);
        if (accepted != NULLACCEPTING) {
            cout << "Found " << accepted.first->getTokenName() << '\n';
        }
    }

    return tokens;
}
// Maximal munch
pair<Node*, int> Scanner::checkRE (Node* current, int inputIndx) {
    if (inputIndx >= inputString.size()) return acceptingRE;
    Node* to = rulesDFATable[current][inputString[inputIndx]];
//    cout << "TO " << to->getName() << " indx " << inputIndx << '\n';
    if (to->isEndState())
        acceptingRE = {to, inputIndx};
    if (to != nullptr)// Not end
        return checkRE(to, ++inputIndx);
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
    if (current->isEndState()) acceptRD = {current, chrIndx};
    if (chrIndx >= word.length()) return acceptRD;
    if (current == nullptr) return acceptRD;
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
