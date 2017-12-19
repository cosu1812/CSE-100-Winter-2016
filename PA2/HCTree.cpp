/**
 * Assignment: PA2
 * File: HCTree.cpp
 * Name: Connie Su
 * Date: 01/18/16
 *
 * Implements method to build tree, encode file, and decode file
 */ 
#include "HCTree.hpp"

#include <queue>
#include <vector>
#include <fstream>
#include <functional>
#include <stack>
#include <algorithm>

#define BYTE 8
#define ASCII_SIZE 256
using namespace std;

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
    
    /**
     * Use to delete HCTree and to prevent memory leaks
     */ 
    HCTree::~HCTree(){
        // delete tree
        deleteAll(root);

	// clear out HCNodes in vector
	leaves.clear();
    }

    /**
     * Use to delete Huffman Tree
     */ 
    void HCTree::deleteAll(HCNode* n){
       // returns if n is null
       if (n == nullptr) return;
       
       // recursively delete left sub tree
       deleteAll(n->c0);

       // recursively delete right subtree
       deleteAll(n->c1);
       
       // delete current node
       delete n;
       n = nullptr;
    }

    /** Use the Huffman algorithm to build a Huffman coding trie.
     *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
     *  the frequency of occurrence of byte i in the message.
     *  POSTCONDITION:  root points to the root of the trie,
     *  and leaves[i] points to the leaf node containing byte i.
     */
    void HCTree::build(const vector<int>& freqs){
       // if file is empty return
       if (freqs.size() == 0) return;
       
       // check if file only have one symbol
       int oneSymb = ASCII_SIZE;
       int found = 0;
	  for (int index = 0; index < freqs.size(); index++){
	     if (freqs[index] == 0) oneSymb--;
	     found = index;
	  }
       
       // if file only use one symbol, create tree with one node and exit 
       if (oneSymb == 1){
          root = new HCNode(freqs[found], (byte) found);
          leaves.push_back(root);
          return;
       }

       // create priority node to sort HCNode
       std::priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;
       
       // create HCNode for nonzero frequency count
       HCNode* leaf;
       for (int index = 0; index < freqs.size(); index++){
          if (freqs[index] == 0) continue; 
	  leaf = new HCNode(freqs[index], (char) index);
	  pq.push(leaf);
       }
     
       // use to get two least significant nodes from priority queue
       HCNode* next;
       HCNode* next2;

       // use to store root's symbol
       byte rootSymb = 0;

       // creates tree until only one node in priority queue
       while (pq.size() > 1){ 
          // get two least significant nodes
	  next = pq.top();
	  pq.pop();
	  next2 = pq.top();
	  pq.pop();

	  // create sum node and create a tree with the other two nodes
          root = new HCNode((next->count + next2->count), next->symbol, 
	                          next, next2);
          next->p = root;
	  next2->p = root;

	  // push sum node to be compare again
	  pq.push(root);
          

	   // put nodes in leaves if not already put into it
	  if (leaves[(int) next->symbol] == 0 && rootSymb!= next->symbol){
	     leaves[(unsigned int) next->symbol] = next;
	  }    
	  if (leaves[(int) next2->symbol] == 0 && rootSymb != next2->symbol){
	     leaves[(unsigned int) next2->symbol] = next2;
          }
    
          // get root->symbol to compare with leaves[i]
          rootSymb = root->symbol; 
       }
    }
    
    /** Write to the given BitOutputStream
     *  the sequence of bits coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
     void HCTree::encode(byte symbol, BitOutputStream& out) const{
	// get ASCII value of character
	int ascii = (int) symbol;
	
	// node that have the symbol
	HCNode* symbolLeaf = leaves[ascii];
        
	// to store in code for symbol
	stack<int> encoded;
	
	// starts from bottom
        HCNode* parent = symbolLeaf->p;
        
	// goes through tree bottom to top until it reaches root
	while (parent){
          if (parent->c0 == symbolLeaf) encoded.push(0);
	  else if (parent->c1 == symbolLeaf) encoded.push(1);
	  symbolLeaf = parent;
	  parent = parent->p;
        }
       
        // stacks is use to get origina code easily, write code to file
        while(!encoded.empty()){
	  out.writeBit(encoded.top());
	  encoded.pop();
       }
     }

    /** Write to the given ofstream
     *  the sequence of bits (as ASCII) coding the given symbol.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
     *  BE USED IN THE FINAL SUBMISSION.
     */
    void HCTree::encode(byte symbol, ofstream& out) const{
       // number representation of the symbol
       int ascii = (int) symbol;

       // node that have the symbol
       HCNode* symbolLeaf = leaves[ascii];
       
       // to store in code for symbol
       stack<char> encoded;

       // starts from bottom to top
       HCNode* parent = symbolLeaf->p;
       
       // goes through tree bottom to top until it reaches root 
       while (parent){
          if (parent->c0 == symbolLeaf) encoded.push('0');
	  else if (parent->c1 == symbolLeaf) encoded.push('1');
	  symbolLeaf = parent;
	  parent = parent->p;
       }
       
       // since stack's order is last in, first out, we have the original code
       while(!encoded.empty()){
	  out.put(encoded.top());
	  encoded.pop();
       }
    }

    /** Return symbol coded in the next sequence of bits from the stream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     */
    int HCTree::decode(BitInputStream& in) const{
       // get root
       HCNode* parent = root;
       
       // use to get byte from file
       int codeChar;

       // goes through tree top to bottom to get to symbol to write to file
       while (parent->c0 && parent->c1){
          int codeChar = in.readBit();
	  if (codeChar == 0) parent = parent->c0;
	  else if (codeChar == 1) parent = parent->c1;
	  else return -1;
       }

       // returns symbol
       return parent->symbol;
    }

    /** Return the symbol coded in the next sequence of bits (represented as 
     *  ASCII text) from the ifstream.
     *  PRECONDITION: build() has been called, to create the coding
     *  tree, and initialize root pointer and leaves vector.
     *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
     *  IN THE FINAL SUBMISSION.
     */
    int HCTree::decode(ifstream& in) const {
       // get root
       HCNode* parent = this->root;
       
       // use to get char 0 or 1 from file
       byte codeChar;
  
       // goes thorugh tree top to bottom to get to symbol and write to file
       while (parent->c0 && parent->c1){
          codeChar = in.get();

	  if (codeChar == '0') parent = parent->c0;
	  else if (codeChar == '1') parent = parent->c1;
	  else return -1;

       }

       //returns symbol
       return parent->symbol;
    }   
