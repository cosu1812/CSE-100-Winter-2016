/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 *
 *  Assignment: PA3
 *  File: DictionaryTrie.hpp
 *  Name: Connie Su
 *  Date: 02/08/16
 *
 *  Creates dictionary using multiway trie
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP
#include <vector>
#include <string>
#define ALPHABET_SIZE 27
#include <utility>

/**
 * This class create nodes and functions use for constructing DictionaryTrie 
 * and finding words
 */ 
class TrieNode{
   public:
      /**
       * constructs TrieNode
       */ 
      TrieNode(bool isWord, unsigned int freq, std::string text);
      
      /**
       * get child based on index of TrieNode
       */ 
      TrieNode* getChild(unsigned int index);

      /**
       * set child of node at specific index
       */ 
      void setChild(TrieNode* newChild, unsigned index);
      
      /**
       * returns if node have word
       */ 
      bool getIsWord();

      /**
       * set node if it have word or not
       */ 
      void setIsWord(bool change);

      /**
       * get word from TrieNode
       */ 
      std::string getText();
     
      /**
       * set word in TrieNode
       */
      void setText(std::string newWord);

      /**
       * get word frequency of node
       */ 
      unsigned int getFreq();

      /**
       * set word frequency of node
       */ 
      void setFreq(unsigned int newFreq);

   private:
      // if node have a word or not
      bool isWord;

      // word frequency
      unsigned int freq;

      // word
      std::string text;
 
      // TrieNode's children
      std::vector<TrieNode*> child = std::vector<TrieNode*>(ALPHABET_SIZE, 
                                                            (TrieNode*) 0);
};

/**
 * This class is used to sort pairs in priority queue
 */ 
class Compare{
public:
   /**
    * use to sort pair of TrieNode and frequency by max frequency
    */ 
   bool operator()(std::pair<TrieNode*, unsigned int> t1, std::pair<TrieNode*, 
                   unsigned int> t2);
   
   /**
    * use to sort pair of string and frequency by max frequency
    */ 
   bool operator()(std::pair<std::string, unsigned int> s1, std::pair<
                   std::string, unsigned int> s2);
};

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);

  /* Destructor */
  ~DictionaryTrie();


private:
  // Add your own data members and methods here
  TrieNode* root;

  void deleteAll(TrieNode* node);
    
};

#endif // DICTIONARY_TRIE_HPP
