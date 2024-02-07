#pragma once
#include "queue_node.h"

template <typename T>
class Queue {
   public:
    Queue();
    Queue<T> *Copy();
    ~Queue();
    bool IsEmpty();
    int Length();
    bool Contains(T value);
    void Enqueue(T value);
    T Dequeue();
    T Peek();
    T Rear();
    void Clear();

   private:
    QueueNode<T> *head;
    QueueNode<T> *tail;
    int size;
};

template <typename T>
Queue<T>::Queue() {
    head = NULL_NODE;
    tail = NULL_NODE;
    size = 0;
}

template <typename T>
Queue<T>::~Queue() {
    delete head;
    head = NULL_NODE;
    delete tail;
    tail = NULL_NODE;
}

template <typename T>
Queue<T> *Queue<T>::Copy() {
    Queue<T> *copy = new Queue<T>();

    for (int i = 0; i < Length(); i++) {
        T item = Dequeue();
        copy->Enqueue(item);
        Enqueue(item);
    }

    return copy;
}

template <typename T>
bool Queue<T>::IsEmpty() {
    return size == 0 || head == NULL_NODE;
}

template <typename T>
int Queue<T>::Length() {
    return size;
}

template <typename T>
bool Queue<T>::Contains(T value) {
    if (IsEmpty()) {
        return false;
    }

    QueueNode<T> *curr = head;
    while (curr != NULL_NODE) {
        if (curr->GetContent() == value) {
            return true;
        }
        curr = curr->GetNextNode();
    }

    return false;
}

template <typename T>
void Queue<T>::Enqueue(T value) {
    QueueNode<T> *newNode = new QueueNode<T>();
    newNode->SetContent(value);

    if (IsEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->SetNextNode(newNode);
        tail = tail->GetNextNode();
    }

    size++;
}

// Returns and remove head
template <typename T>
T Queue<T>::Dequeue() {
    if (IsEmpty()) return DEFAULT_NODE_VALUE;

    QueueNode<T> *curr = head;
    T content = head->GetContent();

    if (size == 1) {
        head = NULL_NODE;
        tail = NULL_NODE;
    } else {
        head = curr->GetNextNode();
    }

    size--;
    delete curr;
    return content;
}

// Returns head without remove from Queue
template <typename T>
T Queue<T>::Peek() {
    if (IsEmpty()) return DEFAULT_NODE_VALUE;
    return head->GetContent();
}

// Returns tail without remove from Queue
template <typename T>
T Queue<T>::Rear() {
    if (IsEmpty()) return DEFAULT_NODE_VALUE;
    return tail->GetContent();
}

template <typename T>
void Queue<T>::Clear() {
    QueueNode<T> *currentNode = this->head;

    while (currentNode) {
        QueueNode<T> *nextNode = currentNode->GetNextNode();
        delete currentNode;
        currentNode = nextNode;
        size--;
    }
}