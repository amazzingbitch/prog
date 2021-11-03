//
// Created by casde on 03.11.2021.
//

#ifndef PROG2_LIST_H
#define PROG2_LIST_H

#include "Node.h"
#include "Date.h"

class List {
public:
    List() : top(nullptr) {}

    bool IsEmpty() { return top == nullptr; }

    void Push(Date &_date) {
        auto *tmp = new node(_date);
        if (IsEmpty()) {
            top = tmp;
        } else {
            tmp->next = top;
            top = tmp;
        }
    }

    void Pop() {
        if (IsEmpty()) return;
        node *tmp = top;
        top = tmp->next;
        delete tmp;
    }

    Date &operator[](int i) {
        if (top == nullptr) throw invalid_argument("Invalid index");
        node *tmp = top;
        for (int j = 0; j < i; ++j) {
            tmp = tmp->next;
            if (tmp == nullptr) throw invalid_argument("Invalid index");
        }
        return tmp->date;
    }

private:
    node *top;
};

#endif //PROG2_LIST_H
