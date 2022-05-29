#include<iostream>
#include<vector>

#ifndef _BINARY_TREE_VECTOR_
#define _BINARY_TREE_VECTOR_

#include "lib_string.h"

class Node {
private:
public:
  abj::String key;
  Node *left, *right;
  
};

namespace abj{
  class BinarySearchTree{
  private:
    Node *treeRoot = NULL;
    int treeNodeCount;
    const char* DEBUG_FILEAME="./Debug-Log-Files/binarySearchTree.txt";

    Node *insert(Node *node, const abj::String& key);
    Node *minValueNode(Node *node);
    Node *newNode(const abj::String& item);
    Node *deleteNode(Node *root, const abj::String& key);
    void inorder(Node *root);
    bool inorder_find(Node *root, const abj::String& key);
    void inorder_free(Node *root);
    bool findFlag = false;
  public:
    BinarySearchTree();
    ~BinarySearchTree();

    void print();
    void print(abj::String& filename);

    void insert(const abj::String& key);
    void deleteNode(const abj::String& key);
    bool find(const abj::String& data);

   [[nodiscard]] int size();

    static void test_function();
  };
}


#endif
