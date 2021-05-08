#ifndef DFA_H
#define DFA_H

#include "../include/Node.h"
#include "../include/Edge.h"
#include "../include/GLOBAL.h"
#include "../include/NFA.h"

class Node;
class Edge;
class NFA;
class DFA
{
public:
    DFA (Node *startNode, Node *endNode);
    DFA (NFA *nfa);
    DFA();

    virtual ~DFA();
    Node *getStart();
    Node *getEnd();
    struct DState {
        Node* DNode;
        bool marked;
        vector<Node *> NNodes:
    };

protected:

private:
    GLOBAL *global = global->getInstance();
    Node* startNode;
    vector<Node*> endNode;
};

#endif // DFA_H
