/*******************************************************************************
 * Name        : rbtree.h
 * Author      : Daniel Detore, Anthony Santilli
 * Version     : 1.0
 * Date        : 23 November, 2024
 * Description : Implementation of red-black tree.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#ifndef RBTREE_H_
#define RBTREE_H_

#include "node.h"
#include "tree.h"
#include "treeprinter.h"
#include <iostream>
#include <cstdlib>
#include <exception>
#include <string>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

// Forward declaration
template <typename K, typename V>
class RedBlackTree;

/**
 * tree_exception class
 * Demonstrates how you can write your own custom exceptions in C++.
 */
class tree_exception: public std::exception {
public:
    tree_exception(const std::string &message) : message_{message} { }

    ~tree_exception() throw() { }

    virtual const char* what() const throw() {
        return message_.c_str();
    }

private:
    std::string message_;
};

template<typename K, typename V>
class RedBlackTree : public Tree<K> {
public:
    /**
     * Constructor to create an empty red-black tree.
     */
    explicit RedBlackTree() : root_{nullptr}, size_{0} { }

    /**
     * Constructor to create a red-black tree with the elements from the
     * vector.
     */
    explicit RedBlackTree(std::vector< std::pair<K, V> > &elements) :
                                            root_(nullptr), size_(0) {
        insert_elements(elements);
    }

    /**
     * Destructor.
     */
    ~RedBlackTree() {
        delete_tree(root_);
    }

    /**
     * Inserts elements from the vector into the red-black tree.
     * Duplicate elements are not inserted.
     */
    void insert_elements(std::vector< std::pair<K, V> > &elements) {
        for (size_t i = 0, len = elements.size(); i < len; ++i) {
            try {
                insert(elements[i].first, elements[i].second);
            } catch (const tree_exception &te) {
                std::cerr << "Warning: " << te.what() << std::endl;
            }
        }
    }

    /**
     * Inserts a key-value pair into the red black tree.
     *
     * MUST throw a tree_exception if attempting to insert a key that is
     * already present in the tree.
     */
    void insert(const K &key, const V &value) {
        Node<K, V> *x = root_, *y = nullptr;
        size_++;
        if(find(key) != nullptr){
            size_--;
            stringstream iss;
            iss << "Attempt to insert duplicate key '" << key << "'.";
            throw tree_exception(iss.str());
        }
        while (x != nullptr) {
            y = x;
            if (key < x->key()) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        Node<K,V> *z = new Node<K,V>(key, value);
        z->parent = y;
        if (y == nullptr) {
            root_ = z;
        } else if (z->key() < y->key()) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = nullptr;
        z->right = nullptr;
        z->color = RED;
        insert_fixup(z);
    }

    /**
     * Returns an ASCII representation of the red-black tree.
     */
    std::string to_ascii_drawing() {
        BinaryTreePrinter<K, V> printer(root_);
        return printer.to_string();
    }

    /**
     * Returns the height of the red-black tree.
     */
    int height() const {
        return height(root_);
    }

    /**
     * Returns the number of nodes in the red-black tree.
     */
    size_t size() const {
        return size_;
    }

    /**
     * Returns the leaf count of the red-black tree.
     */
    size_t leaf_count() const {
        return leaf_count(root_);
    }

    /**
     * Returns the internal node count of the red-black tree.
     */
    size_t internal_node_count() const {
        return internal_node_count(root_);
    }

    /**
     * Returns the diameter of the red-black tree rooted at node.
     * Diameter is defined as the length of the longest path between
     * two (non-null) leaves in the tree. The path does not necessarily have to
     * pass through the root.
     */
    size_t diameter() const {
        return diameter(root_);
    }

    /**
     * Returns the max width of the red-black tree, i.e. the largest number of
     * nodes on any level.
     */
    size_t max_width() const {
        size_t max_width = 0;
        for (int i = 0, h = height(root_) + 1; i < h; ++i) {
            size_t w = width(root_, i);
            if (w > max_width) {
                max_width = w;
            }
        }
        return max_width;
    }

    /**
     * Returns the successful search cost, i.e. the average number of nodes
     * visited to find a key that is present.
     */
    double successful_search_cost() const {
        return size_ == 0 ? 0 : 1 + (double)sum_levels() / size_;
    }

    /**
     * Returns the unsuccessful search cost, i.e. the average number of nodes
     * visited to find a key that is not present.
     */
    double unsuccessful_search_cost() const {
        return (double)sum_null_levels() / null_count();
    }

    /**
     * Searches for item. If found, returns the node
     * for it in the tree; otherwise, returns nullptr.
     */
     Node<K, V> *find(const K &key) {
        Node<K, V> *x = root_;
        while (x != nullptr) {
            const K& current_key = x->key();
            if (key == current_key) {
                break; // Found!
            } else if (key < current_key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        return x;
    }

    std::vector<K> inorder_traversal_helper(Node<K, V> *current) const {
        std::vector<K> result;
        if(current == nullptr) {
            return result;
        }
        for(auto const &element : inorder_traversal_helper(current->left)) {
            result.push_back(element);
        }
        result.push_back(current->key());
        for(auto const &element:  inorder_traversal_helper(current->right)) {
            result.push_back(element);
        }
        return result;
    }

    std::vector<K> inorder_traversal() const {
        return inorder_traversal_helper(root_);
    }

private:
    Node<K, V> *root_;
    size_t size_;

    /**
     * Deletes all nodes from the red-black tree.
     */
    void delete_tree(Node<K, V> *n) {
        
        if (n != nullptr) {
            delete_tree(n->left);
            delete_tree(n->right);
            delete n;
        }
    }

    /**
     * Fixup method described on p. 316 of CLRS.
     */
    void insert_fixup(Node<K, V> *z) {
        
        Node<K, V>* y;
        while (z->parent != nullptr && z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                y = z->parent->parent->right;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;           // case 1 ...
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {        // case 2 ...
                        z = z->parent;               
                        left_rotate(z);
                    }
                    z->parent->color = BLACK;           // case 3 ...
                    if(z->parent->parent !=nullptr)  {
                        z->parent->parent->color = RED;
                        right_rotate(z->parent->parent);
                    }
                }
            } else {
                y = z->parent->parent->left;
                if (y != nullptr && y->color == RED) {
                    z->parent->color = BLACK;           // case 1 reflected ...
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {         // case 2 reflected ...
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;           // case 3 reflected ...
                    if(z->parent->parent != nullptr){
                        z->parent->parent->color = RED;
                        left_rotate(z->parent->parent);
                    }
                }
            }
        }
        // Last line below
        root_->color = BLACK;
    }

    /**
     * Left-rotate method described on p. 313 of CLRS.
     */
    void left_rotate(Node<K, V> *x) {
        
        Node<K, V> *y = x->right;           //set y
        x->right = y->left;                 // turn y's left subtree into x's right subtree
        if (y->left != nullptr)
            y->left->parent = x;
        y->parent = x->parent;              // link x's parent to y
        if (x->parent == nullptr)
            root_ = y; 
        else if (x == x->parent->left)
            x->parent->left = y;
        else x->parent->right = y;
        y->left = x;                        // put x on y's left
        x->parent = y;
    }

    /**
     * Right-rotate method described on p. 313 of CLRS.
     */
    void right_rotate(Node<K, V> *x) {
        
        Node<K, V> *y = x->left;

        x->left = y->right;
        if (y->right != nullptr)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root_ = y; 
        else if (x == x->parent->right)
            x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    /**
     * Returns the height of the red-black tree starting at node.
     * A null node starts at height -1.
     */
    int height(Node<K, V> *node) const {
        
        if (node == nullptr) return -1;
        return max(height(node->left) + 1, height(node->right) + 1);
    }

    /**
     * Returns the count of leaves in the red-black tree starting at node.
     * For this method, a leaf is a non-null node that has no children.
     */
    size_t leaf_count(Node<K, V> *node) const {
        
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return (leaf_count(node->left) + leaf_count(node->right));
    }

    /**
     * Returns the count of internal nodes in the red-black tree starting at
     * node.
     * An internal node has at least one child.
     */
    size_t internal_node_count(Node<K, V> *node) const {
        
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) return 0;
        return (internal_node_count(node->left) + internal_node_count(node->right) + 1);
    }

    /**
     * Helper method to assist in the computation of tree diameter.
     */
    size_t diameter(Node<K, V> *node) const {
        
        if (node == nullptr) return 0;
        return max(height(node->left) + height(node->right) + 2, (int)max(diameter(node->left), diameter(node->right)));
    }

    /**
     * Returns the width of the red-black tree at the designated level.
     * Width is defined as the number of nodes residing at a level.
     */
    size_t width(Node<K, V> *node, size_t level) const {
        
        if (node == nullptr) return 0;
        if (level == 0) return 1;
        return width(node->left, level - 1) + width(node->right, level - 1);
    }

    size_t null_count() const {
        return null_count(root_);
    }

    /**
     * Returns the count of null pointers in the red-black tree starting at
     * node.
     */
    size_t null_count(Node<K, V> *node) const {
        if (node == nullptr) return 1;
        return null_count(node->left) + null_count(node->right);
    }

    size_t sum_levels() const {
        return sum_levels(root_, 0);
    }

    /**
     * Returns the sum of the levels of each non-null node in the red-black
     * tree starting at node.
     * For example, the tree
     *   5 <- level 0
     *  / \
     * 2   8 <- level 1
     *      \
     *       10 <- level 2
     * has sum 1*0 + 2*1 + 1*2 = 4.
     */
    size_t sum_levels(Node<K, V> *node, size_t level) const {
        
        if (node == nullptr) return 0;
        return level + sum_levels(node->left, level + 1) + sum_levels(node->right, level + 1);
    }

    size_t sum_null_levels() const {
        return sum_null_levels(root_, 0);
    }

    /**
     * Returns the sum of the levels of each null node in the red-black tree
     * starting at node.
     * For example, the tree
     *    5 <- level 0
     *   / \
     *  2   8 <- level 1
     * / \ / \
     * * * * 10 <- level 2
     *       / \
     *       * * <- level 3
     * has sum 3*2 + 2*3 = 12.
     */
    size_t sum_null_levels(Node<K, V> *node, size_t level) const {
        if (node == nullptr) return level;
        return sum_null_levels(node->left, level + 1) + sum_null_levels(node->right, level + 1);
    }
};

#endif /* RBTREE_H_ */
