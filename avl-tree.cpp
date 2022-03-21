#include "avl-tree.h"
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

// Function to find the maximum depth of the tree
int AVLTree::depthBelow(Node *n)
{
    // Node is null
    if (n == nullptr) {

        // Return depth of 0
        return 0;
    }

    // Recursively find depth of left and right subtrees
    int leftDepth = depthBelow(n->left);
    int rightDepth = depthBelow(n->right);

    // If left subtree is deeper
    if (leftDepth > rightDepth) {
        return leftDepth + 1;
    }

        // If right subtree is deeper
    else {
        return rightDepth + 1;
    }
}

// Carries out a single left rotation on the subtree, then returns true on success.
bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild) {

    Node *unbalancedNode = nullptr;

    // Parent node is the nullptr
    if (parentNode == nullptr) {
        // We're rotating around the root
        unbalancedNode = getRootNode();
    }
    // isLeftChild is true
    else if (isLeftChild) {
        // We're rotating around the left child
        unbalancedNode = parentNode->left;
    }
    // isLeftChild is false
    else {
        // We're rotating around the right child
        unbalancedNode = parentNode->right;
    }

    // Preform the single Left rotation
    Node *S = unbalancedNode->right;
    Node *B = S->left;
    S->left = unbalancedNode;
    unbalancedNode->right = B;

    // Reassign the root
    if(parentNode == nullptr) {
        Node **root = getRootNodeAddress();
        *root = S;
    }

    // Update the parent node depending on left or right child
    else if (isLeftChild) {
        parentNode->left = S;

    } else {
        parentNode->right = S;
    }
    // We've preformed a single left rotation, return true
    return true;
}

// Carries out a single right rotation on the subtree, then returns true on success.
bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild) {

    Node *unbalancedNode = nullptr;

    // Parent node is the nullptr
    if (parentNode == nullptr) {
        // We're rotating around the root
        unbalancedNode = getRootNode();
    }

    // isLeftChild is true
    else if (isLeftChild) {
        // We're rotating around the left child
        unbalancedNode = parentNode->left;
    }
        // isLeftChild is false
    else {
        // We're rotating around the right child
        unbalancedNode = parentNode->right;
    }

    // Preform the single right rotation
    Node *S = unbalancedNode->left;
    Node *B = S->right;
    S->right = unbalancedNode;
    unbalancedNode->left = B;

    if(parentNode == nullptr) {
        Node **root = getRootNodeAddress();
        *root = S;
    }

    else if (isLeftChild) {
        // We're rotating around the left child
        parentNode->left = S;

    } else {
        // We're rotating around the right child
        parentNode->right = S;
    }

    // We've preformed a single right rotation, return true
    return true;
}

bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild) {

    Node *unbalancedNode = getRootNode();

    // We are not rotating around the root
    if (parentNode != nullptr){
        // The node is a left child
        if (isLeftChild) {
            // Perform single left, then single right rotations
            singleLeftRotation(parentNode->left, true);
            singleRightRotation(parentNode, true);
        }
        // The node is a right child
        if (!isLeftChild) {
            // Perform single left, then single right rotations
            singleLeftRotation(parentNode->right, true);
            singleRightRotation(parentNode, false);
        }
    }
    // The node is the root node
    else {
        // Perform single left, then single right rotations
        singleLeftRotation(unbalancedNode, true);
        singleRightRotation(parentNode, isLeftChild);
    }
    return true;
}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    Node *unbalancedNode = getRootNode();

    // We are not rotating around the root
    if (parentNode != nullptr){
        // The node is a left child
        if (isLeftChild) {
            // Perform single right, then single left rotations
            singleRightRotation(parentNode->left, false);
            singleLeftRotation(parentNode, true);
        }
        // The node is a right child
        if (!isLeftChild) {
            // Perform single right, then single left rotations
            singleRightRotation(parentNode->right, false);
            singleLeftRotation(parentNode, false);
        }
    }
    // The node is a root node
    else {
        // Perform single right, then single left rotations
        singleRightRotation(unbalancedNode, false);
        singleLeftRotation(parentNode, isLeftChild);
    }
    return true;
}

std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val) {
    // Create a stack to store the path to the node
    stack<Node*> *path = new stack<Node*>();

    // Push a nullptr to the end of the path (good practice, indicates end) TRY TO REMOVE THIS AFTER
    Node* end = nullptr;
    path->push(end);

    // Create a pointer to the root node
    Node *currentNode = getRootNode();

    // While the current node is not null
    while (currentNode->val != val) {
        // Push the current node onto the stack
        path->push(currentNode);

        // If the current node's value is greater than the value we're looking for
        if (val < currentNode->val) {
            // Move to the left child
            currentNode = currentNode->left;
        }

        // If the current node's value is less than the value we're looking for
        else if (val > currentNode->val) {
            // Move to the right child
            currentNode = currentNode->right;
        }
        else {
            break;
        }
    }
    // Return the path to the node
    return path;
}

// generic function to updated tree balance of insertion/deletion
bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    // Create a pointer to the node we're updating
    Node *currentNode = nullptr;
    Node *parent = nullptr;
    int leftChild = 0;

    // While the stack is not empty
    while (pathToNode->top() != nullptr) {

        // Get the top node off the stack
        currentNode = pathToNode->top();

        // Pop the top node off the stack
        pathToNode->pop();

        // We have a new top after popping so we can get the parent node
        parent = pathToNode->top();

        // Parent node is nullptr
        if (parent == nullptr) {
            //  --> leftChild must be false
            leftChild = 0;
        }

        // When parent !nullptr
        else {
            // We check if the left value is the current node
            if (parent -> left == currentNode) {
                leftChild = 1;
            }
            else {
                leftChild = 0;
            }
        }

        // Get the current node's balance
        int balance = depthBelow(currentNode->left) - depthBelow(currentNode->right);

        // If the current node's balance is greater than 1
        if (balance > 1) {

            int leftBal = depthBelow(currentNode->left->left) - depthBelow(currentNode->left->right);

            if (leftBal < 0) {
                // Perform a right left rotation
                leftRightRotation(parent, leftChild);
            }
            else {
                // Preform a single right rotation
                singleRightRotation(parent, leftChild);
            }
        }

        // If the current node's balance is less than -1
        else if (balance < -1) {
            int rightBal = depthBelow(currentNode->right->left) - depthBelow(currentNode->right->right);

            // If the current node's right child's value is less than the value we're inserting
            if (rightBal < 0) {

                singleLeftRotation(parent, leftChild);
            }

                // If the current node's right child's value is greater than the value we're inserting
            else {
                // Perform a right left rotation
                rightLeftRotation(parent, leftChild);
            }
        }
    }

    return true;
}

bool AVLTree::insert(DataType val) {

    // Inesrt the node into the tree
    BinarySearchTree::insert(val);

    // Create a stack to store the path to the node
    stack<BinarySearchTree::Node*> *pathToNode = pathToNodeStack(val);

    // Update the balance of the tree
    return updateNodeBalance(pathToNode, val);
}

bool AVLTree::remove(DataType val) {

    // Create a stack to store the path to the node
    std::stack<BinarySearchTree::Node*> *pathToNode = pathToNodeStack(val);

    // Remove the node from the tree
    BinarySearchTree::remove(val);

    // Update the balance of the tree
    return updateNodeBalance(pathToNode, val);
}
