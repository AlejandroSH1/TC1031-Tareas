/*
 * 3 Estructura Lineal Lista Ligada
 * Alfredo Alejandro Soto Herrera
 * A01711368
 * 23/09/2024
 */

#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>

using namespace std;

template <class T> class List;

template <class T>
class Link {
private:
    Link(T);
    Link(T, Link<T>*);

    T	    value;
    Link<T> *next;

    friend class List<T>;
};

template <class T>
Link<T>::Link(T val): value(val), next(0) {}

template <class T>
Link<T>::Link(T val, Link* nxt): value(val), next(nxt) {}

template <class T>
class List {
public:
    List();

    void insertion(T);
    int search(T);
    void update(int, T);
    void deleteAt(int);
    string toString() const;
private:
    Link<T> *head;
    int size;
};

template <class T>
List<T>::List(): head(0), size(0) {}

template <class T>
void List<T>::insertion(T val) {
    Link<T> *newLink, *p;

    newLink = new Link<T>(val);
    if (newLink == 0) {
        return;
    }

    if (head == 0) {
        newLink->next = head;
        head = newLink;
        size++;
        return;
    }

    p = head;
    while (p->next != 0) {
        p = p->next;
    }

    newLink->next = 0;
    p->next = newLink;
    size++;
}

template <class T>
int List<T>::search(T val) {
    Link<T> *p;
    int index;

    p = head;
    index = 0;
    while (p != 0) {
        if (p->value == val) {
            return index;
        }
        index++;
        p = p->next;
    }

    return -1;
}

template <class T>
void List<T>::update(int index, T val) {
    Link<T> *p;
    int pos;

    if (index < 0 || index >= size) {
        return;
    }

    p = head;
    pos = 0;
    while (pos != index) {
        p = p->next;
        pos++;
    }

    p->value = val;
}

template <class T>
void List<T>::deleteAt(int index) {
    Link<T> *p, *q;
    int pos;

    if (index < 0 || index >= size) {
        return;
    }

    if (index == 0) {
        p = head;
        head = head->next;
        delete p;
        size--;
        return;
    }

    p = head;
    pos = 0;
    while (pos != index) {
        q = p;
        p = p->next;
        pos++;
    }

    q->next = p->next;
    delete p;
    size--;
}

template <class T>
string List<T>::toString() const {
	stringstream aux;
	Link<T> *p;

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

#endif