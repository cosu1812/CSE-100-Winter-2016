/**
 * Assignment: PA3
 * File: DictionaryHashtable.cpp
 * Name: Connie Su
 * Date: 02/07/16
 *
 * This class creates a dictionary using hash tables
 */ 
#include "util.hpp"
#include "DictionaryHashtable.hpp"
#include <string>
#include <unordered_set>
#include <utility>
using namespace std;

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
   // inserts word an check if it actually inserted 
   if (!word.empty()){
      auto ret = ht.insert(word);
      if (ret.second) return true;
   }
   return false;   
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
   // find word and check if actually found it
   if (!word.empty()){
      auto found = ht.find(word);
      if (found == ht.end()) return false;
      return true;
   }
   return false;

}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
   ht.clear();
}
