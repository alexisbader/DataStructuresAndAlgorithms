#include "circular-queue.h"
#include <iostream>
using namespace std;

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -999;

CircularQueue::CircularQueue() {
    capacity_ = 16;
    size_ = 0;
    items_ = new QueueItem[capacity_];
    head_ = 0;
    tail_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity;
    size_ = 0;
    items_ = new QueueItem[capacity_];
    head_ = 0;
    tail_ = 0;
}

CircularQueue::~CircularQueue() {
    delete [] items_;
}

bool CircularQueue::empty() const {
    if(size_ == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularQueue::full() const {
    if(size_ == capacity_) {
        return true;
    }
    else {
        return false;
    }
}

int CircularQueue::size() const
{
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
    // Check if the queue is full
    if(size_ == capacity_) {
        return false;
    }
    // If the queue is not full
    else {
        // Place the new element at the back of the list
        items_[tail_] = value;
        // Move the tail back one place
        tail_ = (tail_ + 1) % capacity_;
    }
    // Increment size;
    size_++;
    // New element added successfully
    return true;
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    // Create a temporary variable for the current head to return
    QueueItem temp;

    // If the queue is empty
    if(size_ == 0) {
        return EMPTY_QUEUE;
    }
    // If queue is not empty
    else {
        temp = items_[head_];
        // Move the head back one place
        head_ = (head_ + 1) % capacity_;
    }
    // Decrement size
    size_--;
    // Element removed successfully
    return temp;
}

CircularQueue::QueueItem CircularQueue::peek() const {
    // Check if queue is empty
    if(size_ == 0) {
        return EMPTY_QUEUE;
    }
    // Return the top element
    return items_[head_];
}

void CircularQueue::print() const{
    // If the queue is empty
    if(empty()) {
        cout << "List is empty";
    }
    // If 0 element position is at the beginning or before the queue
    else if (tail_ > head_) {
        for(int i = head_; i <= tail_; i++ ) {
            cout << items_[i] << " ";
        }
    }
    // If te 0 element position is in the middle of the list
    else if( head_ > tail_) {
        // Iterate through the head to the end of the array
        for(int i = head_; i < capacity_; i++) {
            cout << items_[i] << " ";
        }
        // Iterate through the 0 element of the array to the tail
        for(int i = 0; i < tail_; i++) {
            cout << items_[i] << " ";
        }
    }
}