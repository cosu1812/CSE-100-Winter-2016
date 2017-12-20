/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *
 * Assignment: PA3
 * File: DictionaryBST.hpp
 * Name: Connie Su
 * Date: 02/07/16
 * 
 * This class creates a dictionary using a binary search tree
 */

#ifndef DICTIONARY_BST_HPP
#define DICTIONARY_BST_HPP

#include <string>
#include <set>

using namespace std;
/**
 *  The class for a dictionary ADT, implemented as a BST
 * When you implement this class, you MUST use a balanced binary
 * search tree in its implementation.  The C++ set implements 
 * a balanced BST, so we strongly suggest you use that to store 
 * the dictionary.
 */
class DictionaryBST
{
public:

  /* Create a new Dictionary that uses a BST back end */
  DictionaryBST();

  /* Insert a word into the dictionary. */
  bool insert(std::string word);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Destructor */
  ~DictionaryBST();

private:
  // Add your own data members and methods here
  set<string> bst; 
};

#endif // DICTIONARY_BST_HPP