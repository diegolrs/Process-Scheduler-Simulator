#pragma once

#include <iostream>
#include "QueueNode.hpp"

template <typename T>
class Queue
{
    public:
        Queue();
        Queue<T>* Copy();

        bool IsEmpty();
        int Length(); 
        bool Contains(T value);

        void Enqueue(T value);
        T Dequeue();
        T Peek();
        void Clear();
    private:
        QueueNode<T> *head;
        int nElements;

        QueueNode<T> *GetTail();
};

template <typename T>
Queue<T>::Queue()
{
    head = NULL_NODE;
    nElements = 0;
}

template <typename T>
Queue<T>* Queue<T>::Copy()
{
    Queue<T>* copy = new Queue<T>();

    for(int i = 0; i < Length(); i++)
    {
        T item = Dequeue();
        copy->Enqueue(item);
        Enqueue(item);
    }

    return copy;
}

template <typename T>
bool Queue<T>::IsEmpty()
{
    return nElements == 0 || head == NULL_NODE;
}

template <typename T>
int Queue<T>::Length()
{
    return nElements;
}

template <typename T>
bool Queue<T>::Contains(T value)
{
    if (IsEmpty())
    {
        return false;
    }

    QueueNode<T> *aux = head;
    while (aux != NULL_NODE)
    {
        if (aux->GetContent() == value)
        {
            return true;
        }
        aux = aux->GetNextNode();
    }
    return false;
}

template <typename T>
void Queue<T>::Enqueue(T value)
{
    QueueNode<T> *newNode = new QueueNode<T>();
    newNode->SetContent(value);

    if(IsEmpty())
        head = newNode;
    else
    {
        QueueNode<T> *tail = GetTail();
        if(tail != NULL_NODE)
        {
            tail->SetNextNode(newNode);
        }
    }

    nElements++;
}

// Returns and remove head
template <typename T>
T Queue<T>::Dequeue()
{
    if(IsEmpty())
        return DEFAULT_NODE_VALUE;

    QueueNode<T> *aux = head;
    T headContent = head->GetContent();

    if (nElements == 1)
    {
        head = NULL_NODE;
    }
    else
    {
        head = aux->GetNextNode();
    }

    nElements--;
    delete aux;
    return headContent;
}

// Returns head without remove from Queue
template <typename T>
T Queue<T>::Peek()
{
    if(IsEmpty())
        return DEFAULT_NODE_VALUE;

    return head->GetContent();
}

template <typename T>
void Queue<T>::Clear()
{
    QueueNode<T>* currentNode = this->head;

    while(currentNode)
    {
        QueueNode<T>* nextNode = currentNode->GetNextNode();
        delete currentNode;
        currentNode = nextNode;
        nElements--;
    }
}

template <typename T>
QueueNode<T>* Queue<T>::GetTail()
{
    if(IsEmpty())
        return NULL_NODE;

    QueueNode<T> *aux = this->head;
    while (aux->GetNextNode() != NULL_NODE)
    {
        aux = aux->GetNextNode();
    }
    return aux;
}