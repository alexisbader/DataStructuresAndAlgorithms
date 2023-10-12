#include "dynamic-stack.h"
#include <iostream>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -999;

DynamicStack::DynamicStack()
{
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity)
{
    capacity_ = capacity;
    init_capacity_ = capacity;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack()
{
    delete items_;
}

bool DynamicStack::empty() const
{
    // If size is zero, the stack is empty
    if( size_ == 0) {
        return true;
    }
    else{
        return false;
    }
}

int DynamicStack::size() const
{
    // Return the number of elements in the stack
    return size_;
}

void DynamicStack::push(StackItem value) {
    // Increase capacity if there are too many elements
    if(size_ >= capacity_) {
        capacity_ = capacity_ * 2;

        // Create a new stack with updated capacity
        StackItem* new_stack = new StackItem[capacity_];
        // Fill the new stack with the elements in the original stack iteratively
        for( int i = 0; i < size_; i++) {
            new_stack[i] = items_[i];
        }
        // Delete the old stack
        delete [] items_;
        // Rename the new stack
        items_ = new_stack;
    }

    // Add a new element to the stack
    items_[size_] = value;
    // Increment size
    size_++;
}

DynamicStack::StackItem DynamicStack::pop() {
    // Check for stack underflow
    if(size_ <= 0) {
        cout << "Stack Underflow";
        return EMPTY_STACK;
    }
    // If there are elements in the list set a value for the top of the list
    StackItem top = items_[size_-1];
    // Decrement size
    size_--;

    // If the size is one quarter of the storage capacity, half the capacity
    if((size_ <= capacity_ / 4) && (capacity_ / 2 >= init_capacity_)) {
        capacity_ = capacity_ / 2;

        // Create a new stack with updated capacity
        StackItem* new_stack = new StackItem[capacity_];
        // Fill the new stack with the elements in the original stack iteratively
        for( int i = 0; i < size_; i++) {
            new_stack[i] = items_[i];
        }
        // Delete the old stack
        delete [] items_;
        // Rename the new stack
        items_ = new_stack;
    }
    return top;
}

DynamicStack::StackItem DynamicStack::peek() const {
    // If the stack is empty, return the constant
    if(size_ == 0) {
        return EMPTY_STACK;
    }
    // If the stack has elements, return the value at the top element
    else {
        return items_[size_-1];
    }
}

void DynamicStack::print() const
{
    for( int i = 0; i < size_; i++) {
        cout << items_[i] << " ";
    }
}
