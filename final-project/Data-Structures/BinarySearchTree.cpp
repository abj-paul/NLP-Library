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

// Create a node
Node* abj::BinarySearchTree::newNode(const abj::String& item) {
  Node *temp = (Node *)malloc(sizeof(Node));
  temp->key.initialize(item);
  temp->left = temp->right = NULL;
  return temp;
}

// Inorder Traversal
void abj::BinarySearchTree::inorder(Node *root) {
  if (root != NULL) {
    inorder(root->left);

    // Traverse root
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

// Insert a node
Node* abj::BinarySearchTree::insert(Node *node, const abj::String& key) {
  // Return a new node if the tree is empty
  if (node == NULL) return this->newNode(key);

  // Traverse to the right place and insert the node
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


// Find the inorder successor
Node* abj::BinarySearchTree::minValueNode(Node *node) {
  Node *current = node;

  // Find the leftmost leaf
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

void abj::BinarySearchTree::deleteNode(const abj::String& key){
  this->treeRoot = this->deleteNode(this->treeRoot, key);
}

// Deleting a node
Node* abj::BinarySearchTree::deleteNode(Node *root, const abj::String& key) {
  // Return if the tree is empty
  if (root == NULL) return root;
  // Find the node to be deleted
  if (key < root->key)
    root->left = deleteNode(root->left, key);
  else if (key > root->key)
    root->right = deleteNode(root->right, key);
  else {
    // If the node is with only one child or no child
    if (root->left == NULL) {
      Node *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      free(root);
      return temp;
    }

    // If the node has two children
    Node *temp = minValueNode(root->right);

    // Place the inorder successor in position of the node to be deleted
    root->key = temp->key;

    // Delete the inorder successor
    root->right = deleteNode(root->right, temp->key);
  }
  return root;
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

  std::cout << "\nAfter deleting 10\n";
  bst.deleteNode(*new abj::String("Unscruplous"));
  std::cout << "Inorder traversal: ";
  bst.print();
  
  std::cout << "Finding \"Courting death!\": ";
  std::cout<<bst.find("Courting death!");
  std::cout<<std::endl;
}
