#ifndef NFA_H
#define NFA_H

#include "../include/Node.h"
#include "../include/Edge.h"
#include "../include/GLOBAL.h"

class Node;
class Edge;
class NFA
{
public:
    NFA (Node *startNode, Node *endNode);
    NFA (vector<NFA*> to_be_merged);
    NFA (const string& operation, NFA* a1);
    NFA (const string& operation, NFA* a1, NFA* a2);
    NFA (const string& operation, string condition);
    NFA (const string& operation, string s1, string s2);

    virtual ~NFA();
    void printNFA ();
    int numOfStates;
    NFA* mergingNFAs (vector<NFA*> to_be_merged);
    Node *getStart();
    Node *getEnd();
    void setTokenName(string tokenName);
    string getTokenName();
    NFA* RANGEautomata(NFA* a11, NFA* a22);
    NFA* createAutomata(string condition);
    NFA* ORautomata(NFA* a1, NFA* a2);
    NFA* ANDautomata(NFA* a1, NFA* a2);
    NFA* CLOSUREautomata(NFA* a1);
    NFA* PCLOSUREautomata(NFA* a1);
    map <Node* , map<string , vector<Node*>>> NFATable;
//    static OpMap NFATable;

protected:

private:
    GLOBAL *global = global->getInstance();
    string tokenName;
    Node* startNode;
    Node* endNode;
};

#endif // NFA_H
