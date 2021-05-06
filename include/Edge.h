#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <bits/stdc++.h>
#include "Node.h"

#define EPS "\0"
using namespace std;

class Node;
class Edge
{
    public:
        Edge(Node* destination, string condition);
        virtual ~Edge();
        Node *getDestination();
        void setDestination(Node *destination);
        string getCondition();
        void setCondition(string condition);

    protected:

    private:
        Node* destination;
        string condition;
};

#endif // EDGE_H
