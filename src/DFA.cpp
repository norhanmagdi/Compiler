#include "../include/DFA.h"

DFA::DFA (Node *startNode, vector <Node*> endNode) {
    this->startNode = startNode;
    this->endNode = endNode;
}

DFA::DFA (NFA *nfa, set<string> inputSymbols) {
//    cout << "From DFA merged name \n";
//    cout << nfa->getStart()->getName() << '\n';
    DFA::inputSymbols = inputSymbols;
    subsetConstruction(nfa->getStart(), nfa->getEnd());
}

DFA::~DFA()
{
    //dtor
}

Node *DFA::getStart(){
    return startDState;
}

vector<Node*> DFA::getEnd(){
    return endNode;
}

Node *dNULL = new Node (-1, false);

DFA *DFA::subsetConstruction(Node* start, Node *finish) {
    vector<Node*> s0;
    s0.push_back(start);
    vector<Node*> T = EPSClosure(s0);
    startDState = new Node (global->getNum() ,false);
    startDState->marked = false;
    startDState->NNodes = T;
//    startNode = startDState->DNode;
    vector<Node*> DStates;
    DStates.push_back(startDState);
    Node* unMarked = AnyStateUnmarked(DStates);
    while (unMarked != dNULL) {
        unMarked->marked = true;
        for (const auto& input :inputSymbols) {
            //cout << "HERE \n";
            //cout << unMarked->getName() << '\n';
            vector<Node*> U = EPSClosure(move(unMarked->NNodes, input));
            if (U.empty()) {
                continue;
            }
            Node* dd = find(U, DStates);
            if (dd == dNULL) {
                auto *d = new Node (global->getNum() ,false) ;
                //cout << "HERE \n";
                //cout << d->getName() << '\n';
                d->marked = false;
                d->NNodes = U;
                bool isEnd = false;
                string tkn;
                for (auto nde : U) {
                    //cout << "HERE \n";
                    //cout << nde->getName() << '\n';
                    if (nde->isEndState()){
                        isEnd = true;
                        tkn = nde->getTokenName();
                        break;
                    }
                }
                if (isEnd) {
                    d->setTokenName(tkn);
//                    cout << tkn << '\n';
                }
//                d->DNode = new Node (global->getNum() ,false);
                //cout << isEnd << " is END \n";

                d->setEndState(isEnd);
                DStates.push_back(d);
                global->transitionTable[unMarked->getName()][d->getName()] = input;
                DFATable[unMarked][input] = d;
                DFATable[d][input] = nullptr ;
                if (input.find('-') != string::npos) {
                    unMarked->addEdge(new Edge (d, input[0], input[2] ,input));
                }
                else
                    unMarked->addEdge(new Edge (d, input));
            }
            else {
                unMarked->addEdge(new Edge(dd, input));
                DFATable[unMarked][input] = dd;
                global->transitionTable[unMarked->getName()][dd->getName()] = input;
            }
        }
        unMarked = AnyStateUnmarked(DStates);
    }
    return this;
}



Node* DFA::find (vector<Node*> U, const vector<Node*>& DStates){
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
        //cout << "HERE \n";
        //cout << node->getName() << '\n';
        vector<Edge*> edges = node->getAllEdges();
        for (auto edge : edges) {
            if (edge->getCondition() == a) {
                Node* dest = edge->getDestination();
                //cout << "HERE \n";
                //cout << dest->getName() << '\n';
                if (ans.empty()) {
                    ans.push_back(dest);
                }
                else {
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
    }
    return ans;
}

vector<Node*> DFA::EPSClosure(vector<Node*> states) {
    vector<Node*> closure;
    stack<Node*> DStack;
    for (auto state : states) {
        //cout << "HERE \n";
        //cout << state->getName() << '\n';
        DStack.push(state);
        closure.push_back(state);
    }
    while (! (DStack.empty()) ) {
        Node* state = DStack.top();
        DStack.pop();
        vector<Edge*> edges = state->getAllEdges();
        for (auto edge : edges) {
            Node* dest = edge->getDestination();
            //cout << "HERE \n";
            //cout << dest->getName() << '\n';
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

Node* DFA::AnyStateUnmarked(vector<Node*> DStates) {
    for (auto state:DStates) {
        if (state->marked == false) {
            return state;
        }
    }
    return dNULL;
}


void DFA::printDFATable () {
    for (auto mp : DFATable) {
        cout << mp.first->getName() << " is End  : " << mp.first->isEndState();
        if (mp.first->isEndState()) cout << "   " << mp.first->getTokenName() ;
        cout << '\n';
        for (auto m : mp.second) {
            cout << m.first << " ";
            if (m.second == nullptr) {
                cout << "-" << '\n';
            }
            else {
                cout << m.second->getName() << '\n';
            }
        }
        cout << '\n';
    }
}
