#ifndef TASK1_A_STAR_ALGORITHM_PRIORITY_QUEUE_H
#define TASK1_A_STAR_ALGORITHM_PRIORITY_QUEUE_H

#include <queue>
#include <vector>
#include <cstddef>

template<typename T>
class PriorityQueue {
private:
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;

public:
    void push(const T& item);
    T pop();
    bool empty() const;
    size_t size() const;
};

#endif //TASK1_A_STAR_ALGORITHM_PRIORITY_QUEUE_H