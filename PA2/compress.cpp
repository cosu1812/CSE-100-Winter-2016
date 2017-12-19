/**
 * Assignment: PA2
 * File: compress.cpp
 * Name: Connie Su
 * Date: 01/20/16
 *
 * Use to compress a file by using Huffman Tree
 */ 
#include "HCTree.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>

#define ASCII_SIZE 256
#define SECOND_FILE 2
using namespace std;
  
  /**
   * writes frequency of each ASCII value to encoded file
   * Parameters: 
   *    const vector<int>& freqs: vector with frequency counts of each ASCII 
   *       value
   *    ofstream& out: stream to write frequency counts to file
   * Returns: void
   */ 
   void checkpointHeader(const vector<int>& freqs, ofstream& out){
      for (int index = 0; index != freqs.size(); index++){ 
         out << freqs[index];
	 out.put('\n');
      }
   }

   /**
    * Creates encoded file from another file
    * Must take in two files as arguments
    * One file is the original file
    * Other file will be a file with the encoded original file.
    */ 
   int main(int argc, char* argv[]){
      // check if have right number of arguments to proceed
      if (argc != 3) {
         cout << "Invalid number of arguments.\n";
	 return -1;
      } 

      // creates stream to read original and write onto a new file
      ifstream in;
      ofstream out;

      // open files in binary mode
      in.open(argv[1], ios::binary);
      out.open(argv[SECOND_FILE], ios::binary);
      
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
	in.seekg(0, ios_base::beg); 

      // to hold frequency count for each ASCII value
      vector<int> freqs(ASCII_SIZE, 0);
      
      //use to get char from file
      unsigned char nextChar;
      
      // total number of characters in file
      int fileCount = 0;

      // get frequency counts from file
      while (1){
         nextChar = in.get();
	 if (in.eof()) break;
         freqs[(int) nextChar] += 1;
	 fileCount += 1;
      }
      
      // reopens file to prevent seg fault
      in.close();
      in.open(argv[1]);
 
      // build tree
      HCTree tree;
      tree.build(freqs);
      
      // creates BitOutputstream to write bits
      BitOutputStream bout(out); 
      
      // prints out frequency count
      checkpointHeader(freqs, out);
      
      // encode original file and put code into new file
      while (1){
         nextChar = in.get();
	 if (in.eof()) break;
         tree.encode(nextChar, bout);
      }

      // flush buffer if there are leftover bits
      bout.flush();
      
      // close files
      in.close();
      out.close();
      return 0;
   }
