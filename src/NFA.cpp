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



