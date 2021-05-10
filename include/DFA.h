#ifndef DFA_H
#define DFA_H

#include "../include/Edge.h"
#include "../include/GLOBAL.h"
#include "../include/NFA.h"
#include "../include/Node.h"

class Edge;
class NFA;
class Node;
class DFA
{
public:
    DFA (Node *startNode, vector <Node*> endNode);
    DFA (NFA *nfa);
    DFA () {};

    virtual ~DFA();
    Node *getStart();
    map <Node* , map<string , Node*>> DFATable;
    vector<Node*> getEnd();
//    struct DState {
//        Node* DNode;
//        bool marked = false;
//        vector<Node *> NNodes;
//    };
//    DState* startDState;
    Node* startDState;
    void printDFATable();

protected:

private:
    GLOBAL *global = global->getInstance();
    DFA* subsetConstruction(Node* start, Node *finish);
    vector<Node*> EPSClosure(vector<Node*> states);
    Node* startNode;

    Node* AnyStateUnmarked(vector<Node*> DStates);
    static Node* find (vector<Node*> U, const vector<Node*>& DStates);
    vector<Node*> move (vector<Node*> T, string input);
    vector<Node*> endNode;
};

#endif // DFA_H
