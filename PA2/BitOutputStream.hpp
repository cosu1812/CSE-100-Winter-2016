/**
 * Assignment: PA2
 * File: BitOutputStream.hpp
 * Name: Connie Su
 * Date: 01/26/16
 *
 * Creates BitOutputStream to write bits from a byte
 */ 
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
using namespace std;
class BitOutputStream{
private:
   char buf;       // one byte buffer
   int nbits;      // number of bits have been written to buf
   ostream & out;  // reference to the output stream to use
public:
   /** Initialize a BitOutputStream that will use the given ostream for output*/
   BitOutputStream(ostream & os) : out(os), buf(0), nbits(0){ }
   
   /**
    * Write the least significant bit of the argument to the bit buffer, and 
    * increment the bit buffer index. But flush the buffer first, if full
    */ 
   void writeBit(int i);

   /** Send the buffer to the output and clear it */
   void flush(){
      out.put(buf);
      out.flush();
      buf = nbits = 0;
   }
};

#endif // BITOUTPUTSTREAM_HPP
