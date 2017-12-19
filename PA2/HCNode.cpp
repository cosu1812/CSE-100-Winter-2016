/**
 * Assignment: PA2
 * File: HCNode.cpp
 * Name: Connie Su
 * Date: 01/18/16
 *
 * implements less-than comparision for priority queue
 */ 
#include "HCNode.hpp"

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** A class, instances of which are nodes in an HCTree.
 */
  /** Less-than comparison, so HCNodes will work in std::priority_queue
   *  We want small counts to have high priority.
   *  And we want to break ties deterministically.
   */
  bool HCNode::operator<(const HCNode& other){
     if (this->count != other.count) return this->count > other.count;

     return this->symbol > other.symbol;
  }

