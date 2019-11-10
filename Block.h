/**---------------------------------------------------------------------------
// @Block.h
// Class Block (Contains Records)
// @author Tyler Lahr and Sushan Tiwari  (Additional comments by Mark Christenson)
//---------------------------------------------------------------------------
// Block class:  Used by Sequence Set Class
//   includes additional features:
//   --
//   --
//   --
//   --
//   --
//---------------------------------------------------------------------------**/

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include "Record.h"
using namespace std;

class Block
{
   public:
   /**  Default constructor
        Preconditions:   None
        Postconditions:  Empty block is created*/
   Block();

   void write(fstream);
   bool search(string pKey);
   unsigned long long getNextBlock();
   void deleteRecord(string pKey);
   void addRecord(string pKey);
   void getRecords(Record[]);

   private:
   void moveAroundRecord(string pKey);
   void moveReadWriteHead(fstream file, streampos pos);
   const int RECORDSPERBLOCK = 4; /**< Maximum records for the block can be defined globally*/
   const int ZIPLENGTH = 5 * ; /**< Max length of the zip code in digits can be defined globally*/
   const int RBNLENGTH = 8 * ; /**< Max length of the RBN code in digits can be defined globally*/
   const int BLOCKLENGTH = RBNLENGTH + RECORDSPERBLOCK * ZIPLENGTH; /**< Maximum length for the block can be defined globally*/
   bool isEmpty;  /**< Bool for empty*/
   unsigned long long relativeBlockNumber; /**< This blocks identity*/
   int recordCount; /**< Current number of records in this block*/
   string [RECORDSPERBLOCK] records; /**< Record identities in this block*/
   Block * nextBlock;  /**< Next block*/
   Block * previousBlock; /**< Previous block*/
};

#include "Block.cpp"

#endif


