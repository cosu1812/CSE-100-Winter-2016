/**
 * Assignment: PA2
 * File: BitInputStream.hpp
 * Name: Connie Su
 * Date: 01/26/16
 *
 * Creates BitInputStream to read bits from a byte
 */ 
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#define BYTE_SIZE 8
using namespace std;
class BitInputStream{
private:
   char buf;     // one byte buffer of bits
   int nbits;    // number of bits read from buf
   istream & in; // input stream to use
public:

   /**
    * Initialize a BitInputStream that will use the given istream for input
    */ 
   BitInputStream(istream & is) : in(is){
      // clear buffer
      buf = 0; 
      // initialize bit index
      nbits = BYTE_SIZE;
   }   
   
   /**
    * Read next bit from bit buffer
    * Fill the buffer from the input stream first if needed
    * Return 1 if bit read is 1
    * Return 0 if bit read is 0
    */ 
   int readBit();

   /** Fill the buffer from the input */
   void fill(){
      buf = in.get();
      nbits = 0;
   }
};

#endif // BITINPUTSTREAM_HPP
