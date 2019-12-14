/**---------------------------------------------------------------------------
 * @Block.h
 * Class Block (Contains Records)
 * @author Tyler Lahr, Sushan Tiwari, and Seth Pomahatch  
 * (Additional comments by Mark Christenson)
 *---------------------------------------------------------------------------
 * Block class:  Used by Sequence Set Class
 *   includes additional features:
 *   -- Sets primary key of the record
 *   -- Search the block
 *	 -- Remove a record
 *	 -- Add a record
 *	 -- Get a record
 *	 -- Move a record
 *	 -- Get the next block pointer
 *	 -- Get the previous block pointer
 *	 -- Set the next block pointer
 *	 -- Set the previous block pointer
 *---------------------------------------------------------------------------*/
 
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
		/** Default constructor
 		 *  @pre None
 		 *  @post A blank Block object is created
 		 */
  	Block();

		/** Relative Block Number constructor
 		 *  @pre None
 		 *  @post A blank Block object is created
 		 */
    Block(unsigned long long _RBN);

		/** Constructor with record numbers
 		 *  @pre The passed array must be of size fill count
 		 *  @post A block object is made using an array of primary keys
 		 */
		Block(string[]);

		/** Constructor with record numbers
 		 *  @pre A string
 		 *  @post A Block object is created using the string
 		 */
  	Block(string);
		
		/**
 		 * @pre A block
 		 * @post Writes the block to a file
 		 */
 		void write(string);

		/** Searches for record
 		 * @pre Primary key
 		 * @post Returns the record or -1 if the record is not found
 		 */
   	int search(string pKey);

   	Block * getNextBlock(); /**< Gets pointer of next block */
   	Block * getPreviousBlock(); /**< Gets pointer of previous block */
   	void setNextBlock( Block * nextBlockPtr ); /**< Sets pointer to next block */
   	void setPrevBlock( Block * previousBlockPtr ); /**< Sets pointer to previous block */
    int getRecordCount(); /**< Gets the record count */
    int getLastRecordPKey(); /**< Gets the last record of the block */

		/**
		 * @pre Primary key
		 * @post Deletes the record with the given primary key
		 */
   	bool deleteRecord(string pKey);
		 
		/**
		 * @pre Primary key
		 * @post Adds the record with the given primary key
		 */
   	bool addRecord(string pKey);
		 
		/**
		 * @pre Record object array
		 * @post Fills record block
		 */
   	void getRecords(Record block[]);

		string blockData(); /**< Returns RBN and records of the block*/
		unsigned long long getRBN();	/**< Gets the relative block number*/

		/** Set rleative block number
		 * @pre unsigned long long int 
		 * @post Sets the relative block number
		 */
    void setRBN(unsigned long long);
    
  private:
   	void sortRecord(); /**< Sorts the record */
 		bool isEmpty;  /**< Bool for empty*/
   	unsigned long long relativeBlockNumber; /**< This blocks identity*/
   	int recordCount; /**< Current number of records in this block*/
   	string records[RECORDSPERBLOCK]; /**< Record identities in this block*/
   	Block * nextBlock;  /**< Next block*/
  	Block * previousBlock; /**< Previous block*/
};
 
#include "Block.cpp"
 
#endif