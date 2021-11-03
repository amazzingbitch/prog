//
// Created by casde on 03.11.2021.
//

#ifndef PROG2_NODE_H
#define PROG2_NODE_H

#include "Date.h"

template <typename T>

struct node {
    node *next;
    T &t;

    node(T &_T) : next(nullptr), t(_T) {}
};


#endif //PROG2_NODE_H
