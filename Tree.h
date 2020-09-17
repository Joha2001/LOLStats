#pragma once
#include "Hero.h"
#include <iostream>
/*Code adapted from Gorms Analysis and Packt
  Link to websites: https://www.gormanalysis.com/blog/making-a-binary-search-tree-in-cpp/ and https://hub.packtpub.com/binary-search-tree-tutorial/
*/
using namespace std;
class Tree
{
private:
    struct Node {
        Node* left;
        Node* right;
        Hero data;
        Node(Hero data) : data(data), left(nullptr), right(nullptr) {}
    };
    Node* root;
public:
    Tree() { root = nullptr; }
    /* A utility function to insert a new node with given key in BST */
    void Insert(Hero champ) {
        if (root == nullptr) {
            this->root = new Node(champ);
        }
        else {
            this->Insert(champ, this->root);
        }
    }

    /// Insert a new value into the subtree starting at node
    void Insert(Hero champ, Node* node) {

        // Check if node's value equals val
        // If so, warn the user and then exit function
        if (stoi(champ.getId()) == stoi(node->data.getId())) {
            return;
        }

        // Check if val is < or > this node's value
        if (stoi(champ.getId()) < stoi(node->data.getId())) {
            if (node->left == nullptr) {
                // Make a new node as the left child of this node
                node->left = new Node(champ);
            }
            else {
                // Recursively call Insert() on this node's left child
                this->Insert(champ, node->left);
            }
        }
        else {
            if (node->right == nullptr) {
                // Make a new node as the right child of this node
                node->right = new Node(champ);
            }
            else {
                // Recursively call Insert() on this node's right child
                this->Insert(champ, node->right);
            }
        }
    }
    Node* Search(string champ)
    {
        if (root == nullptr) // The given key is not found in BST
            return nullptr;
        else if (stoi(root->data.getId()) == stoi(champ))         // The given key is found
            return root;
        else if (stoi(root->data.getId()) < stoi(champ))         // The given is greater than current node's key
            return Search(root->right, champ);
        else         // The given is smaller than current node's key
            return Search(root->left, champ);
    }
    Node* Search(Node* node, string champ)
    {
        if (node == nullptr) // The given key is not found in BST
            return nullptr;
        else if (stoi(node->data.getId()) == stoi(champ))         // The given key is found
            return node;
        else if (stoi(node->data.getId()) < stoi(champ))         // The given is greater than current node's key
        // The given is smaller than current node's key
            return Search(node->right, champ);
        else
            return Search(node->left, champ);
    }
};