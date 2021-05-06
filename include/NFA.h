#ifndef NFA_H
#define NFA_H

class Node;
class NFA
{
    public:
        NFA(Node *startNode, Node *endNode);
        virtual ~NFA();
        int numOfStates;
        Node *getStart();
        Node *getEnd();
        NFA* createAutomata(char startLetter , char endLetter);
        NFA* ORautomata(NFA* a1, NFA* a2);
        NFA* ANDautomata(NFA* a1, NFA* a2);
        NFA* CLOSUREautomata(NFA* a1);
        NFA* PCLOSUREautomata(NFA* a2);

    protected:

    private:
        Node* startNode;
        Node* endNode;

};

#endif // NFA_H
