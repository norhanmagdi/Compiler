#include "../include/NFA.h"

NFA::NFA (Node *startNode, Node *endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
}
NFA::NFA (string operation, string condition) {
    createAutomata(condition);
}
NFA::NFA (string operation, NFA* a1) {
    if (operation == "PCLOSURE")
        PCLOSUREautomata(a1);
    if (operation == "CClosure")
        CLOSUREautomata(a1);
}
NFA::NFA (string operation, NFA* a1, NFA* a2) {
    if (operation == "OR")
        ORautomata(a1, a2);
    if (operation == "AND")
        ANDautomata(a1, a2);
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
    a1->getEnd()->setEndState(0);
    a2->getEnd()->setEndState(0);
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
    a1->getEnd()->setEndState(0);
    a1->getEnd()->addEdge(new Edge(a2->getStart(), EPS));
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

void NFA::printNFA () {
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
}

