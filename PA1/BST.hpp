/**
 * Assignment: PA1
 * File:BST.hpp
 * Name: Connie Su
 * Date: 01/08/16
 *
 * Creates binary search tree and functions to search for nodes and print out
 * size, height, and nodes
 */
#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;
  
public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
      Initialize an empty BST.
   */
  BST() : root(0), isize(0), iheight(0) {  }


  /** Default destructor.
      Delete every node in this BST.
   */ // TODO
  virtual ~BST() {
     deleteAll(root);
     isize = 0;
     iheight = 0;
     root = 0;
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
   *  Return  true if the item was added to this BST
   *  as a result of this call to insert,
   *  false if an item equal to this one was already in this BST.
   *  Note: This function should use only the '<' or "==" operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  virtual bool insert(const Data& item) {
     // if there was no tree, create root      
     if (root == nullptr) root = new BSTNode<Data>(item);
     
     // if exist a tree, find placement of new node
     else {
         // use as temp root and to find place for item
	 BSTNode<Data>* curr;
         BSTNode<Data>* spot;
         curr = root;
         
	 // use to find new height of tree if there is
	 unsigned int newHeight = 0;

	// goes through tree to find placement of new node
        while(curr){
	   
	   // if node's data is less than item, find place in right subtree
	   if (curr->data < item){
	      spot = curr;
	      newHeight++;
	      curr = curr->right;
	   }
	   
	   // if item is already in tree, no need to add item and return false
	   else if (curr->data == item) return false;
	   
	   // if node's data is greater than item, find place in left subtree
	   else {
	      spot = curr;
	      newHeight++;
	      curr = curr->left;
	   }
	}
	
        // if spot's data is less than item, it's put on spot's right side
        if (spot->data < item){
	   spot->right = new BSTNode<Data>(item);
	   spot->right->parent = spot;
	}   
     
	// item is put on spot's left side	
	else {
	   spot->left = new BSTNode<Data>(item);
	   spot->left->parent = spot;
	}

	// check if item made the tree longer and update height
        if (iheight < newHeight) iheight = newHeight;
     }

     // increase node count
     isize++;
     
     // successfully insert item
     return true;  	
  }


  /** Find a Data item in the BST.
   *  Return an iterator pointing to the item, or pointing past
   *  the last node in the BST if not found.
   *  Note: This function should use only the '<' or "==" operator when comparing
   *  Data items. (should not use >, <=, >=)
   */ // TODO
  iterator find(const Data& item) const {
     // iterator point at minimum node
     // iterator point past the last node
     auto beg = this->begin();
     auto end = this->end();
  
     // finds item in tree
     while (!(beg == end)){
	if (*beg == item) return beg;
	beg++;
     }

     return beg;
  }

  
  /** Return the number of items currently in the BST.
   */ // TODO
  unsigned int size() const {
     return isize;
  }
  
  /** Return the height of the BST.
   */ // TODO
  unsigned int height() const {
     return iheight;
  }


  /** Return true if the BST is empty, else false.
   */ // TODO
  bool empty() const {
     if (root == 0) return true;
     return false;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
   */ // TODO
  iterator begin() const {
     return typename BST<Data>::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
   */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }

  /** Perform an inorder traversal of this BST.
   */
  void inorder() const {
    inorder(root);
  }


private:
   
  /** Recursive inorder traversal 'helper' function */

  /** Inorder traverse BST, print out the data of each node in ascending order.
      Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
    * Parameters: BSTNode<Data> *n
    * Returns: none
    */ // TODO
  void inorder(BSTNode<Data>* n) const {
    /* Pseudo Code:
      if current node is null: return;
      recursively traverse left sub-tree
      print current node data
      recursively traverse right sub-tree
    */
     if (n == nullptr)  return;
     inorder(n->left);
     cout << n->data << "\n";
     inorder(n->right);
  }

  /** Find the first element of the BST
   */ 
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if(root == 0) return 0;
    while(root->left != 0) root = root->left;
    return root;
  }

  /** do a postorder traversal, deleting nodes
   * Parameters: BSTNode<Data>* n
   * Returns: none
   */ // TODO
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
      if current node is null: return;
      recursively delete left sub-tree
      recursively delete right sub-tree
      delete current node
    */
      if (n == nullptr) return;
      deleteAll(n->left);
      deleteAll(n->right);
      delete n;
      n = nullptr;
  }

 };


#endif //BST_HPP
