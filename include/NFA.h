#ifndef NFA_H
#define NFA_H

#include "../include/Node.h"
#include "../include/Edge.h"
class Node;
class Edge;
class NFA
{
public:
    NFA(Node *startNode, Node *endNode);
    virtual ~NFA();
    int numOfStates;
    Node *getStart();
    Node *getEnd();
    NFA* createAutomata(string condition);
    NFA* ORautomata(NFA* a1, NFA* a2);
    NFA* ANDautomata(NFA* a1, NFA* a2);
    NFA* CLOSUREautomata(NFA* a1);
    NFA* PCLOSUREautomata(NFA* a1);

protected:

private:
    Node* startNode;
    Node* endNode;

};

#endif // NFA_H
