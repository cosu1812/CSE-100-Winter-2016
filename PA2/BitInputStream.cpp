/**
 * Assignment: PA2
 * File: BitInputStream.cpp
 * Name: Connie Su
 * Date: 01/26/16
 *
 * implements readBit method to read encoded text bit by bit
 */

#include "BitInputStream.hpp"

#include <iostream>

/**
 * Read next bit from bit buffer
 * Fill the buffer from the input stream first if needed
 * Return 1 if bit read is 1
 * Return 0 if bit read is 0
 */ 
int BitInputStream::readBit(){
   // if finish reading bits, get new sequence of bits
   if (nbits == BYTE_SIZE) fill();
   
   // gets bit from unread position
   char bit = buf >> nbits;
   bit = bit & 1;

   // increment to next position
   nbits++;

   // returns bit value if 0 or 1
   if (bit == 0) return 0;
   else if (bit = 1) return 1;

   // returns -1 for invalid bit
   else {
      nbits--;
      return -1;
   }

}
