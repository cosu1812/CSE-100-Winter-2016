/**
 * Assignment: PA3
 * File: benchdict.cpp
 * Name: Connie Su
 * Date: 02/16/16
 *
 * Find average time of finding 10 words in DictionaryBST, DictionaryHashtable, 
 * and DictionaryTrie
 */ 
#include "util.hpp"
#include "DictionaryBST.hpp"
#include "DictionaryHashtable.hpp"
#include "DictionaryTrie.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#define ARG_NUM 5
#define DICT 4
#define ITER 3
#define STEP 2
#define RETRY 10

using namespace std;

int main(int argc, char* argv[]){
   // check if have valid number of arguments
   if (argc != ARG_NUM){
      cout << "Invalid number of arguments. \n";
      return -1;
   } 

   // if arguments are less than or equal to 0 exit
   if (argv[1] <= 0 || argv[STEP] <= 0 || argv[ITER] <= 0) return -1;

   // creates stream to read dictionary
   ifstream in;

   // open files in binary mode
   in.open(argv[DICT], ios::binary);
      
   //Check if input file was actually opened
   if(!in.is_open()) 
   {
      cout<< "No file was opened.\n";
      return -1;
   } 

   //Check for empty file
   in.seekg(0, ios_base::end); 
   unsigned int len = in.tellg();
	
   if(len==0) 
   {
      cout << "The file is empty. \n";
      return -1;
   }

   //Resets the stream to beginning of file
   in.close();
   in.open(argv[DICT], ios::binary);

   // mininum number of words
   int minSize = atoi(argv[1]);

   // increment number of words by stepSize
   int stepSize = atoi(argv[STEP]);

   // increment stepSize 
   unsigned int iterNum = atoi(argv[ITER]);

   // create dictionary structure
   DictionaryBST* bst = new DictionaryBST();
   DictionaryHashtable* ht = new DictionaryHashtable();
   DictionaryTrie* trie = new DictionaryTrie();

   // words not in dictionary
   vector<string> notInDict = {"a babe in the plane", "not to say things", 
                               "barely to do", "can can can", "eat fiber",
			       "lets say goodbye", "delphic oracle", 
			       "google android", "play doh", 
			       "on top of their world"};
   
   // number of trials for finding 10 words
   int retry = 0;

   // timer to time find method
   Timer timer;

   // use to load dictionary
   Utils util;

   // average for finding 10 words
   long long average = 0;

   // time DictionaryBST's find for 10 words 
   cout << "DictionaryBST" << "\n";
   for (unsigned int index = 0; index < iterNum; index++){
      util.load_dict(*bst, in, minSize + (index * stepSize));
      
      cout << minSize + (index * stepSize) << "\t";
      
      // get sum of trial times 
      while (retry < RETRY){
         timer.begin_timer();
	 for (unsigned int mark = 0; mark < notInDict.size(); mark++){
            bst->find(notInDict[mark]);
	 }

	 // add all times
	 long long total = timer.end_timer();
	 average += total;
         retry++;  
      }

      // get average time to find 10 words of 10 trials
      average /= RETRY;
      cout << average << "\n";
      
      //reset for next word size of dictionary file
      average = 0;
      retry = 0;
      
      // close and reopen dictionary file
      in.close();
      in.open(argv[DICT], ios::binary);
   }   

   // free bst
   delete bst;
   bst = NULL;
   
   // close and reopen file to be at beginning of file
   in.close();
   in.open(argv[DICT], ios::binary);

   // time DictionaryHashtable's find for 10 words
   cout << "DictionaryHashtable" << "\n";
   for (unsigned int index = 0; index < iterNum; index++){
      // load dictionary
      util.load_dict(*ht, in, minSize + (index * stepSize));
      
      // print out supposed loaded dictioanry size
      cout << minSize + (index * stepSize) << "\t";
      
      // time find method for 10 words and repeat for 10 trials
      while (retry < RETRY){
         timer.begin_timer();
	 for (unsigned int mark = 0; mark < notInDict.size(); mark++){
            ht->find(notInDict[mark]);
	 }

	 // add all times
	 long long total = timer.end_timer();
	 average += total;
         retry++;  
      }
      
      // get average of finding 10 words in 10 trials
      average /= RETRY;
      cout << average << "\n";
      
      // reset for next iteration
      average = 0;
      retry = 0;
      
      // close and reopen dictionary file to be at beginning of file
      in.close();
      in.open(argv[DICT], ios::binary);
   }

   // free ht
   delete ht;
   ht = NULL;
   
   // close and reopen dictionary file to be at beginning of file
   in.close();
   in.open(argv[DICT], ios::binary);
  
   // time DictionaryTrie's find for 10 words
   cout << "DictionaryTrie" << "\n";
   for (unsigned int index = 0; index < iterNum; index++){
      // load dictionary
      util.load_dict(*trie, in, minSize + (index * stepSize));
      
      // print out supposed loaded dictionary size
      cout << minSize + (index * stepSize) << "\t";
      
      // time find method for 10 words and repeat for 10 trials
      while (retry < RETRY){
         timer.begin_timer();
	 for (unsigned int mark = 0; mark < notInDict.size(); mark++){
            trie->find(notInDict[mark]);
	 }   
	 // add all times
	 long long total = timer.end_timer();
	 average += total;
         retry++;  
      }

      // get average time to find 10 words in 10 trials
      average /= RETRY;
      cout << average << "\n";
      
      // reset for next word size of dictionary file
      average = 0;
      retry = 0;

      // close and reopen dictionary file to be at beginning of file
      in.close();
      in.open(argv[DICT], ios::binary);
   }

   // free trie
   delete trie;
   trie = NULL;

   // close file
   in.close();

   return 0;
}
