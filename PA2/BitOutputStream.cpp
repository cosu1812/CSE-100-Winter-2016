/**
 * Assignment: PA2
 * File: BitOutputStream.cpp
 * Name: Connie Su
 * Date: 01/26/16
 *
 * implements writeBit to write bits in a byte to a file
 */ 
#include "BitOutputStream.hpp"

#include <iostream>
#define BYTE_SIZE 8
using namespace std;
   /**
    * Write the least significant bit of the argument to the bit buffer, and 
    * increment the bit buffer index. But flush the buffer first, if full
    */ 
   void BitOutputStream::writeBit(int i){
      // if bit buffer is full then flush it
      if (nbits == BYTE_SIZE) flush();

      // write least significant bit of i into buffer at current index
      buf = buf | ((i & 1) << nbits);

      // increment the index to put in next bit
      nbits++;
   }
