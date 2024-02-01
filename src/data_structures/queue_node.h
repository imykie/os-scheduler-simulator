#pragma once

#define DEFAULT_NODE_VALUE T()
#define NULL_NODE nullptr

template <typename T>
class QueueNode {
   private:
    T content;
    QueueNode<T> *next;

   public:
    QueueNode<T>();
    T GetContent();
    void SetContent(T value);
    QueueNode *GetNextNode();
    void SetNextNode(QueueNode *nextNode);
};

template <typename T>
QueueNode<T>::QueueNode() {
    this->content = DEFAULT_NODE_VALUE;
    this->next = NULL_NODE;
}

template <typename T>
T QueueNode<T>::GetContent() {
    return content;
}

template <typename T>
void QueueNode<T>::SetContent(T value) {
    this->content = value;
}

template <typename T>
QueueNode<T> *QueueNode<T>::GetNextNode() {
    return next;
}

template <typename T>
void QueueNode<T>::SetNextNode(QueueNode<T> *nextNode) {
    this->next = nextNode;
}