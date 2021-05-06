#include "Node.h"
using namespace std;

Node::Node() {
    this->nodeName = "";
    this->acceptingState =false;

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
bool Node::isAcceptingState(){
    return acceptingState;
}
void Node::setAcceptingState(bool acceptingState) {
    this->acceptingState = acceptingState;
}
void Node::addEdge(char c,string destinationNode){
 if (edges.find(c) == edges.end())
        edges[c] = destinationNode;
 else
        edges[c] += "," + destinationNode;
}
string Node::getDestination(char c)
{
    if (edges.find(c) == edges.end())
        return "";
    return edges[c];
}

unordered_map<char, string >Node::getAllEdges()
{
    return edges;
}
void Node::setPriority(int priority)
{
    this->priority = priority;
}
int Node::getPriority()
{
    return priority;
}
