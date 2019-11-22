/**---------------------------------------------------------------------------
// @SequenceSet.h
// Class Sequence set
// @author Tyler Lahr, Seth Pomahatch, Sushan Tiwari  (Additional comments by Mark Christenson)
//---------------------------------------------------------------------------
// Block class:  Used by Sequence Set Class
//   includes additional features:
//   --Make record offsets
//   --
//---------------------------------------------------------------------------**/

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
    string SSFileName = "Sequence_Set.txt";
    unsigned long long headerLength(string);
    unsigned long long blockCount;
    unsigned int recordCount;
    //unsigned int indexArray[getRecordCount()][2];
    vector <unsigned int> pKeyIndex;
    vector <unsigned int> offsetIndex;

    Record recordBlock[RECORDSPERBLOCK];  /**<This is where the block is loaded into memory*/
    Block * headBlock = new Block;

    int binarySearchSS(string x);

public:
    SequenceSet();

    /**  makeRecordOffsets
    *    Preconditions:     File must have fixed length primary keys
    *                       equal to the "ziplength" in globals.cpp
    *    Postconditions:    An index file is made for the provided file name
    */
    void makeRecordOffsets(string fileName);

    /**  fillIndex
    *    Preconditions:     "RecordOffsets.txt" file must exist
    *                       makeRecordOffsets can be ran to be sure of this
    *    Postconditions:    The index is made and stored here, in the Sequence Set
    */
    void fillIndex();

    /**  writeBlocks
    *    Preconditions:     None
    *    Postconditions:    All blocks are called to run their write function
    */
    void writeBlocks();

    /**  fillRecord
    *    Preconditions:     Record string must follow parameter conventions
    *    Postconditions:    A record string is loaded into a record object
    */
    Record fillRecord(string RecordString);

    /**  getRecordCount
    *    Preconditions:     Files must be available and the header in data
    *                       file must contain "Records:"
    *    Postconditions:    RecordCount is returned
    */
    unsigned int getRecordCount();

    /**  fetch
    *    Preconditions:     None
    *    Postconditions:    returns the whole record as a string
    */
    string fetch(string pKey);

    /**  fetch
    *    Preconditions:     None
    *    Postconditions:    returns the whole record as a string
    */
    string fetch(unsigned int pKey);

    /**  test
    *    Preconditions:     This is not a permanent function
    *    Postconditions:    See precondition
    */
    int test();
};

#include "SequenceSet.cpp"

#endif
