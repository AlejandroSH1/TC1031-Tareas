/*
 * 4 Estructura Lineal Lista Doble
 * Alfredo Alejandro Soto Herrera
 * A01711368
 * 2/09/2024
 */

#ifndef DLIST_H
#define DLIST_H

#include <iostream>

using namespace std;

template <class T> class DList;

template <class T>
class DLink {
private:
    DLink(T);

    T       value;
    DLink<T> *previous;
    DLink<T> *next;

    friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val) : value(val), previous(0), next(0) {}


template <class T>
class DList {
public:
    DList();

    bool empty() const;
    void insertion(T);
    T    removeFirst();
    T    search(int) const;
    void update(int, T);
    T    deleteAt(int);
    string toStringForward() const;
    string toStringBackward() const;

private:
    DLink<T> *head;
    DLink<T> *tail;
    int      size;
};

template <class T>
DList<T>::DList() : head(0), tail(0), size(0) {}

template <class T>
bool DList<T>::empty() const {
    return (head == 0 && tail == 0);
}

template <class T>
void DList<T>::insertion(T val){
    DLink<T> *newLink;
    newLink = new DLink<T>(val);
    if (empty()) {
        head = newLink;
        tail = newLink;
    } else {
        tail->next = newLink;
        newLink->previous = tail;
        tail = newLink;
    }
    size++;
}

template <class T>
T DList<T>::removeFirst(){
    T val;
    DLink<T> *p;
    p = head;
    val = p->value;
    if (head == tail) {
        head = 0;
        tail = 0;
    } else {
        head = p->next;
        p->next->previous = 0;
    }
    delete p;
    size--;

    return val;
}

template <class T>
T DList<T>::search(int val) const {
    DLink<T>* p = head;
    int index = 0;

    while (p != nullptr) {
        if (p->value == val){
            return index;
        }
        p = p->next;
        index++;
    }
    return -1;
}

template <class T>
void DList<T>::update(int indice, T val){
    int pos;
    DLink<T> *p;
    if (indice == 0) {
        head->value = val;
    } else {
        p = head;
        pos = 0;
        while (pos != indice) {
            p = p->next;
            pos++;
        }
        p->value = val;
    }   
}

template <class T>
T DList<T>::deleteAt(int index) {
    int pos;
    T val;
    DLink<T> *p;
    if (index == 0) {
        return removeFirst();
    }
    p = head;
    pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }
    val = p->value;
    p->previous->next = p->next;
    if (p->next != 0) {
        p->next->previous = p->previous;
    }
    size--;
    delete p;
    return val;
}

template <class T>
    string DList<T>::toStringForward() const {
        stringstream aux;
        DLink<T> *p;
        p = head;
        aux << "[";
        while (p != 0) {
            aux << p->value;
            if (p->next != 0) {
                aux << ", ";
            }
            p = p->next;
        }
        aux << "]";
        return aux.str();
    }

    template <class T>
    string DList<T>::toStringBackward() const {
        stringstream aux;
        DLink<T> *p;
        p = tail;
        aux << "[";
        while (p != 0) {
            aux << p->value;
            if (p->previous != 0) {
                aux << ", ";
            }
            p = p->previous;
        }
        aux << "]";
        return aux.str();
    }

#endif