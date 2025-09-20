#include "priority_queue.h"

template<typename T>
void PriorityQueue<T>::push(const T& item) {
    pq.push(item);
}

template<typename T>
T PriorityQueue<T>::pop() {
    T item = pq.top();
    pq.pop();
    return item;
}

template<typename T>
bool PriorityQueue<T>::empty() const {
    return pq.empty();
}

template<typename T>
size_t PriorityQueue<T>::size() const {
    return pq.size();
}

// Explicit template instantiation
#include "chess_state.h"
template class PriorityQueue<ChessState>;