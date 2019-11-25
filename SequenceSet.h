/**-------------------------------------------------------------------------------------------------
 * @SequenceSet.h
 * Class Sequence set
 * @author Tyler Lahr, Seth Pomahatch, Sushan Tiwari, Ryan Sweeney 
 * (Additional comments by Mark Christenson)
 *--------------------------------------------------------------------------------------------------
 * Block class:  Used by Sequence Set Class
 *   includes additional features:
 *   --Make record offsets
 *   --
 ---------------------------------------------------------------------------------------------------
 */

#ifndef SEQUENCESET_H
#define SEQUENCESET_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Block.h"
#include "Record.h"

using namespace std;

class SequenceSet
{
private:
    string SSFileName = "Sequence_Set.txt";	/**< Variable for Sequence_set.txt*/
    string recordAvailListFileName = "availRecordList.txt";	/**< Variable for availRecordList.txt*/
    unsigned long long headerLength(string);	/**< */
    unsigned long long blockCount;	/**< */
    unsigned int recordCount;	/**< */
    //unsigned int indexArray[getRecordCount()][2];
    vector<unsigned int>pKeyIndex;
    vector<unsigned int>offsetIndex;
    vector<vector<string>>stateZips;    
    vector<vector<string>>sKeyCounty;
    vector<vector<string>>sKeyPlace;
    vector<Block*>blockAvailList;
    Record recordBlock[RECORDSPERBLOCK];  /**< This is where the block is loaded into memory*/
    Block * headBlock = new Block;

public:
    SequenceSet();

    /**  Make record offsets
    *    @pre		File must have fixed length primary keys
    *         	equal to the "ziplength" in globals.cpp
    *    @post  An index file is made for the provided file name
    */
    void makeRecordOffsets(string fileName);

    /**  Fill Index
    *    @pre		"RecordOffsets.txt" file must exist
    *            makeRecordOffsets can be ran to be sure of this
    *    @post   The index is made and stored here, in the Sequence Set
    */
    void fillIndex();

    /**  Fill record block
    *    @pre		blockID must be less than the block count
    *    @post	Block is loaded into a record block
    */
    void fillRecordBlock(unsigned long long blockID);

    /**  Write blocks
    *    @pre		None
    *    @post	All blocks are called to run their write function
    */
    void writeBlocks();

    /**  Fill record
    *    @pre		Record string must follow parameter conventions
    *           Record string must be complete, call fetch if needed
    *    @post	A record string is loaded into a record object
    */
    Record fillRecord(string RecordString);

    /**  Get record count
    *    @pre		Files must be available and the header in data
    *           file must contain "Records:"
    *    @post	RecordCount is returned
    */
    unsigned int getRecordCount();

    /**  Fetch string
    *    @pre		None
    *    @post	returns the whole record as a string
    */
    string fetch(string pKey);

    /**  Fetch unsigned int
    *    @pre		None
    *    @post	returns the whole record as a string
    */
    string fetch(unsigned int pKey);

    /**Add block state key
		 *	@pre		Block ID is less than block count
		 *	@post		******************************************************add post
		 */
    void addBlockStateKey(unsigned long long blockID);

    /**Add block state key builder
		 *	@pre		None
		 *	@post		Builds the secondary index for states
		 */
    void sKeyStateBuilder();

		/** Extreme coordinate
		 *	@pre	State of type string and Direction (N, E, S, W)
		 *	@post Returns the zipcode containing the most extreme point of said direction
		 */
		string extremeCoord(string, char);

    /**  Test 1
    *    Preconditions:     This is not a permanent function
    *    Postconditions:    See precondition
    */
    int test();

    bool deleteRecord(int pKey);
    void addRecord(Record record);
	void rewriteSSFile();
	void writeToTxt(Record, string, string);
	int binarySearchSS(string x);
};

#include "SequenceSet.cpp"

#endif

