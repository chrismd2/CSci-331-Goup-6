/**---------------------------------------------------------------------------
 * @Block.cpp
 * Block (Manages blocks)
 * @author Seth Pomahatch
 *---------------------------------------------------------------------------
 * Block:
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
 *---------------------------------------------------------------------------
 */
 
#include "Block.h"
#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;

//prototype for binary search
bool binarySearch(string[],string,int);

/** Default constructor
 *  @pre None
 *  @post A blank Block object is created
 */
Block::Block()
{
  isEmpty = true; 
  relativeBlockNumber = 0;
  recordCount = 0;
  for(int i = 0; i < RECORDSPERBLOCK; i++){
    records[i] = "";
  }
 
  nextBlock = nullptr;
  previousBlock = nullptr;

  if(DEBUG) {cout << "Made an empty block.\n";}
}

string Block::blockData(){
  string returnString = "";
  returnString += relativeBlockNumber;
  for(int i = 0; i < recordCount; i++){
    returnString += " ";
    returnString += records[i];
  }
  return returnString;
}
/** Constructor with record numbers
 *  @pre A string
 *  @post A Block object is created using the string
 */
Block::Block(string _blockData)
{
  if(DEBUG) {cout << "Making a block with \"" << _blockData << "\".\n";}
  
  isEmpty = false; 
  relativeBlockNumber = 0;
  recordCount = 0;

  //set the primary keys of each record
  string tempStr = "";
  int recordNumber = 0;
  int j = 0; //pointer to track the position in the string
  while(recordNumber < BLOCKFILLCOUNT)
  {
    for(int i = 0; i < ZIPLENGTH; i++) //for each element of the pKey
    {
      if( _blockData[j] >= '0' && _blockData[j] <= '9' )
      {
        tempStr += _blockData[j]; //if the element is numeric, store the value
      }
      j++; //increment the pointer
    }
    records[recordNumber] = tempStr; //store the pKey in the class
    tempStr = ""; //clear the temp string
    recordNumber++; //increment the record number
    j++; //start at the beginning of the next pKey
    if(records[recordNumber] != ""){
      recordCount++; //update the number of records in the block
    }
  }

  if(DEBUG) {cout << "Elements of Constructed block " << relativeBlockNumber << ": \"" ;
             for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i] << " ";}
             cout << "\".\n";}

  nextBlock = nullptr;
  previousBlock = nullptr;
}

/** Constructor with record numbers
 *  @pre None
 *  @post A blank Block object is created
 */
Block::Block(string _blockData[RECORDSPERBLOCK])
{
  if(DEBUG) {cout << "Making a block with \"" ;
             for(int i = 0; i < RECORDSPERBLOCK; i++){cout << _blockData[i];}
             cout << "\".\n";}
  
  isEmpty = false; 
  relativeBlockNumber = 0;
  recordCount = 0;

  //set the primary keys of each record
  for(int i = 0; i < RECORDSPERBLOCK; i++)
  {
    records[i] = _blockData[i];
    if(records[i] != ""){
      recordCount++;
    }
  }
  
  if(DEBUG) {cout << "Elements of Constructed block " << relativeBlockNumber << ": \"" ;
             for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i] << " ";}
             cout << "\".\n";}

  nextBlock = nullptr;
  previousBlock = nullptr;
}
 
 
void Block::write(string _fileName)
{
  ofstream file;
  file.open(_fileName);
	if(DEBUG) {cout << "Writing block number " << relativeBlockNumber << " to a file.\n";}
 
  file.seekp(relativeBlockNumber * BLOCKLENGTH);
 
  if(DEBUG){
    cout << relativeBlockNumber << ": ";
    for(int i = 0; i < recordCount; i++){
      cout << records[i] << " ";
    }
    cout << endl;
  }

	file << relativeBlockNumber; 
  if(DEBUG)(cout << "The file should read: \"");
	if(DEBUG){cout << relativeBlockNumber;}
	for(int i = 0;  i < recordCount; i++){
        string record = records[i];
        for(int j = ZIPLENGTH - record.length(); j > 0; j--){
            file << " ";
            if(DEBUG){cout << " ";}
        }
 
        file << record;
        if(DEBUG){cout << record;}
	}
  for(int i = RECORDSPERBLOCK - recordCount; i > 0; i--){
    for(int j = 0; j < ZIPLENGTH; j++){
      file << " ";
      if(DEBUG){cout << " ";}
    }
  }
  if(DEBUG)(cout << "\"\n");
  file.close();
}
 
/** Searches for record
 * @pre Primary key
 * @post Returns the record, primary key, and records per block
 */
bool Block::search(string pKey)
{
	if(DEBUG) {cout << "Searching for " << pKey << " in this block\n";}
	
  return binarySearch(records, pKey, RECORDSPERBLOCK );
}
 
Block * Block::getNextBlock()
{
  return nextBlock;
 
	if(DEBUG) {cout << "Pointer to the next block has been returned.\n";}
}

Block * Block::getPreviousBlock()
{
  return previousBlock;
 
	if(DEBUG) {cout << "Pointer to the previous block has been returned.\n";}
}

void Block::setNextBlock( Block * nextBlockPtr )
{
  nextBlock = nextBlockPtr;

  if(DEBUG) {cout << "Pointer to the next block has been set.\n";}
}

void Block::setPrevBlock( Block * previousBlockPtr )
{
  previousBlock = previousBlockPtr;

  if(DEBUG) {cout << "Pointer to the previous block has been set.\n";}
}
 
void Block::deleteRecord(string pKey)
{
	if(DEBUG) {cout << "Deleting record " << pKey << " in block "<< relativeBlockNumber <<"\n";}
 
	unsigned long long index = 1;
 
	while(!search(pKey) && index < RECORDSPERBLOCK){
        index++;
	}
 
	while(index < RECORDSPERBLOCK)
    {
        records[index] = records[index+1];
        index++;
	}
 
    records[index] = "";
}
 
void Block::addRecord(string pKey)
{
 
 
  if(DEBUG) {cout << ".\n";}
}
 
void Block::getRecords(Record block[])
{
 
 
  if(DEBUG) {cout << ".\n";}
}
 
void Block::moveAroundRecord(string pKey)
{
 
 
  if(DEBUG) {cout << ".\n";}
}

/** Searches block for record by primary key
 * @pre Primary key
 * @post Returns the record or 0 if the record is not found
 */
bool binarySearch(string arr[], string x, int n)
{ 
    int l = 0 ; 
    int r = n - 1; 
    while (l <= r)  
    { 
        int m = l + (r - l) / 2; 

    	int res; 
    	if (x == (arr[m])) 
        res = 0; 
          

      // Check if x is present at mid 
      if (res == 0) 
          return true; 

      // If x greater, ignore left half 
      if (x > (arr[m])) 
        l = m + 1; 

      // If x is smaller, ignore right half 
      else
        r = m - 1; 
    } 

    return false; 
}
 
