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
    return new NFA(startNode, endNode);
}
NFA *NFA::ORautomata(NFA* a1, NFA* a2){
    startNode = new Node(global->getNum() ,false);
    endNode = new Node(global->getNum(), true);
    global->transitionTable[startNode->getName()][a1->getStart()->getName()] = EPS;
    global->transitionTable[startNode->getName()][a2->getStart()->getName()] = EPS;
    global->transitionTable[a1->getEnd()->getName()][endNode->getName()] = EPS;
    global->transitionTable[a2->getEnd()->getName()][endNode->getName()] = EPS;
    a1->getEnd()->setEndState(false);
    a2->getEnd()->setEndState(false);
    startNode->addEdge(new Edge(a1->getStart(),EPS));
    startNode->addEdge(new Edge(a2->getStart(),EPS));
    a1->getEnd()->addEdge(new Edge(endNode,EPS));
    a2->getEnd()->addEdge(new Edge(endNode,EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::ANDautomata(NFA* a1, NFA* a2){
    startNode = a1->getStart();
    endNode = a2->getEnd();
    global->transitionTable[a1->getEnd()->getName()][a2->getStart()->getName()] = EPS;
    a1->getEnd()->setEndState(false);
    a1->getEnd()->addEdge(new Edge(a2->getStart(), EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::PCLOSUREautomata(NFA* a){
    cout << " PK\n";
    startNode = new Node(global->getNum() ,false);
    endNode = new Node(global->getNum(), true);

    global->transitionTable[a->getEnd()->getName()][endNode->getName()] = EPS;
    global->transitionTable[a->getEnd()->getName()][a->getStart()->getName()] = EPS;
    global->transitionTable[startNode->getName()][a->getStart()->getName()] = EPS;

    a->getEnd()->setEndState(false);

    startNode->addEdge(new Edge(a->getStart(), EPS));
    a->getEnd()->addEdge(new Edge(a->getStart(), EPS));
    a->getEnd()->addEdge(new Edge(endNode, EPS));

    return new NFA(startNode, endNode);
}
NFA *NFA::CLOSUREautomata(NFA* a){
    PCLOSUREautomata(a);
    global->transitionTable[startNode->getName()][endNode->getName()] = EPS;
    this->getStart()->addEdge(new Edge(this->getEnd(), EPS));
    return this;
}

NFA* NFA::mergingNFAs (vector<NFA*> to_be_merged) {
    startNode = new Node(global->getNum() ,false);
    for (auto RE : to_be_merged) {
        startNode->addEdge(new Edge(RE->getStart(), EPS));
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
vector<bool> visited(1000, false);

void NFA::printNFA () {
    cout << "Start Node " << startNode->getName() << " End Node ";
    if (endNode != nullptr)
        cout << endNode->getName() << " at " << endNode->getTokenName();
    cout << '\n';
    stack <Node*> stck;
    stck.push(startNode);
    while (!stck.empty()) {
        Node* stt = stck.top();
        stck.pop();
        if (visited[stt->getName()]) continue;
        visited[stt->getName()] = true;
        cout << stt->getName() << " ";
        for (auto st : stt->getAllEdges()) {
            cout << "\t" << st->getDestination()->getName() << "\t" << st->getCondition() << '\n';
            if (!visited[st->getDestination()->getName()]) {
                stck.push(st->getDestination());
            }
        }
        cout << '\n';

    }
}

NFA *NFA::RANGEautomata(NFA* a11, NFA* a22) {
    string a1 = a11->getStart()->getAllEdges()[0]->getCondition();
    string a2 = a22->getStart()->getAllEdges()[0]->getCondition();
    char st = a1.at(0);
    char en = a2.at(0);
    startNode = new Node (global->getNum(), false);
    endNode = new Node (global->getNum(), true);
    startNode->addEdge(new Edge (endNode, st, en, a1 + "-" + a2));
    global->transitionTable[startNode->getName()][endNode->getName()] = a1 + "-" + a2;
    /*
    stack<NFA*> tb_merged;
    cout << "\nRANGE" << '\n';
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
    if (tb_merged.size()==2){
        NFA* val1 = tb_merged.top();
        tb_merged.pop();
        NFA* val2 = tb_merged.top();
        tb_merged.pop();
        tb_merged.push(new NFA ("OR", val1, val2));
    }
    startNode = tb_merged.top()->getStart();
    endNode =tb_merged.top()->getEnd();
     */
    return this;
}


