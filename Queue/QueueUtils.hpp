#pragma once
#include <vector>
#include <algorithm>
#include "../Queue/Queue.hpp"

namespace QueueUtils
{
    template <typename T>
    std::vector<T> to_std_vector(Queue<T>* queue)
    {
        std::vector<T> vector;

        for(int i = 0; i < queue->Length(); i++)
        {
            T item = queue->Dequeue();
            vector.push_back(item);
            queue->Enqueue(item);
        }

        return vector;
    }

    template <typename T>
    Queue<T>* from_std_vector(std::vector<T> vector)
    {
        Queue<T>* queue = new Queue<T>();

        for(int i = 0; i < vector.size(); i++)
        {
            queue->Enqueue(vector[i]);
        }

        return queue;
    }

    template <typename T>
    Queue<T>* sort_queue(Queue<T>* queue, bool(*sortingFunction)(T, T))
    {
        std::vector<T> _vector = QueueUtils::to_std_vector(queue);
        std::sort(_vector.begin(), _vector.end(), sortingFunction);   
        return QueueUtils::from_std_vector(_vector);
    }
}