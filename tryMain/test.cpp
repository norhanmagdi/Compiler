#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string>* split_string(string production){
    int index = 0;
    int size = production.size();
    vector<string>* array_of_terms = new vector<string>();
    while(index < size){
        string str = "";
        while(index < size && production.at(index) != ' '){
            str = str + production.at(index++);
        }
        if(str != ""){
            array_of_terms->push_back(str);
        }
        index++;
    }
    return array_of_terms;
}

int main(){
    string s = "Hello world my name is Ramez";

    vector<string>* v = split_string(s);

    for(auto &x: *v){
        cout << x << endl;
    }   
}