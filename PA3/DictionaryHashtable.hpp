/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *
 *  Assignment: PA3
 *  File: DictionaryHashtable.hpp
 *  Name: Connie Su
 *  Date: 02/07/16
 *
 *  Creates dictionary using hash tables
 */

#ifndef DICTIONARY_HASHTABLE_HPP
#define DICTIONARY_HASHTABLE_HPP

#include <string>
#include<unordered_set>
#include <utility>

using namespace std;

/**
 *  The class for a dictionary ADT, implemented as a Hashtable
 * When you implement this class, you MUST use a Hashtable
 * in its implementation.  The C++ unordered_set implements 
 * a Hashtable, so we strongly suggest you use that to store 
 * the dictionary.
 */
class DictionaryHashtable
{
public:

  /* Create a new Dictionary that uses a Hashset back end */
  DictionaryHashtable();

  /* Insert a word into the dictionary. */
  bool insert(std::string word);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Destructor */
  ~DictionaryHashtable();

private:
  // Add your own data members and methods here
  unordered_set<string> ht;
};

#endif // DICTIONARY_HASHTABLE_HPP
