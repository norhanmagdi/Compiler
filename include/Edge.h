#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <bits/stdc++.h>
#include "Node.h"

#define EPS "\\L"
using namespace std;

class Node;
class Edge
{
    public:
    Edge(Node* destination, string condition);

    Edge(Node *destination, char start, char end, string condition);

    virtual ~Edge();
        Node *getDestination();
        void setDestination(Node *destination);
        string getCondition();
        void setCondition(string condition);
        char getStartChar();
        char getEndChar();

    protected:

    private:
        Node* destination;
        string condition;
        char end;
        char start = '+';
};

#endif // EDGE_H
