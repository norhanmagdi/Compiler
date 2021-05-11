//
// Created by hp on 10/05/2021.
//

#ifndef MAIN_CPP_CONVERTOR_H
#define MAIN_CPP_CONVERTOR_H

#include "Edge.h"
#include "GLOBAL.h"
#include "NFA.h"
#include "Node.h"
#include "Convertor.h"

class Edge;
class NFA;
class Node;
class Convertor
{
public:
    Convertor () {};

    virtual ~Convertor();
    GLOBAL *global = global->getInstance();
    NFA* toNFA (const map<string, vector<string>>& RR);
protected:

private:

};

#endif //MAIN_CPP_CONVERTOR_H
