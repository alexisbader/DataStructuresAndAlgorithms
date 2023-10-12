#include "doubly-linked-list.h"
#include <iostream>
using namespace std;

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = NULL;
    prev = NULL;
}

DoublyLinkedList::DoublyLinkedList() {
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList() {
    Node* cur = head_;
    Node* before;

    while(cur != NULL) {
        before = cur;
        cur = cur->next;

        delete before;
    }

    head_ = NULL;
    tail_ = NULL;
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if(size_ == 0) {
        return true;
    }
    else return false;
}

bool DoublyLinkedList::full() const
{
    if( size_ == CAPACITY ) {
        return true;
    }
    else return false;
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const {
   // If index is invalid, return last element
    if(index > size_-1) {
        // Return the last element
        return tail_->value;
    }
    // If the index is valid
    Node* target = getNode(index);
    return target-> value;

}

unsigned int DoublyLinkedList::search(DataType value) const
{
    // Create a new node at the start of the list
    Node* curr = head_;
    // Iterate through the list
    for (int i = 0; i < size_; i++) {
        if( curr->value == value) {
            return i;
        }
        curr = curr->next;
    }
    // If the value is not found, return the size
    return size_;

}

void DoublyLinkedList::print() const
{
    // Set the first node.
    Node* curr = head_;

    // Iterate until we're at the end.
    cout << "LinkedList: ";
    while (curr != NULL) {
        cout << curr->value << " ";
        curr = curr->next;
    }
    cout << endl << endl;
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const {
    // Return a pointer to the node at the index

    // If the index is invalid
    if(index > size_-1) {
        return NULL;
    }

    //If the index is in range
    Node* curr = head_;
    for(int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index) {
    // Check if insert is valid
    if( size_ == CAPACITY || index > size_) {
        return false;
    }
    // Create a new node to insert
    Node* myNode;
    myNode = new Node(value);

    // If the index is the first position
    if(index == 0) {
       if(empty()) {
           head_ = myNode;
           tail_ = myNode;
       }
       else {
           myNode-> next = head_;
           head_->prev = myNode;
           head_ = myNode;
       }
    }
    // If the index is in the last position
    else if(index == size_) {
        myNode->prev = tail_;
        tail_->next = myNode;
        tail_ = myNode;
    }

    // If index is in the middle of the list
    else {
        // If the list is empty
        if(empty()) {
            head_ = myNode;
            tail_ = myNode;
            return true;
        }
        // If there is only one element in the list
        if(size_ == 1) {
            head_->next = myNode;
            myNode->prev = head_;
        }
        // If there is more than one element in the list
        else {
            // Create a node to traverse the list
            Node* curr = head_;
            // Iterate through the list until the index is reached
            for( int i = 0; i < index-1; i++) {
                curr = curr->next;
            }
            // Insert the new node
            myNode->prev = curr;
            myNode->next = curr->next;
            curr->next = myNode;
            curr->next->prev = myNode;
        }
    }

    // Increment size
    size_++;

    // Successful
    return true;
}

bool DoublyLinkedList::insert_front(DataType value) {
    // Check if insert is valid
    if( size_ == CAPACITY ) {
        return false;
    }

    // Create a new node to insert
    Node* myNode;
    myNode = new Node(value);

    // If the list is empty
    if(size_ == 0) {
        head_ = myNode;
        tail_ = myNode;
    }
    else {
        // Insert the new node
        myNode->prev = NULL;
        myNode->next = head_;

        // If list is empty
        if(empty()) {
            tail_ = myNode;
        }
            // If list has elements already
        else {
            head_->prev = myNode;
        }
        // Set the head as the inserted node
        head_ = myNode;
    }

    // Increment the size of the list
    size_++;

    // Successful
    return true;
}

bool DoublyLinkedList::insert_back(DataType value) {
    // Check if insert is valid
    if( size_ == CAPACITY ) {
        return false;
    }

    // Create a new node to insert
    Node* myNode;
    myNode = new Node(value);

    // Insert the new node
    myNode->prev = tail_;
    myNode->next = NULL;

    // If the list is empty
    if(empty()) {
        head_ = myNode;
        myNode->prev = NULL;
    }
    // If the list has some elements
    else {
        tail_->next = myNode;
    }
    // Set tail as inserted node
    tail_ = myNode;

    // Increment size
    size_++;

    // Successful
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    // Check is remove is valid
    if(index >= size_ || size_ == 0 ) {
        return false;
    }
    // If the index is the front element
    if(index == 0) {
        return remove_front();
    }
    // If the index is the last element
    if(index == size_-1) {
        return remove_back();
    }
    // If the index is in the middle
    Node* curr = head_;
    // Transverse through the list to get to the index
    for(int i = 0; i < index; i++) {
        curr = curr->next;
    }
    // The previous node's next will point at the next node
    curr->prev->next = curr->next;
    // The next node's prev will point at the prev node
    curr->next->prev = curr->prev;

    //Delete the removed node
    delete(curr);

    // Successful
    return true;
}

bool DoublyLinkedList::remove_front() {
    // Check is remove is valid
    if(size_ == 0) {
        return false;
    }
    // If there is only one element in the list
    if(size_ == 1) {
        delete head_;
        head_ = NULL;
        tail_ = NULL;
    }
    else {
        // Set second element as head
        Node* curr = head_;
        head_ = head_->next;
        delete curr;
    }
    // Decrement size
    size_--;

    // Successful
    return true;
}

bool DoublyLinkedList::remove_back() {
    // Check is remove is valid
    if(size_ == 0) {
        return false;
    }
    // If there is only one element in the list
    if(size_ == 1) {
        head_ = NULL;
        tail_ = NULL;
    }
    else{
        // Make the second last element the tail
        tail_ = tail_->prev;
        tail_->next = NULL;
    }
    // Decrement size
    size_--;

    // Successful
    return true;

}

bool DoublyLinkedList::replace(unsigned int index, DataType value) {
    if(empty() || index >= size_){
        return false;
    }
    Node* curr = getNode(index);
    curr->value = value;
    return true;
}
