#pragma once

#include <algorithm>
#include <vector>

#include "queue.h"

namespace QueueUtils {
    template <typename T>
    std::vector<T> ConvertToVector(Queue<T>* queue);

    template <typename T>
    Queue<T>* ConvertFromVector(std::vector<T> vector);

    template <typename T>
    Queue<T>* Sort(Queue<T>* queue, bool (*sort_function)(T, T));
}  // namespace QueueUtils