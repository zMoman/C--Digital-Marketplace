#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include "defs.h" 

using namespace std;

template<typename T>
class List {
public:
    List(); 
    ~List(); 

    List& operator+=(const T& item); 
    List& operator-=(const T& item); 
    T& operator[](int index); 
    const T& operator[](int index) const; 
    int getSize() const;
    bool isFull() const;
    void clear();

private:
    int numElements;
    T* elements;
};

template<typename T>
List<T>::List() : numElements(0), elements(new T[MAX_ARRAY]) {}

template<typename T>
List<T>::~List() {
    delete[] elements;
}

template<typename T>
List<T>& List<T>::operator+=(const T& item) {
    if (!isFull()) {
        elements[numElements++] = item;
    }
    return *this;
}

template<typename T>
List<T>& List<T>::operator-=(const T& item) {
    int index = 0;
    while (index < numElements) {
        if (elements[index] == item) {
            for (int j = index; j < numElements - 1; ++j) {
                elements[j] = elements[j + 1];
            }
            --numElements;
            return *this;
        }
        ++index;
    }
    return *this;
}

template<typename T>
T& List<T>::operator[](int index) {
    if (index < 0 || index >= numElements) {
        cerr << "List index out of bounds" << endl;
        exit(1);
    }
    return elements[index];
}

template<typename T>
const T& List<T>::operator[](int index) const {
    if (index < 0 || index >= numElements) {
        cerr << "List index out of bounds" << endl;
        exit(1);
    }
    return elements[index];
}

template<typename T>
int List<T>::getSize() const {
    return numElements;
}

template<typename T>
bool List<T>::isFull() const {
    return numElements >= MAX_ARRAY;
}

template<typename T>
void List<T>::clear() {
    numElements = 0;
}

#endif // LIST_H
