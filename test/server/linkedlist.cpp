#include "linkedlist.h"
#include "card.h"


template <typename card> LinkedList<card>::LinkedList()
{

}

template <typename T> void Node<T>::setData(T *data1) {
    data = data1;
}

template <typename T> T* Node<T>::getData() {
     return data;
}

template <typename T> void Node<T>::setNext(Node<T> *next1) {
    next = next1;
}

template <typename T> Node<T>* Node<T>::getNext() {
     return next;
}

template <typename T> void LinkedList<T>::add(T* data) {
    if (head == NULL) {
        head = new Node<T>;
        head->setData(data);
        //printf("head o %d\n", head->getData()->o);
    } else {
        Node<T> *tmp = head;
        while (tmp->getNext() != NULL) {
            tmp = tmp->getNext();
        }
        tmp->setNext(new Node<T>);
        tmp->getNext()->setData(data);
    }
    size++;
}

template <typename T> T* LinkedList<T>::getData(int index) {
    if (index < size && index >= 0) {
        Node<T> *tmp = head;
        for (int i = 0; i < index; i++) {
            tmp = tmp->getNext();
        }
        return tmp->getData();
    } else {
        return NULL;
    }
}

template <typename T> int LinkedList<T>::deleteData(int index) {
    if (size == 1 && index == 0) {
        delete(head);
        return 1;
    } else if (size == 0) {
        return -1;
    } else if (index < size && index >= 0) {
        Node<T> *tmp = head;
        for (int i = 0; i < index - 1; i++) {
            tmp = tmp->getNext();
        }
        Node<T> *tmpNext = tmp->getNext()->getNext();
        delete(tmp->getNext());
        tmp->setNext(tmpNext);
        size--;
        return 1;
    }
    return 0;
}

template <typename T> int LinkedList<T>::deleteLastData() {
    return deleteData(size - 1);
}
