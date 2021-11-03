//
// Created by casde on 03.11.2021.
//

#ifndef PROG2_NODE_H
#define PROG2_NODE_H

#include "Date.h"

struct node {
    node *next;
    Date &date;

    explicit node(Date &_date) : next(nullptr), date(_date) {}
};


#endif //PROG2_NODE_H
