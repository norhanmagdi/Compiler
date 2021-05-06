#include "Edge.h"


Edge::Edge(Node* destination, char startLetter , char endLetter) {
    this->destination = destination;
    this->startLetter = startLetter;
    this->endLetter = endLetter;
    this->sizeOfAlphabet = endLetter - startLetter + 1;
}

Edge::~Edge()
{
    //dtor
}
Node *Edge::getDestination(){
    return this->destination;
}

void Edge::setDestination(Node *destination) {
    Edge::destination = destination;
}

char Edge::getStartLetter(){
    return startLetter;
}

void Edge::setStartLetter(char startLetter) {
    Edge::startLetter = startLetter;
}

char Edge::getEndLetter(){
    return endLetter;
}

void Edge::setEndLetter(char endLetter) {
    Edge::endLetter = endLetter;
}

