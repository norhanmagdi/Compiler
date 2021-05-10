#include "../include/NFA.h"

#include <utility>

NFA::NFA (Node *startNode, Node *endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
}
NFA::NFA (const string& operation, string condition) {
    createAutomata(std::move(condition));
}
NFA::NFA (const string& operation, NFA* a1) {
    if (operation == "PCLOSURE")
        PCLOSUREautomata(a1);
    if (operation == "CClosure")
        CLOSUREautomata(a1);
}
NFA::NFA (const string& operation, NFA* a1, NFA* a2) {
    if (operation == "OR")
        ORautomata(a1, a2);
    if (operation == "AND")
        ANDautomata(a1, a2);
    if (operation == "RANGE")
        RANGEautomata(a1, a2);
}
//NFA::NFA (const string& operation, string s1, string s2) {
//    RANGEautomata(s1, s2);
//}

NFA::NFA (vector<NFA*> to_be_merged){
    mergingNFAs(std::move(to_be_merged));
}

NFA::~NFA()
{
    //dtor
}
Node *NFA::getStart(){
    return startNode;
}

Node *NFA::getEnd(){
    return endNode;
}

NFA *NFA::createAutomata(string condition){
    startNode = new Node(global->getNum() ,false);
    endNode = new Node(global->getNum(), true);
    global->transitionTable[startNode->getName()][endNode->getName()] = condition;
    startNode->addEdge(new Edge(endNode, condition));
    NFATable[startNode][condition].push_back(endNode);
    return new NFA(startNode, endNode);
}
NFA *NFA::ORautomata(NFA* a1, NFA* a2){
    startNode = new Node(global->getNum() ,false);
    endNode = new Node(global->getNum(), true);
    cout << 1 << '\n';
    global->transitionTable[startNode->getName()][a1->getStart()->getName()] = EPS;
    global->transitionTable[startNode->getName()][a2->getStart()->getName()] = EPS;
    global->transitionTable[a1->getEnd()->getName()][endNode->getName()] = EPS;
    global->transitionTable[a2->getEnd()->getName()][endNode->getName()] = EPS;
    cout << 1 << '\n';
    a1->getEnd()->setEndState(0);
    a2->getEnd()->setEndState(0);
    startNode->addEdge(new Edge(a1->getStart(),EPS));
    NFATable[startNode][EPS].push_back(a1->getStart());
    startNode->addEdge(new Edge(a2->getStart(),EPS));
    NFATable[startNode][EPS].push_back(a2->getStart());
    a1->getEnd()->addEdge(new Edge(endNode,EPS));
    NFATable[a1->getEnd()][EPS].push_back(endNode);
    a2->getEnd()->addEdge(new Edge(endNode,EPS));
    NFATable[a2->getEnd()][EPS].push_back(endNode);
    return new NFA(startNode, endNode);
}
NFA *NFA::ANDautomata(NFA* a1, NFA* a2){
    cout << "AND\n";
    cout << a1->getStart()->getName() << " " << a2->getStart()->getName() << '\n';
    startNode = a1->getStart();
    endNode = a2->getEnd();
    global->transitionTable[a1->getEnd()->getName()][a2->getStart()->getName()] = EPS;
    a1->getEnd()->setEndState(false);
    a1->getEnd()->addEdge(new Edge(a2->getStart(), EPS));
    NFATable[a1->getEnd()][EPS].push_back(a2->getStart());
    return new NFA(startNode, endNode);
}
NFA *NFA::PCLOSUREautomata(NFA* a){
    startNode = new Node(global->getNum() ,false);
    endNode = new Node(global->getNum(), true);
    global->transitionTable[a->getEnd()->getName()][endNode->getName()] = EPS;
    global->transitionTable[a->getEnd()->getName()][a->getStart()->getName()] = EPS;
    global->transitionTable[startNode->getName()][a->getStart()->getName()] = EPS;
    a->getEnd()->setEndState(0);
    startNode->addEdge(new Edge(a->getStart(), EPS));
    NFATable[startNode][EPS].push_back(a->getStart());
    a->getEnd()->addEdge(new Edge(a->getStart(), EPS));
    NFATable[a->getEnd()][EPS].push_back(a->getStart());
    a->getEnd()->addEdge(new Edge(endNode, EPS));
    NFATable[a->getEnd()][EPS].push_back(endNode);
    return new NFA(startNode, endNode);
}
NFA *NFA::CLOSUREautomata(NFA* a){
    PCLOSUREautomata(a);
    global->transitionTable[startNode->getName()][endNode->getName()] = EPS;
    this->getStart()->addEdge(new Edge(this->getEnd(), EPS));
    NFATable[this->getStart()][EPS].push_back(this->getEnd());
    return this;
}

NFA* NFA::mergingNFAs (vector<NFA*> to_be_merged) {
    startNode = new Node(global->getNum() ,false);
    for (auto RE : to_be_merged) {
        startNode->addEdge(new Edge(RE->getStart(), EPS));
        NFATable[startNode][EPS].push_back(RE->getStart());
        global->transitionTable[startNode->getName()][RE->getStart()->getName()] = EPS;
    }
    return this;
}

void NFA::setTokenName(string tokenName) {
    endNode->setTokenName(tokenName);
}
string NFA::getTokenName() {
    return endNode->getTokenName();
}

void NFA::printNFA () {
    cout << "PRINTNFA" << '\n';
    int numOfNodes = global->getNumNow();
    for (int i = 0; i < numOfNodes; ++i) {
        cout << "  " << i;
    }
    cout << '\n';
    for (int i = 0; i < numOfNodes; ++i) {
        cout << i << "  ";
        for (int j = 0; j < numOfNodes; ++j) {
            cout << " " << global->transitionTable[i][j] << "  ";
        }
        cout << '\n';
    }
//    global->NFAStates = numOfNodes;

//    for (auto mp : NFATable) {
//        cout << mp.first->getName() << '\n';
//        for (auto m : mp.second) {
//            cout << m.first << " ";
//            for (auto  v : m.second)
//                cout << v << " ";
//        }
//        cout << '\n';
//    }
}

NFA *NFA::RANGEautomata(NFA* a11, NFA* a22) {
    string a1 = a11->getStart()->getAllEdges()[0]->getCondition();
    string a2 = a22->getStart()->getAllEdges()[0]->getCondition();
    stack<NFA*> tb_merged;
    cout << "RANGE" << '\n';
    for (char A = a1.at(0); A <= a2.at(0); ++A) {
        cout << A << '\n';
        if (tb_merged.size()==2){
            NFA* val1 = tb_merged.top();
            tb_merged.pop();
            NFA* val2 = tb_merged.top();
            tb_merged.pop();
            tb_merged.push(new NFA ("OR", val1, val2));
        }
        std::string s(1, A);
        NFA* TEMP = new NFA ("SINGLE", s);
        TEMP->setTokenName(s);
        tb_merged.push(TEMP);
    }
    startNode = tb_merged.top()->getStart();
    endNode =tb_merged.top()->getEnd();
    return this;
}


