#include "../include/DFA.h"

DFA::DFA (Node *startNode, vector <Node*> *endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
}

DFA::DFA (NFA *nfa) {
    subsetConstruction(nfa.getStart(), nfa.getEnd());
}

DFA::~DFA()
{
    //dtor
}

Node *DFA::getStart(){
    return startNode;
}

vector<Node*> *DFA::getEnd(){
    return endNode;
}

DFA *DFA::subsetConstruction(Node* start, Node *finish) {
    vector<Node*> s0;
    s0.push_back(start);
    vector<Node*> T = EPSClosure(s0);
    DState startDState;
    startDState->marked = false;
    startDState->DNode = new Node (global->getNum() ,false);
    startDState->NNodes = T;
    startNode = startDState->DNode;
    vector<DState> DStates;
    DStates.push_back(startDState);
    while (AnyStateUnmarked(DStates)) {

        //TO BE CONTINUED ...

    }
}

vector<Node*> DFA::EPSClosure(vector<Node*> states) {
    vector<Node*> closure;
    stack<Node*> DStack;
    for (auto state : states) {
        DStack.push(state);
        closure.push_back(state);
    }
    while (! (DStack.empty()) ) {
        Node* state = DStack.top();
        DStack.pop();
        vector<Edge*> edges = state.getAllEdges();
        for (auto edge : edges) {
            Node* destination = edge.getCondition();
            if (destination == EPS) {
                for (auto node : closure) {
                    if (node == destination) {
                        break;
                    }
                    if (node == closure.end()) {
                        closure.push_back(destination);
                        DStack.push(destination);
                    }
                }
            }
        }
    }
    sort(closure.begin(), closure.end());
    return closure;
}

bool DFA::AnyStateUnmarked(vector<DState> DStates) {
    for (auto DState:DStates) {
        if (DState->marked == false) {
            DState->marked = true;
            return true;
        }
    }
    return false;
}
