#include "../include/Edge.h"


Edge::Edge(Node* destination, string condition) {
    this->destination = destination;
    this->condition = condition;
}

Edge::Edge(Node* destination, char start, char end, string condition) {
    this->destination = destination;
    this->start = start;
    this->end = end;
    this->condition = condition;
}

Edge::~Edge()
{
    //dtor
}
Node *Edge::getDestination(){
    return this->destination;
}

void Edge::setDestination(Node *destination){
    this->destination = destination;
}

void Edge::setCondition(string condition) {
    Edge::condition = condition;
}

string Edge::getCondition(){
    return this->condition;
}

char Edge::getStartChar() {
    return start;
}

char Edge::getEndChar() {
    return end;
}