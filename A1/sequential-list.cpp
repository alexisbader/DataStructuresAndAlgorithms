

#include <iostream>
#include "sequential-list.h"

// Constructor
SequentialList::SequentialList(unsigned int cap) {
    // Declare the member variables
    capacity_ = cap;
    size_ = 0;
    data_ = new DataType[cap];
}

// Deconstructor
SequentialList::~SequentialList() {
    // Free the mem
    delete [] data_;
    data_ = NULL;
}

unsigned int SequentialList::size() const {
    // Return size
    return size_;
}

unsigned int SequentialList::capacity() const {
    // Return capacity (max size)
    return capacity_;
}

bool SequentialList::empty() const {
    // If it is empty
    if(size_ == 0) {
        return true;
    }
    // If it is not empty
    return false;
}

bool SequentialList::full() const {
    // If every available space is filled
    if (size_ == capacity_) {
        return true;
    }
    // If some of the spaces are empty
    else {
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const {
   // If the index is outside of the size of the list, return the last element
    if (index > size_ - 1) {
        return data_[size_ - 1];
    }
    // Return the data at index
    return data_[index];
}

unsigned int SequentialList::search(DataType val) const {
   // Iterate through the list
    for (int i = 0; i < size_; i++) {
        // If the val and data_ match, return the position
        if(data_[i] == val) {
            return i;
        }
    }
    // The val is not found, return size
    return size_;
}

void SequentialList::print() const {
    // Iterate through the list, print each element
    for (int i = 0; i < size_; i++)
    {
        std::cout << data_[i] << " ";
    }
}

bool SequentialList::insert(DataType val, unsigned int index) {
    // If the list does not have capacity for an additional element
    if (full() || index > size_ || index < 0) {
        return false;
    }
    // Iterate through the list
    for (int i = size_; i > index; i--) {
        // Shift the elements forward
        data_[i] = data_[i - 1];
    }
    // Set the data at that index to val
    data_[index] = val;

    // Increment size
    size_++;

    // Insert was successful, return true
    return true;
}

bool SequentialList::insert_front(DataType val)
{
    // If the capacity has already been reached
    if (full()) {
        return false;
    }

    // Check for an empty list
    if (size_ == 0) {

        // Set the zero index to val
        data_[0] = val;

        // Increment size
        size_++;
    }

    // When there are elements in the list
    else {
        // Iterate through the array
        for (int j = size_; j > 0; j--) {

            // Push all of the elements forward
            data_[j] = data_[j - 1];
        }

        // Set the zero index to val
        data_[0] = val;

        // Increment size
        size_++;
    }

    // Insertion was successful, return true
    return true;
}

bool SequentialList::insert_back(DataType val)
{
    // If the capacity has already been reached
    if (full()) {
        return false;
    }

    // Set the last element equal to val
    data_[size_] = val;

    // Increment size
    size_++;

    // Insertion was successful
    return true;
}

bool SequentialList::remove(unsigned int index)
{
    // If nothing bad happens
    if (size_ != 0 && index < size_) {

        // Increment
        for (int i = index; i < size_; i++) {

            // Shift
            data_[i] = data_[i + 1];
        }

        // Decrement size
        size_--;
        return true;
    }

    // If it was unsuccessful
    return false;
}

bool SequentialList::remove_front()
{
    if (size_ != 0) {

        // Iterate
        for (int i = 0; i < size_; i++) {
            data_[i] = data_[i + 1];
        }

        // Decrement size
        size_--;

        // Success
        return true;
    }

    // Empty case
    else {
        return false;
    }
}

bool SequentialList::remove_back()
{
    if (size_ != 0) {

        // Removes the last element
        size_--;

        return true;
    }

    // Empty array case
    else {

        return false;
    }
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (size_ != 0) {

        // Overwrite the data at the index
        data_[index] = val;
        return true;

    }

    // Unsuccessful
    return false;
}

