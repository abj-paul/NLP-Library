#include<iostream>
#include<vector>

#ifndef _BINARY_TREE_SET_
#define _BINARY_TREE_SET_

#include "../Data-Structures/lib_string.h"

namespace abj{
  // NODE IMPLEMENTATION
  
template<typename T>
class TNode{
private:
  TNode<T>* createTNode(T data);
public:
  T data;
  TNode<T>* left, *right;
  int occurences;

  void inorder(TNode<T>* currentRoot);
  int containsTNode(TNode<T>* currentRoot, T data);
  // Returns new root node to account for cases the incoming element is inserted at root.
  TNode<T>* insert(TNode<T>* currentRoot, T data);
  int getOccurences(TNode<T>* currentRoot, T data);
};


  // SET implementation
  template<typename T>
  class Set{
  private:
    TNode<T>* treeRoot;
    int treeTNodeCount;

  public:
    Set();
    Set(const Set& set);
    // ~Set();

    [[nodiscard]] TNode<T>* getRoot();
    int size();
    // We can handle duplicate count here!!!
    void insert(const T& data);
    bool contains(const T& data);
    int getOccurences(const T& data);
    void print();
  };
  
}



















template<typename T>
void abj::TNode<T>::inorder(TNode<T>* currentRoot){
    if(currentRoot == NULL) return;

    inorder(currentRoot->left);
    std::cout<< currentRoot->data << " Occurences=" << currentRoot->occurences << " ,";
    inorder(currentRoot->right);
}


template<typename T>
int abj::TNode<T>::getOccurences(TNode<T>* currentRoot, T data){
  if(currentRoot==NULL) return 0;
  if(currentRoot->data==data) return this->occurences;
  return std::max(containsTNode(currentRoot->left, data) , containsTNode(currentRoot->right, data));
}
template<typename T>
int abj::TNode<T>::containsTNode(TNode<T>* currentRoot, T data){
    if(currentRoot==NULL) return 0;
    if(currentRoot->data==data) return 1;
    return containsTNode(currentRoot->left, data) | containsTNode(currentRoot->right, data);
}

template<typename T>
abj::TNode<T>* abj::TNode<T>::createTNode(T data){
    TNode<T>* temp = new TNode<T>;
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->occurences = 1; // It itself is an occurence.

    return temp;
}



template<typename T>
abj::TNode<T>* abj::TNode<T>::insert(TNode<T>* currentRoot, T data){
    if(currentRoot == NULL) return this->createTNode(data);

    if(currentRoot->data > data) {
      currentRoot->left = this->insert(currentRoot->left, data);
      return currentRoot;
    }
    else if(currentRoot->data==data){
      currentRoot->occurences++;
      return currentRoot; // Makes sure that no duplicate element stays in the tree!
    }
    else{ //(currentRoot->data<data)
      currentRoot->right = this->insert(currentRoot->right, data);
      return currentRoot;
    }
}


template<typename T>
abj::Set<T>::Set(){
  treeRoot = NULL;
  treeTNodeCount = 0;
}
template<typename T>
abj::Set<T>::Set(const Set& set){
  treeRoot = set.getRoot();
  treeTNodeCount = set.size();
}

template<typename T>
abj::TNode<T>* abj::Set<T>::getRoot(){
  return treeRoot;
}

template<typename T>
int abj::Set<T>::size(){
  return treeTNodeCount;
}

template<typename T>
void abj::Set<T>::insert(const T& data){
      // if(!treeRoot->containsTNode(treeRoot, data)){ // We can handle duplicate count here!!!
	treeRoot = treeRoot->insert(treeRoot, data);
	this->treeTNodeCount++;
      // }
}

template<typename T>
bool abj::Set<T>::contains(const T& data){
  if(this->treeRoot->containsTNode(treeRoot, data)) return true;
  return false;
}
template<typename T>
int abj::Set<T>::getOccurences(const T& data){
  return this->treeRoot->getOccurences(treeRoot, data);
}

template<typename T>
void abj::Set<T>::print(){
      // FILE* fptr = fopen(fileName, "w");
      // if(fptr==NULL){
      // 	printf("\"%s\" File not found! Exiting...\n",fileName);
      // 	exit(1);
      // }

      // fprintf(fptr, "Set Size = %d\n ", this->size());
      // fprintf(fptr, "{ ");
      std::cout<<"Set Size = "<<this->size()<<std::endl;
      std::cout<<"{ ";
      treeRoot->inorder(treeRoot);
      // fprintf(fptr, "} ");
      std::cout<<"} "<<std::endl;
}



// void set_test_function(){
//   abj::Set<int> set;
//   set.insert(2);
//   set.insert(2);
//   set.insert(2);
//   set.insert(3);
//   set.insert(3);
//   set.insert(3);
//   set.insert(1);
//   set.insert(10);
//   set.insert(-1);


//   set.print();

//   std::cout << "Does Set contain 10? " << set.contains(10) << std::endl;
//   std::cout << "Does Set contain 11? " << set.contains(11) << std::endl;
//   std::cout << "Occurences of 2 = " << set.getOccurences(2) << std::endl;
// }
#endif
