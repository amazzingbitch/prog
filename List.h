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

template <>

class List<int> {
public:
    static int minInt(int n1, int n2) {
        return n1 - n2;
    }

    List() : top(nullptr) {}

    bool IsEmpty() { return top == nullptr; }

    void Push(int &_T) {
        auto *tmp = new node<int>(_T);
        if (IsEmpty()) {
            top = tmp;
        } else {
            tmp->next = top;
            top = tmp;
        }
    }

    void Pop() {
        if (IsEmpty()) return;
        node<int> *tmp = top;
        top = tmp->next;
        delete tmp;
    }

    int &operator[](int i) {
        if (top == nullptr) throw invalid_argument("Invalid index");
        node<int> *tmp = top;
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
    node<int> *top;
};

template <>

class List<float> {
public:
    static float sumFloat(float n1, float n2) {
        return n1 + n2;
    }

    List() : top(nullptr) {}

    bool IsEmpty() { return top == nullptr; }

    void Push(float &_T) {
        auto *tmp = new node<float>(_T);
        if (IsEmpty()) {
            top = tmp;
        } else {
            tmp->next = top;
            top = tmp;
        }
    }

    void Pop() {
        if (IsEmpty()) return;
        node<float> *tmp = top;
        top = tmp->next;
        delete tmp;
    }

    float &operator[](int i) {
        if (top == nullptr) throw invalid_argument("Invalid index");
        node<float> *tmp = top;
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
    node<float> *top;
};

#endif //PROG2_LIST_H
