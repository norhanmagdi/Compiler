#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <bits/stdc++.h>
#include "Node.h"

#define EPS '\0'
using namespace std;

class Node;
class Edge
{
    public:
        Edge(Node* destination, char startLetter , char endLetter);
        virtual ~Edge();
        Node *getDestination();
        void setDestination(Node *destination);
        char getStartLetter();
        void setStartLetter(char start);
        char getEndLetter();
        void setEndLetter(char en);

    protected:

    private:
        Node* destination;
        char startLetter;
        char endLetter;
        int sizeOfAlphabet;
};

#endif // EDGE_H
