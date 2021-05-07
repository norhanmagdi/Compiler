//
// Created by hp on 07/05/2021.
//

#include "../include/GLOBAL.h"

static GLOBAL* instance;

GLOBAL* GLOBAL::getInstance() {
    if (!instance)
        instance = new GLOBAL;
    return instance;
}

int GLOBAL::getNumNow() {
    return num;
}

int GLOBAL::getNum() {
    return num++;
}

