#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval) {
    val = newval;
    left = NULL;
    right = NULL;
}

int BinarySearchTree::getNodeDepth(Node* n) const {
    // Declare variables
    int leftDepth = 0;
    int rightDepth = 0;

    if( n == NULL) {
        return -1;
    }
    else {
        // Get the depth of the left subtree
        leftDepth = getNodeDepth(n->left);
        // Get the depth of the right subtree
        rightDepth = getNodeDepth(n->right);
    }
    // Add one to the right and left depth for the root
    rightDepth++;
    leftDepth++;

    // Check which depth is larger and return its value
    if (rightDepth > leftDepth)
        return rightDepth;
    else
        return leftDepth;
}

BinarySearchTree::BinarySearchTree() {
    root_ = NULL;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree() {
    while(size_)
        remove(root_->val);
}

unsigned int BinarySearchTree::size() const {
    // Return size
    return size_;
}

DataType BinarySearchTree::max() const {
    // Set a node to the beginning of the list
    Node* curr = root_;
    // Iterate through the list moving to the right
    while( curr->right != NULL) {
        curr = curr->right;
    }
    // Return the most right element
    return curr -> val;
}

DataType BinarySearchTree::min() const {
    // Set a node to the beginning of the list
    Node* curr = root_;
    // Iterate through the list moving to the right
    while( curr->left != NULL) {
        curr = curr->left;
    }
    // Return the leftmost element
    return curr -> val;
}

unsigned int BinarySearchTree::depth() const {
    return getNodeDepth(root_);
}

void BinarySearchTree::print() const {
    // Use recursion to iterate through the list.
    Node* leftNode = root_->left;
    Node* rightNode = root_->right;

    // Print the value at each node.
    cout << leftNode->val;
    cout << rightNode->val;
}

bool BinarySearchTree::exists(DataType val) const {
    // Declare a current node to traverse the tree
    Node* curr = root_;

    // Traverse until root reaches to end
    while (curr != NULL) {
        // If the value is found
        if(curr->val == val) {
            return true;
        }
            // If val is larger, move right
        else if (curr->val < val) {
            curr = curr->right;
        }
            // If val is smaller, move left
        else if (curr->val > val)
            curr = curr->left;
    }
    // If the val was not found
    return false;
}

Node* BinarySearchTree::getRootNode() {
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress() {
    return &root_;
}

bool BinarySearchTree::insert(DataType val) {
    // Check if the value is already in the tree
    if(exists(val)) {
        return false;
    }

    // Create a new node with the val to insert
    Node* newInsert = new Node(val);

    // If the tree is empty, set the root to val
    if (root_ == NULL) {
        root_ = newInsert;
    }

    else {
        // If there are elements, create two nodes to traverse through the list
        Node* curr = root_;
        Node* prev = NULL;

        while(curr != NULL) {
            prev = curr;
            // If the val is higher than value at the current node, go right
            if(val > curr->val) {
                curr = curr->right;
            }
                // If the val is lower than value at the current node, go left
            else {
                curr = curr->left;
            }
        }

        // Set the value in the appropriate position and return true
        if(val > prev->val) {
            prev -> right = newInsert;
        }
        else {
            prev -> left = newInsert;
        }
    }
    // Increment the size
    size_++;
    //Successful
    return true;
}

Node* findPredecessor(Node* ptr) {
    // Declare a current node to traverse the tree
    Node* curr = ptr;
    // Go to the left subtree
    curr = curr->left;
    // Go to rightmost value of the left subtree
    while (curr->right != NULL) {
        curr = curr->right;
    }
    // Return the predecessor
    return curr;
}

bool BinarySearchTree::remove(DataType val) {

    // Ensure that the val exists in the tree
    if (exists(val) == false) {
        return false;
    }

    // If the root is the only element in the tree
    if (size_ == 1) {

        delete root_;
        root_ = NULL;
        size_--;
        return true;
    }

    // Declare two nodes to traverse the tree
    Node* curr = root_;
    Node* prev;

    // Find the target node to remove
    while( curr-> val != val) {
        prev = curr;
        // if val is larger, move to the right,
        if (val > curr->val) {
            curr = curr->right;
        }
            // if val is smaller, move to the left
        else {
            curr = curr->left;
        }
    }

    // If it is a leaf node, remove it from the tree
    if(curr->left == NULL && curr->right == NULL) {
        // Check which child the target node is, and set that pointer to NULL
        if(prev->right == curr && prev-> right != NULL) {
            prev->right = NULL;
        }
        else {
            prev->left = NULL;
        }
        delete curr;

        // Decrement size
        size_--;
        // Successful
        return true;
    }

    //If the node has two children
    if(curr->right != NULL && curr->left != NULL) {
        // Create a node to traverse the list and a node to mark the target value to be deleted
        Node *predecessor;

        // To find the predecessor, go to the left subtree
        while (curr->left != NULL) {
            prev = curr;
            predecessor = curr->left;

            // Go to the rightmost value of the left subtree
            while (predecessor->right != NULL) {
                prev = predecessor;
                predecessor = predecessor->right;
            }
            // Copy the predecessor to the current target node
            curr->val = predecessor->val;
            curr = predecessor;
        }
    }

    // If the node has only one child and it is to the right
    if(curr->left != NULL && curr->right == NULL) {
        // The current node is a left child of its parent
        if(prev->left == curr) {
            // The current node's parent points at the current nodes child
            prev->left = curr->left;
        }
        else {
            prev->right = curr->left;
        }
    }
        // The node has one child to the right
    else  {
        // The curr node is a left child of its parent
        if(prev->left == curr) {
            // Make the parent point at the child's child
            prev->left = curr->right;
        }
            // The curr node is a right child of the parent
        else {
            // Make the parent point at the child's child
            prev->right = curr->right;
        }
    }
    // Decrement
    size_--;
    // Successful
    return true;
}