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
 
#ifndef BLOCK_H
#define BLOCK_H
 
#include <iostream>
#include <string>
#include <fstream>
#include "Record.h"
using namespace std;

class Block
{
   public:
   /**  Default constructor
    *    Preconditions:   None
    *    Postconditions:  Empty block is created
    */
   Block();
   
   Block(string[]);

   Block(string);
 
   void write(string);
   bool search(string pKey);
   Block * getNextBlock();
   Block * getPreviousBlock();
   void setNextBlock( Block * nextBlockPtr );
   void setPrevBlock( Block * previousBlockPtr );
   void deleteRecord(string pKey);
   void addRecord(string pKey);
   void getRecords(Record[]);

   string blockData();
 
   private:
   void moveAroundRecord(string pKey);
 
   bool isEmpty;  /**< Bool for empty*/
   unsigned long long relativeBlockNumber; /**< This blocks identity*/
   int recordCount; /**< Current number of records in this block*/
   string records[4]; /**< Record identities in this block*/
   Block * nextBlock;  /**< Next block*/
   Block * previousBlock; /**< Previous block*/
};
 
#include "Block.cpp"
 
#endif