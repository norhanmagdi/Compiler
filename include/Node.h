#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Node
{
    public:
        Node();
        virtual ~Node();
        string getName();
        void setName(string stateName);
        bool isAcceptingState();
        void setAcceptingState(bool acceptingState);
        void addEdge(char c,string destinationNode);
        string getDestination(char c);
        unordered_map<char, string > getAllEdges();
        void setPriority(int priority);
        int getPriority();


    protected:

    private:
        unordered_map<char ,string >edges;
        string nodeName;
        bool acceptingState;
        int priority;

};

#endif // NODE_H

