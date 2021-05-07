#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Edge;
class Node
{
    public:
        Node(int nodeName, bool endState);
        virtual ~Node();
        int getName();
        void setName(int stateName);
        bool isEndState();
        void setEndState(bool acceptingState);
        void addEdge(Edge* edge);
       // string getDestination(char c);
        vector<Edge*> getAllEdges();
        void setPriority(int priority);
        int getPriority();


    protected:

    private:
        vector<Edge*>edges;
        int nodeName;
        bool endState;
        int priority;

};

#endif // NODE_H

