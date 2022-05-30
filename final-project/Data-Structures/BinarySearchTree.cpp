#include "BinarySearchTree.h"

abj::BinarySearchTree::BinarySearchTree(){
  this->treeNodeCount = 0;
}

abj::BinarySearchTree::~BinarySearchTree() {
  this->inorder_free(this->treeRoot);
}

void abj::BinarySearchTree::inorder_free(Node *root){
   if (root != NULL) {
     inorder_free(root->left);
     inorder_free(root->right);
     root->key.~String();
     free(root);
  }
}

Node* abj::BinarySearchTree::newNode(const abj::String& item) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key.initialize(item);
  temp->left = temp->right = NULL;
  return temp;
}

void abj::BinarySearchTree::inorder(Node *root) {
  if (root != NULL) {
    inorder(root->left);

    std::cout << root->key << " -> ";

    inorder(root->right);
  }
}

void abj::BinarySearchTree::print(){
  this->inorder(this->treeRoot);
}


bool abj::BinarySearchTree::inorder_find(Node *root, const abj::String& key){
  if (root != NULL) {
    if(root->key==key){
      this->findFlag = true;
      return true;
    }
    this->inorder_find(root->left, key);
    this->inorder_find(root->right, key);
  }
  return false;
}

bool abj::BinarySearchTree::find(const abj::String& data){
  this->inorder_find(this->treeRoot,data);
  return this->findFlag;
}

Node* abj::BinarySearchTree::insert(Node *node, const abj::String& key) {
  if (node == NULL) return this->newNode(key);

  if (key < node->key)
    node->left = this->insert(node->left, key);
  else
    node->right = this->insert(node->right, key);

  return node;
}

void abj::BinarySearchTree::insert(const abj::String& key) {
  this->treeNodeCount++;
  this->treeRoot = this->insert(this->treeRoot, key);
}


int abj::BinarySearchTree::size(){
  return this->treeNodeCount;
}

void abj::BinarySearchTree::test_function(){
  abj::BinarySearchTree bst;
  bst.insert(*new abj::String("Abhijit"));
  bst.insert(*new abj::String("Paul"));
  bst.insert(*new abj::String("String"));
  bst.insert(*new abj::String("Stupor"));
  bst.insert(*new abj::String("Unscruplous"));
  bst.insert(*new abj::String("Courting death!"));
  bst.insert(*new abj::String("Firee"));
  bst.insert(*new abj::String("Tadaaaaa"));

  std::cout << "Inorder traversal: ";
  bst.print();

  std::cout << "Inorder traversal: ";
  bst.print();
  
  std::cout << "Finding \"Courting death!\": ";
  std::cout<<bst.find("Courting death!");
  std::cout<<std::endl;
}
