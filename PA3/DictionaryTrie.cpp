/**
 * Assignment: PA3
 * File: DictionaryTrie.cpp
 * Name: Connie Su
 * Date: 02/08/16
 *
 * Creates dictionary using multiway trie
 */ 
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <stack>
#define ALPHABET_SIZE 27
#define CHAR_NUM 97
#define SPACE 26

using namespace std;

/**
 * Construct TrieNode
 */
TrieNode::TrieNode(bool isWord, unsigned int freq, string text):isWord(isWord), 
                                                                freq(freq), 
								text(text){}

/**
 * Gets child based on index of TrieNode
 */ 
TrieNode* TrieNode::getChild(unsigned int index){
   return child[index];
}

/**
 * Gets word from TrieNode
 */ 
string TrieNode::getText(){
   return text;
}

/**
 * set word in TrieNode
 */
void TrieNode::setText(string newWord){
   text = newWord;
}

/**
 * set child of Node
 */ 
void TrieNode::setChild(TrieNode* newChild, unsigned int index){
   child[index] = newChild;
}

/**
 * returns if node have word
 */ 
bool TrieNode::getIsWord(){
   return isWord;
}

/**
 * set node if it have word or not
 */ 
void TrieNode::setIsWord(bool change){
   isWord = change;
}

/**
 * get word frequency of node
 */ 
unsigned int TrieNode::getFreq(){
   return freq;
}

/**
 * set word frequency of node
 */ 
void TrieNode::setFreq(unsigned int newFreq){
   freq = newFreq;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie():root(0){}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */

bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  // check if word is not empty
  if (!word.empty()){
     // creates root if none was created
     if (!root) root = new TrieNode(false, 0, "");
     
     // set current node at root
     TrieNode* curr = root;

     // go through trie to traverse and insert word
     for (unsigned int index = 0; index < word.size(); index++){
        // get index to put in TrieNode's children
	int childChar = word[index] - CHAR_NUM;
	if (word[index] == ' ') childChar = SPACE;

	// get child
	TrieNode* kid = curr->getChild(childChar);
	
	// check if kid is null
	if (kid != nullptr){	   
	   // go down the trie
	   curr = kid;
	   continue;
	}
	
	// create node that have a char from the word 
	else /*if (index != (word.size() - 1))*/ kid = new TrieNode(false, 0,
	                                                        "");	
	 // insert kid as curr's children
	 curr->setChild(kid, childChar);

	 // traverse down the trie
	 curr = kid;   
     }
     if (curr->getIsWord()){
        if (curr->getFreq() < freq) curr->setFreq(freq);
	return false;
     }	
     
     curr->setIsWord(true);
     curr->setText(word);
     curr->setFreq(freq);
     
     // inserted successfully
     return true;
  }

  // inserted unsuccessfully
  return false;
}

/* Return true if word is in the dictionary, and false otherwise */

bool DictionaryTrie::find(std::string word) const
{
  // check if word is empty
  if (!word.empty()){
     // set current node at root
     TrieNode* curr = root;

     // go through trie to find word
     for (unsigned int index = 0; index < word.size(); index++){
        int childChar = word[index] - CHAR_NUM;
	if (childChar < 0) childChar = SPACE;
	TrieNode* kid = curr->getChild(childChar);
	// if kid doesn't have char from word find failed
	if (kid == nullptr) return false;
        curr = kid;   
     }
     // if current node have word find is succesful
     if (curr->getIsWord()) return true;
  }
  // find failed
  return false; 
}

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  // hold max frequent words
  std::vector<std::string> words;

  // use to sort max frequent words 
  priority_queue<pair<string, unsigned int>, vector<pair<string, unsigned int>>,
                 Compare> list;
  
  // set current node as root
  TrieNode* curr = root;
  
  // go through trie with given prefix
  for (unsigned int index = 0; index < prefix.size(); index++){
     int childChar = prefix[index] - CHAR_NUM;
     if (childChar < 0) childChar = SPACE;
        TrieNode* kid = curr->getChild(childChar);
	if (kid == nullptr) return words;
        curr = kid;
  }
  
  // use to traverse through trie
  queue<TrieNode*> getNodes;
  getNodes.push(curr);
 
  // traverse through trie to find max frequent words
  while (!getNodes.empty()){
     // get top element
     curr = getNodes.front();
     getNodes.pop();
     
     // if node have word put into list to be sorted
     if (curr->getIsWord()){
        pair<string, unsigned int> found = {curr->getText(), curr->getFreq()};
	list.push(found);
     }
     
     // pushes in TrieNode's children
     for (unsigned int index = 0; index < ALPHABET_SIZE; index++){
        if (curr->getChild(index)){
	   TrieNode* child = curr->getChild(index);
           getNodes.push(child);
        }
     }  
  } 


  // go through list to put the found words in words
  for (unsigned int index = 0; index < num_completions; index++){
     pair<string, unsigned int> max = list.top();
     string maxWord = max.first;
     words.push_back(maxWord);
     list.pop();
  }

  // return max frequent words
  return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){ 
   deleteAll(root);
}

/**
 * Use to delete trie
 */ 
void DictionaryTrie::deleteAll(TrieNode* node){
   // return if node is null
   if (node == nullptr) return;

   // go through children's subtree
   for (int index = 0; index < ALPHABET_SIZE; index++){
      if (node->getChild(index)) deleteAll(node->getChild(index));
   }

   // delete current node
   delete node;
   node = nullptr;
}

 /**
  * use to sort pair of TrieNode and frequency by max frequency
  */ 
bool Compare::operator()(pair<TrieNode*, unsigned int> t1, 
                         pair<TrieNode*, unsigned int> t2){
   if (t1.second == t2.second) return t1.first->getText() < t2.first->getText();
   return t1.second < t2.second;
}

/**
 * use to sort pair of string and frequency by max frequency
 */ 
bool Compare::operator()(pair<string, unsigned int> s1, 
                         pair<string, unsigned int> s2){
   if (s1.second == s2.second) return s1.first < s2.first;
   return s1.second < s2.second;
}
