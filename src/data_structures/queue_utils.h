#pragma once

#include <algorithm>
#include <vector>

#include "queue.h"

namespace QueueUtils {
    template <typename T>
    std::vector<T> ConvertToVector(Queue<T>* queue) {
        std::vector<T> vector;
        for (int i = 0; i < queue->Length(); ++i) {
            T item = queue->Dequeue();
            vector.push_back(item);
            queue->Enqueue(item);
        }
        return vector;
    }

    template <typename T>
    Queue<T>* ConvertFromVector(std::vector<T> vector) {
        Queue<T>* queue = new Queue<T>();
        for (T item : vector) queue->Enqueue(item);
        return queue;
    }

    template <typename T>
    Queue<T>* Sort(Queue<T>* queue, bool (*sort_function)(T, T)) {
        std::vector<T> vector = ConvertToVector(queue);
        std::sort(vector.begin(), vector.end(), sort_function);
        return ConvertFromVector(vector);
    }
}  // namespace QueueUtils