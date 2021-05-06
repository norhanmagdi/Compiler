#include "NFA.h"

NFA::NFA(Node *startNode, Node *endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
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
NFA *NFA::createAutomata(char startLetter , char endLetter){
    Node* startNode = new Node("0" ,0);
    Node* endNode = new Node("1" ,1);
    startNode->addEdge(new Edge(endNode, startLetter, endLetter));
    return new NFA(startNode, endNode);
}
NFA *NFA::ORautomata(NFA* a1, NFA* a2){
    Node* startNode = new Node(0);
    Node* endNode = new Node(1);
    a1->getEnd()->setEndState(0);
    a2->getEnd()->setEndState(0);
    startNode->addEdge(new Edge(a1->getStart(), EPS, EPS));
    startNode->addEdge(new Edge(a2->getStart(), EPS, EPS));
    a1->getEnd()->addEdge(new Edge(endNode, EPS, EPS));
    a2->getEnd()->addEdge(new Edge(endNode, EPS, EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::ANDautomata(NFA* a1, NFA* a2){
    Node* startNode = a1->getStart();
    Node* endNode = a2->getEnd();
    a1->getEnd()->setEndState(0);
    a1->getEnd()->addEdge(new Edge(a2->getStart(), EPS, EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::PCLOSUREautomata(NFA* a){
    Node* startNode = new Node(0);
    Node* endNode = new Node(1);
    a->getEnd()->setEndState(0);
    startNode->addEdge(new Edge(a->getStart(), EPS, EPS));
    a->getEnd()->addEdge(new Edge(a->getStart(), EPS, EPS));
    a->getEnd()->addEdge(new Edge(endNode, EPS, EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::CLOSUREautomata(NFA* a){
    NFA* newAutomata = PCLOSUREautomata(a);
    newAutomata->getStart()->addEdge(new Edge(newAutomata->getEnd(), EPS,EPS));
    return newAutomata;
}


