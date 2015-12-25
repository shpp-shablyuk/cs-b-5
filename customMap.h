#ifndef CUSTOMMAP_H
#define CUSTOMMAP_H

#include <iostream>
#include "gobjects.h"

using namespace std;

template <typename kT, typename vT>
class CustomMap {
public:
    struct BSTNode {
        kT key;
        vT value;
        BSTNode *right, *left;
        int height;
    };

    typedef BSTNode* Node;

    CustomMap() {
        root = NULL;
        count = 0;
    }

//    insert node with key, value in map
    void insert(const kT key, const vT value) {
        insertNode(root, key, value);
    }

//    insert node with key, value in map
    void put(const kT key, const vT value) {
        insertNode(root, key, value);
    }

//    find node by key
    Node find(const kT key) {
        return findNode(root, key);
    }

//    check is key exist
    bool containsKey(const kT key) {
        return (size() == 0 || findNode(root, key) == NULL) ? false : true;
    }

//    return number of nodes in map
    int size() const {
        return count;
    }

//    check is empty map
    bool empty() const {
        return (count == 0) ? true : false;
    }

//    return referense to node by key
    vT & operator[] (const kT key) {
        Node node = findNode(root, key);
        if (node != NULL) {
            return node->value;
        } else {
            throw "operator[]: key not find";
        }
    }

//    erase node by key
    void erase(const kT key) {
        removeNode(root, key);
    }

//    erase all nodes in map
    void clear() {
        while (count != 0 ) {
            erase(root->key);
        }
    }

    void infixPrint() {
        infixPrint(root);
    }

    void prefixPrint() {
        prefixPrint(root);
    }

    void postfixPrint() {
        postfixPrint(root);
    }

//  show map friendly
    void print() {
        gw.clear();
        windowPrint(root, gw.getWidth() / 2);
    }


private:
    GWindow gw;
    Node root;
    int count;


    int height(Node node) {
        return (node == NULL) ? 0 : node->height;
    }

    int balanceFactor(Node node) {
        return height(node->right) - height(node->left);
    }

    void fixHeight(Node node) {
        int hl = height(node->left);
        int hr = height(node->right);
        node->height = ((hl > hr) ? hl : hr) + 1;
    }

    void rotateRight(Node& node) {
        Node tNode = node;
        Node l = tNode->left;
        tNode->left = l->right;
        l->right = tNode;
        fixHeight(tNode);
        fixHeight(l);
        node = l;
    }

    void rotateLeft(Node& node) {
        Node tNode = node;
        Node r = tNode->right;
        tNode->right = r->left;
        r->left = tNode;
        fixHeight(tNode);
        fixHeight(r);
        node = r;
    }

    void balance(Node& node) {
        if (node == NULL) {
            return;
        }
        fixHeight(node);
        if (balanceFactor(node) == 2) {         //  rotate to left
            if (balanceFactor(node->right) < 0) {
                rotateRight(node->right);
            }
            rotateLeft(node);
        } else if (balanceFactor(node) == -2) { //  rotate to right
            if (balanceFactor(node->left) > 0) {
                rotateLeft(node->left);
            }
            rotateRight(node);
        }
    }

    void insertNode(Node& node, const kT key, const vT value){
        if (node == NULL) {
            //  add new node
            node = new BSTNode;
            node->key = key;
            node->value = value;
            node->left = node->right = NULL;
            node->height = 1;
            count++;
        } else {
            if (node->key != key) {
                if (key > node->key) {
                    insertNode(node->right, key, value);
                } else {
                    insertNode(node->left, key, value);
                }
            }
        }
        balance(node);
    }

    Node findNode(Node node, const kT key) {
        if (node == NULL) return NULL;
        if (node->key == key) {
            return node;
        }
        if (key < node->key) {
            return findNode(node->left, key);
        } else {
            return findNode(node->right, key);
        }
    }

    Node findMin(Node node) {
        if (node->left == NULL) {
            return node;
        }
        return findMin(node->left);
    }

    Node findMax(Node node) {
        if (node->right == NULL) {
            return node;
        }
        return findMax(node->right);
    }

    //  break links parent of min's with min
    Node removeMin(Node node) {
        if (node->left == NULL) {
            return node->right;
        }
        node->left = removeMin(node->left);
        balance(node);
        return node;
    }

    void removeNode(Node & node, const kT key) {
        if (node == NULL) {
            return ;
        }
        if (key < node->key) {
            removeNode(node->left, key);
        } else if (key > node->key) {
            removeNode(node->right, key);
        } else {    //  key == node->key
            Node l = node->left;
            Node r = node->right;
            delete node;
            if (r == NULL) {
                node = l;
            } else {
//                find node with minimum key in right subtree
                Node minRight = findMin(r);
                minRight->right = removeMin(r);
                minRight->left = l;
                node = minRight;
                balance(node);
            }
            count--;
        }
        balance(node);
    }

    void infixPrint(Node node) {
        if (node != NULL) {
            infixPrint(node->left);
            std::cout << "key [" << node->key << "] - value [" << node->value << "]" << endl;
            infixPrint(node->right);
        }
    }

    void prefixPrint(Node node) {
        if (node != NULL) {
            std::cout << "key [" << node->key << "] - value [" << node->value << "]" << endl;
            prefixPrint(node->left);
            prefixPrint(node->right);
        }
    }

    void postfixPrint(Node node) {
        if (node != NULL) {
            postfixPrint(node->left);
            postfixPrint(node->right);
            std::cout << "key [" << node->key << "] - value [" << node->value << "]" << endl;
        }
    }

    void windowPrint(Node node, double x, int c = 0) {
        if (node != NULL) {
            c++;
            GLabel* label = new GLabel(to_string(node->key));
            //  offset
            int k = 20;
            gw.add(label, x, c * k);
            windowPrint(node->left, x - k, c);
            windowPrint(node->right, x + k, c);
        }
    }
};

#endif // CUSTOMMAP_H
