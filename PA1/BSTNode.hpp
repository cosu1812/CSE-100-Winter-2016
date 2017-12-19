/**
 * Assignment: PA1
 * File: BSTNode.hpp
 * Name: Connie Su
 * Date: 01/08/16
 *
 * Create nodes for binary search tree
 */
#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>

template<typename Data>
class BSTNode {
 
public:

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
  BSTNode(const Data & d) : data(d) {
    left = right = parent = 0;
  }

  BSTNode<Data>* left;
  BSTNode<Data>* right;
  BSTNode<Data>* parent;
  Data const data;   // the const Data in this node.

  /** Return the successor of this BSTNode in a BST, or 0 if none.
   ** PRECONDITION: this BSTNode is a node in a BST.
   ** POSTCONDITION:  the BST is unchanged.
   ** RETURNS: the BSTNode that is the successor of this BSTNode,
   ** or 0 if there is none.
   */ // TODO
  BSTNode<Data>* successor() {
     // spot for current node
     // next for navigating node to node
     BSTNode<Data>* spot;
     BSTNode<Data>* next;
      
     // if tree have right subtree, go right then left to get successor
     if (this->right){
        next = this->right;
        while (next->left) next = next->left;
	return next;
     }	
    
     // if tree have no right subtree, check if node's or higher parent is 
     // successor
     else {
        next = this->parent;
	spot = this;

        // moves up the tree to find parent that is a sucessor
	while (spot && next-right && next->right == spot){
	   spot = next;
	   next = next->parent;
	}
	return next;
     }
     
     // can't find successor
     return 0;
  }
}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}

#endif // BSTNODE_HPP
