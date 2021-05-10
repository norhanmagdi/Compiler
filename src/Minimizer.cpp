//
// Created by hp on 09/05/2021.
//
#include "../include/Minimizer.h"

void Minimizer::minimize() {
    vector <vector <Node*>> partitions;
    vector<Node*> finalStates;
    vector<Node*> nonFinalStates;

    for (const auto& state : DFATable) {
        if (state.first->isEndState())
            finalStates.push_back(state.first);
        else nonFinalStates.push_back(state.first);
    }

    partitions.push_back(finalStates);
    partitions.push_back(nonFinalStates);

    minimizePartition (partitions);
}

vector<vector<Node *>> Minimizer::minimizePartition(vector<vector<Node *>> partitions) {
    vector<vector<Node*>> ret;
    for (auto partition : partitions){
        if (partition.size() > 1) {
            for (int i = 0; i < partition.size(); ++i){
                if (findState(ret, partition[i])){
                    continue;
                }
                vector<Node*> temp_partition;
                temp_partition.push_back(partition[i]);

                for (int j = i + 1; j < partition.size(); j++){
                    Node* s1 = partition.at(i);
                    Node* s2 = partition.at(j);

                    if ((!canBeCombined(partitions, s1, s2)) &&
                        DFATable.find(s1) != DFATable.end() &&
                        DFATable.find(s2) != DFATable.end()) {

                        if(DFATable[s1] == DFATable[s2]){
                            if(!s1->isEndState()) {
                                temp_partition.push_back(s2);
                            } else if(s1->getName() == s2->getName()){
                                temp_partition.push_back(s2);
                            }
                        }

                    }
                }
                ret.push_back(temp_partition);
                updateTable(temp_partition);
            }
        }else{
            ret.push_back(partition);
        }
    }
    if (partitions.size() == ret.size()){
        return ret;
    }
    return minimizePartition(ret);
}

void Minimizer::updateTable(vector<Node *> temp) {
        if (temp.size() > 1){
            Node* state = temp.at(0);
        for (int i = 1; i < temp.size(); i++){
            DFATable.erase(temp.at(i));
        }
        for (pair<Node*, map<string , Node *>> row:DFATable){
            for (const auto& c : row.second){
                for(int i = 1; i < temp.size(); i++){
                    if (temp.at(i) == c.second){
                        DFATable.at(row.first).at(c.first) = state;
                    }
                }
            }
        }
    }
}

bool Minimizer::canBeCombined(vector<vector<Node *>> &partitions, Node *state1, Node *state2) {
    for (auto partition : partitions) {
        if (!(find(partition.begin(), partition.end(), state1) != partition.end() &&
              find(partition.begin(), partition.end(), state2) != partition.end()))
            return true;
    }
    return false;
}

bool Minimizer::findState(const vector<vector<Node*>>& pp, Node *state) {
    for (auto partition : pp) {
        if (find(partition.begin(), partition.end(), state) != partition.end())
            return true;
    }
    return false;
}
