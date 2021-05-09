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
    DFA (Node *startNode, vector <Node*> endNode);
    DFA (NFA *nfa);
    DFA () {};

    virtual ~DFA();
    Node *getStart();
    vector<Node*> getEnd();
    struct DState {
        Node* DNode;
        bool marked;
        vector<Node *> NNodes;
    };

protected:

private:
    GLOBAL *global = global->getInstance();
    DFA* subsetConstruction(Node* start, Node *finish);
    vector<Node*> EPSClosure(vector<Node*> states);
    Node* startNode;
    DState* startDState;
    DState* AnyStateUnmarked(const vector<DState*>& DStates);
    static DState* find (vector<Node*> U, const vector<DState*>& DStates);
    vector<Node*> move (vector<Node*> T, string input);
    vector<Node*> endNode;
};

#endif // DFA_H
