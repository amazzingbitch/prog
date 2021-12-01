//
// Created by casde on 03.11.2021.
//

#ifndef PROG2_LIST_H
#define PROG2_LIST_H

#include "Node.h"
#include "Date.h"

template <typename T>

class List {
public:
    List() : top(nullptr) {}

    bool IsEmpty() { return top == nullptr; }

    void Push(T &_T) {
        auto *tmp = new node<T>(_T);
        if (IsEmpty()) {
            top = tmp;
        } else {
            tmp->next = top;
            top = tmp;
        }
    }

    void Pop() {
        if (IsEmpty()) return;
        node<T> *tmp = top;
        top = tmp->next;
        delete tmp;
    }

    T &operator[](int i) {
        if (top == nullptr) throw invalid_argument("Invalid index");
        node<T> *tmp = top;
        for (int j = 0; j < i; ++j) {
            tmp = tmp->next;
            if (tmp == nullptr) throw invalid_argument("Invalid index");
        }
        return tmp->t;
    }
    ~List() {
        while (!IsEmpty()) {
            Pop();
        }
    }

private:
    node<T> *top;
};

#endif //PROG2_LIST_H
