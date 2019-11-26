/**-------------------------------------------------------------------------------------------------
 * @SequenceSet.h
 * Class Sequence set
 * @author Tyler Lahr, Seth Pomahatch, Sushan Tiwari, Ryan Sweeney, Mark Christenson
 *--------------------------------------------------------------------------------------------------
 * Block class:  Used by Sequence Set Class
 *   includes additional features:
 *   --Make record offsets
 *   --Fill Index
 *   --fillRecordBlock
 *   --extremeCoord
 *   --deleteRecord
 *   --addRecord
 *   --rewriteSSClass
 *   --writeToTxt
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
    unsigned long long headerLength(string);	/**< Gets length of header*/
    unsigned long long blockCount;	/**< Holds number of blocks*/
    unsigned int recordCount;	/**< Holds number of records */
    //unsigned int indexArray[getRecordCount()][2];
    vector<unsigned int>pKeyIndex;	/**< Primary key zipcode to be used with offsetIndex*/
    vector<unsigned int>offsetIndex;	/**< Find a pKey position in pKeyIndex go to that 
                                         * position here to retrieve the offet for that 
                                         * record
																				 */
    vector<vector<string>>stateZips;    /**< States zipcodes*/
    vector<vector<string>>sKeyCounty;	/**< Secondary key for county*/
    vector<vector<string>>sKeyPlace;	/**< Secondary key for place (city)*/
    vector<Block*>blockAvailList;	/**< Stack of empty blocks*/
    Record recordBlock[RECORDSPERBLOCK];  /**< This is where the block is loaded into memory*/
    Block * headBlock = new Block;	/**< Start of the block list*/

    /**Add block state key
		 *	@pre		Block ID is less than block count(ie the block is in the block chain)
		 *	@post		A block in the chain is added to the state keys
		 */
    void addBlockStateKey(unsigned long long blockID);

    /**Add block state key builder
		 *	@pre		None
		 *	@post		Builds the secondary index for states
		 */
    void sKeyStateBuilder();
    

public:
		/** Default constructor
		* @pre File with a name that matches DATAFILENAME in Header.cpp must exist
    *      and it must contain a line equal to HEADERENDSTRING in Header.cpp
		* @post Sequence Set Class is made
		*/
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

    /** Extreme coordinate
    *	@pre	State of type string and Direction of type Char (N, E, S, W)
    *       State code must be in the list of states or the last state in list is used
    *	@post Returns the zipcode containing the most extreme point of said direction
    */
    string extremeCoord(string, char);

		/** Delete record
		 * @pre A primary key (zipcode)
		 * @post Deletes record with given zipcode
		 */
    bool deleteRecord(int pKey);
		
		/** Add record
		 * @pre A record object
		 * @post Adds the record
		 */
    void addRecord(Record record);
    void rewriteSSFile();/**< */

		/** WriteToTxt
		 * @pre Inputs should match source length requirements
		 * @post Writes the record to the data file (us_postal_codes.txt)
		 */
    void writeToTxt(Record, string, string);

		/** Searches block for record by primary key
		* @pre Primary key
		* @post Returns true if found otherwise returns false
		*/
    int binarySearchSS(string x);
    
    /**
    * @pre None
    * @post Returns the various tester results
    */
    int test();
};

#include "SequenceSet.cpp"

#endif

