#include "../include/Node.h"
using namespace std;

Node::Node(string nodeName, bool endState) {
    this->nodeName = nodeName;
    this->endState = endState;
}

Node::Node(bool endState) {
    this->nodeName = "DEFAULT";
    this->endState = endState;
}

Node::~Node()
{
    //dtor
}
string Node::getName(){
    return nodeName;
}
void Node::setName(string nodeName) {
    this->nodeName =nodeName;
}
bool Node::isEndState(){
    return endState;
}
void Node::setEndState(bool aendState) {
    this->endState = endState;
}
void Node::addEdge(Edge* edge){
 this->edges.push_back(edge);
}

vector<Edge *>Node::getAllEdges(){
    return this->edges;
}
void Node::setPriority(int priority){
    this->priority = priority;
}
int Node::getPriority(){
    return priority;
}
