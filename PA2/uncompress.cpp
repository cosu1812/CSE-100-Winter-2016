/**
 * Assignment: PA2
 * File: uncompress.cpp
 * Name: Connie Su
 * Date: 01/20/16
 *
 * Use to decompress file to get original file using Huffman Tree
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
    * Creates decoded file from encoded file to get original file
    * Must take in two files as arguments
    * One file is the encoded file
    * Other file will be the file with decoded code
    */ 
   int main(int argc, char* argv[]){
      // check if have right number of arguments to proceed
      if (argc != 3) {
         cout << "Invalid number of arguments.\n";
	 return -1;
      }

      // creates stream to read encoded and write onto a new file
      ifstream in;
      ofstream out;

      // open file in binary mode
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
      
      // creates BitInputStream to read bits
      BitInputStream bin(in);

      // forfrequency count
      int num;

      // use to store frequnecy count as a string
      string count;

      // use to stop when finish reading frequency count
      int fullSize = ASCII_SIZE;

      // use to store frequency ocunt
      vector<int> freqs;
      
      // get counts and store into freqs
      while(fullSize > 0){
	 getline(in, count);
	 num = atoi(count.c_str());
	 freqs.push_back(num);
         fullSize -= 1;
      }      
     
      // build tree
      HCTree tree;
      tree.build(freqs);
            
      // check if file is suppose to have one character used
      int oneSymb = ASCII_SIZE;
      int charBit = 0;
      int fileCount = 0;
      for (int index; index < freqs.size(); index++){
         if (freqs[index] == 0){
	    oneSymb--;
	 }   
	 charBit = index;
	 fileCount += freqs[index];
      }

      // if one character is used, write character number of times and close
      if (oneSymb == 1){
         while (fileCount > 0){
	    out.put((char) charBit);
	 }
	 in.close();
	 out.close();
         return 0;
      }
      
      // decodes file and write it to another file
      while(fileCount > 0){
         int symbol = tree.decode(bin);
         out.put(symbol);
	 fileCount--;
      }
      
      // closes file
      in.close();
      out.close();
      return 0;
   }
