#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "card.h"


template <typename T> class Node {
private:
    T *data;
    Node<T> *next = NULL;

public:
    void setData(T *data1);
    T* getData();
    void setNext(Node<T> *next1);
    Node<T>* getNext();
};

template <typename T> class LinkedList {
private:
    Node<T> *head = NULL;
    int size;

public:
    LinkedList();
    void add(T* data);
    T* getData(int index);
    int deleteData(int index);
    int deleteLastData();
};

#endif // LINKEDLIST_H
