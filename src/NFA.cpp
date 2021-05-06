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
    startNode = new Node(0);
    endNode = new Node(1);
    startNode->addEdge(new Edge(endNode, condition));
    return new NFA(startNode, endNode);
}
NFA *NFA::ORautomata(NFA* a1, NFA* a2){
    startNode = new Node(0);
    endNode = new Node(1);
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
    a1->getEnd()->setEndState(0);
    a1->getEnd()->addEdge(new Edge(a2->getStart(), EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::PCLOSUREautomata(NFA* a){
    startNode = new Node(0);
    endNode = new Node(1);
    a->getEnd()->setEndState(0);
    startNode->addEdge(new Edge(a->getStart(), EPS));
    a->getEnd()->addEdge(new Edge(a->getStart(), EPS));
    a->getEnd()->addEdge(new Edge(endNode, EPS));
    return new NFA(startNode, endNode);
}
NFA *NFA::CLOSUREautomata(NFA* a){
    PCLOSUREautomata(a);
    this->getStart()->addEdge(new Edge(this->getEnd(), EPS));
    return this;
}

void dfs(int node,int parent){
    visited[node] = true;
    for(auto adjNode : adjList[node]){
        if (!visited[adjNode])
            dfs(adjNode, node);
    }
}


void NFA::printNFA () {
    for (auto edge : startNode->getAllEdges()){
        cout << edge->getCondition() << '\n';
        for (auto e = edge->getDestination())
    }
}

