#include "../include/DFA.h"

DFA::DFA (Node *startNode, vector <Node*> endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
}

DFA::DFA (NFA *nfa) {
    subsetConstruction(nfa->getStart(), nfa->getEnd());
}

DFA::~DFA()
{
    //dtor
}

Node *DFA::getStart(){
    return startNode;
}

vector<Node*> DFA::getEnd(){
    return endNode;
}

DFA::DState *dNULL = new DFA::DState;

DFA *DFA::subsetConstruction(Node* start, Node *finish) {
    vector<Node*> s0;
    s0.push_back(start);
    vector<Node*> T = EPSClosure(s0);
    startDState = new DState;
    startDState->marked = false;
    startDState->DNode = new Node (global->getNum() ,false);
    startDState->NNodes = T;
    startNode = startDState->DNode;
    vector<DState*> DStates;
    DStates.push_back(startDState);
    DState* unMarked = AnyStateUnmarked(DStates);
    while (unMarked != dNULL) {
        unMarked->marked = true;
        for (const auto& input : global->inputSymbols) {
            vector<Node*> U = EPSClosure(move(unMarked->NNodes, input));
            DState* dd = find(U, DStates);
            if (dd == dNULL) {
                auto *d = new DState;
                d->marked = false;
                d->NNodes = U;
                bool isEnd = false;
                for (auto nde : U) {
                    if (nde->isEndState()){
                        isEnd = true;
                        break;
                    }
                }
                d->DNode = new Node (global->getNum() ,false);
                d->DNode->setEndState(isEnd);
                DStates.push_back(d);
                global->transitionTable[unMarked->DNode->getName()][d->DNode->getName()] = input;
                unMarked->DNode->addEdge(new Edge (d->DNode, input));
            }
            else {
                unMarked->DNode->addEdge(new Edge(dd->DNode, input));
                global->transitionTable[unMarked->DNode->getName()][dd->DNode->getName()] = input;
            }
        }
        unMarked = AnyStateUnmarked(DStates);
    }
    return this;
}



DFA::DState* DFA::find (vector<Node*> U, const vector<DState*>& DStates){
    for (auto state : DStates) {
        if (state->NNodes == U) {
            return state;
        }
    }
    return dNULL;
}

vector<Node*> DFA::move (vector<Node*> T, string a){
    vector<Node*> ans;
    for (auto node : T) {
        vector<Edge*> edges = node->getAllEdges();
        for (auto edge : edges) {
            if (edge->getCondition() == a) {
                Node* dest = edge->getDestination();
                for (auto n : ans) {
                    if (n == dest) {
                        break;
                    }
                    if (n == ans.back()) {
                        ans.push_back(dest);
                    }
                }
            }
        }
    }
    return ans;
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
        vector<Edge*> edges = state->getAllEdges();
        for (auto edge : edges) {
            Node* dest = edge->getDestination();
            if (edge->getCondition() == EPS) {
                for (auto node : closure) {
                    if (node == dest) {
                        break;
                    }
                    if (node == closure.back()) {
                        closure.push_back(dest);
                        DStack.push(dest);
                    }
                }
            }
        }
    }
    sort(closure.begin(), closure.end());
    return closure;
}

DFA::DState* DFA::AnyStateUnmarked(vector<DState*> DStates) {
    for (auto state:DStates) {
        if (state->marked == false) {
            return state;
        }
    }
    return dNULL;
}
