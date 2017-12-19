/**
 * Assginment: PA3
 * File: DictionaryBST.cpp
 * Name: Connie Su
 * Date: 02/07/16
 *
 * This class creates a dictionary using a binary search tree
 */ 
#include "util.hpp"
#include "DictionaryBST.hpp"
#include <string>
#include <set>

using namespace std;

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
   // creates iterator to see if word is inserted
   pair<set<string>::iterator, bool> ret; 
   
   // insert word
   if (!word.empty()){
      ret = bst.insert(word);
      return ret.second;
   }   
   return false;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
   // find word and check if it actually found it
   if (!word.empty()){
      auto it = bst.find(word);
      if (it == bst.end()) return false;
      return true;
   }   
   return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
   bst.clear();
}
