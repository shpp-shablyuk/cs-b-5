#ifndef CUSTOMQUEUE_H
#define CUSTOMQUEUE_H

#include <iostream>

template<typename ValueType>
class CustomQueue
{
public:
    CustomQueue();

    ~CustomQueue();

    bool empty() const;

    int size() const;

    ValueType& front();

    ValueType& back();

    void push(ValueType value);

    void pop();


    CustomQueue(const CustomQueue<ValueType> & src);

    CustomQueue<ValueType> & operator=(const CustomQueue<ValueType> & src);

private:
    static const int INITIAL_CAPACITY = 5;

    ValueType* array;
    int capacity;
    int head;
    int tail;

    void expandCapacity();
    void deepCopy(const CustomQueue<ValueType> & src);
};

template<typename ValueType>
CustomQueue<ValueType>::CustomQueue() {
    capacity = INITIAL_CAPACITY;
    array = new ValueType[capacity];
    head = tail = 0;
}

template<typename ValueType>
CustomQueue<ValueType>::~CustomQueue() {
    delete [] array;
}

template<typename ValueType>
bool CustomQueue<ValueType>::empty() const {
    return head == tail;
}

template<typename ValueType>
int CustomQueue<ValueType>::size() const {
    return (tail + capacity - head) % capacity;
}

template<typename ValueType>
ValueType& CustomQueue<ValueType>::front() {
    if (empty()) {
        throw "front: queue is empty";
    }
    return array[head];
}

template<typename ValueType>
ValueType& CustomQueue<ValueType>::back() {
    if (empty()) {
        throw "back: queue is empty";
    }
    return array[tail - 1];
}

template<typename ValueType>
void CustomQueue<ValueType>::push(ValueType value) {
    if (size() == capacity - 1) {
        expandCapacity();
    }
    array[tail] = value;
    tail = (tail + 1) % capacity;
}


template<typename ValueType>
void CustomQueue<ValueType>::pop() {
    if (empty()) {
        throw "pop: queue is empty";
    }

    head = (head + 1) % capacity;
}

template<typename ValueType>
void CustomQueue<ValueType>::expandCapacity() {
    int sz = size();
    ValueType *oldArray = array;
    array = new ValueType[capacity * 2];
    for (int i = 0; i < sz; i++) {
        array[i] = oldArray[(head + i) % capacity];
    }
    capacity *= 2;
    head = 0;
    tail = sz;
    delete [] oldArray;
}

template<typename ValueType>
CustomQueue<ValueType>::CustomQueue(const CustomQueue<ValueType> & src) {
   deepCopy(src);
}

template<typename ValueType>
CustomQueue<ValueType> & CustomQueue<ValueType>::operator=(const CustomQueue<ValueType> & src) {
    if (this != &src) {
        delete [] array;
        deepCopy(src);
    }
    return *this;
}

template<typename ValueType>
void CustomQueue<ValueType>::deepCopy(const CustomQueue<ValueType> & src) {
    capacity = src.capacity;
    int sz = src.size();
    array = new ValueType[capacity];
    for (int i = 0; i < sz; i++) {
        array[i] = src[(head + i) % src.capacity];
    }
    head = 0;
    tail = sz;
}


#endif // CUSTOMQUEUE_H
