#include <iostream>
#include <binary_tree.hpp>

using namespace std;
using namespace BT;

Node* BinaryTree::search(double value) {
    Node* curr_node = BinaryTree::root;

    while (curr_node->left || curr_node->right) {
        if (curr_node->value == value)
            return curr_node;
        else if (curr_node->value < value)
            curr_node = curr_node->right;
        else
            curr_node = curr_node->left;
    }
    // If value not found then return nullptr
    return curr_node;
}

void BinaryTree::insert(double value) {
    Node* parent = BinaryTree::root;
    Node* node = search(value);

    // First insert in the binary tree
    if (!parent) {
        node = new Node;
        node->value = value;
        BinaryTree::root = node;
        return;
    }

    // If node has exist then add to the number of nodes
    if (node)
        node->count++;
    else {
        while (parent->left || parent->right) {
            if (parent->value < value) {
                if (!parent->right) 
                    break;
                parent = parent->right;
            }
            else {
                if (!parent->left)
                    break;
                parent = parent->left;
            }
        }

        node = new Node;
        node->value = value;
        node->parent = parent;

        if (node->value > parent->value)
            parent->right = node;
        else
            parent->left = node;
    }
}

/* It places node y in the position of node x, and node x 
    will no longer be in its previous location. */
void BinaryTree::transplant(Node* x, Node* y) {
    if (!x->parent) {
        BinaryTree::root = y;
    } else {
        if (x->parent->left == x)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->parent = x->parent;
}

// Print values in order
void BinaryTree::print(Node* curr_root=nullptr) {
    if (!curr_root)
        curr_root = BinaryTree::root;
    print(curr_root->left);
    cout<<curr_root->value<<" "<<endl;
    print(curr_root->right);
}

Node* BinaryTree::get_min(Node* curr_root=nullptr) {
    if (!curr_root)
        curr_root = BinaryTree::root;
    if (!curr_root || !curr_root->left)
        return curr_root;
    else
        return get_min(curr_root->left);
}

Node* BinaryTree::get_max(Node* curr_root=nullptr) {
    if (!curr_root)
        curr_root = BinaryTree::root;
    if (!curr_root || !curr_root->right)
        return curr_root;
    else
        return get_max(curr_root->right);
}

void BinaryTree::remove(double value) {
    Node* node = search(value);

    if (node) {
        if (node->left && !node->right)
            transplant(node, node->left);
        else if (!node->left && node->right)
            transplant(node, node->right);
        else if (node->left && node->right) {
            Node* node_succ = get_min(node->right);

            if (node->right != node_succ) {
                transplant(node_succ, node_succ->right);
                node_succ->right = node->right;
            }
            transplant(node, node_succ);

            node_succ->left = node->left;
        } else {
            if (!node->parent)
                BinaryTree::root = nullptr;
            else {
                if (node->parent->left == node)
                    node->parent->left = nullptr;
                else
                    node->parent->right = nullptr;
            }
        }
        delete node;
    }
}
