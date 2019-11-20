/**---------------------------------------------------------------------------
 * @Block.cpp
 * Block (Manages blocks)
 * @author Tyler Lahr, Sushan Tiwari, and Seth Pomahatch  
 * (Additional comments by Mark Christenson)
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
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
 
using namespace std;

//prototype for binary search
int binarySearch(const string[], string,int);
void convertStrArrToIntArr(const string[], int[], int);
void convertIntArrToStrArr(string [], int [], int );

const string null_str = "";
const int NULL_INT = 1000000;

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
  while( j < _blockData.length() && j < BLOCKFILLCOUNT*ZIPLENGTH)
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
    if(records[recordNumber] != ""){
      recordCount++; //update the number of records in the block
	    recordNumber++; //increment the record number
    }
  }

  if(DEBUG) {cout << "Elements of Constructed block " << relativeBlockNumber << ": \"" ;
             for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i] << " ";}
             cout << "\".\n";}

  nextBlock = nullptr;
  previousBlock = nullptr;
}

Block::Block(string _blockData[RECORDSPERBLOCK])
{
  if(DEBUG) {cout << "Making a block with \"" ;
             for(int i = 0; i < BLOCKFILLCOUNT; i++){cout << _blockData[i];}
             cout << "\".\n";}
  
  isEmpty = false; 
  relativeBlockNumber = 0;
  recordCount = 0;

  //set the primary keys of each record
  for(int i = 0; i < BLOCKFILLCOUNT; i++)
  {
    records[i] = _blockData[i];
    if(records[i] != ""){
      recordCount++;
    }
  }
  
  if(DEBUG) {cout << "Elements of Constructed block " << relativeBlockNumber << ": \"" ;
             for(int i = 0; i < BLOCKFILLCOUNT; i++){cout << records[i] << " ";}
             cout << "\".\n";}

  nextBlock = nullptr;
  previousBlock = nullptr;
}
 
 
void Block::write(string _fileName)
{
  ofstream file;
  file.open(_fileName, ios_base::app);	if(DEBUG) {cout << "Writing block number " << relativeBlockNumber << " to a "<< _fileName <<".\n";}
 
  file.seekp(relativeBlockNumber * BLOCKLENGTH);
 
  if(DEBUG){
    cout << relativeBlockNumber << ": ";
    for(int i = 0; i < recordCount; i++){
      cout << records[i] << " ";
    }
    cout << endl;
  }

	file << "RBN " << relativeBlockNumber << ": "; 
  if(DEBUG)(cout << "The file should read: \"");
	if(DEBUG){cout << "RBN " << relativeBlockNumber << ": ";}
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

int Block::search(string pKey)
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
 
bool Block::deleteRecord(string pKey)
{
  if(DEBUG) {cout << "Deleting record " << pKey << " in block "<< relativeBlockNumber <<"\n";}
  if(DEBUG) {cout << "Elements of Constructed block before deleting record: \"" ;
      for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i];}
      cout << "\".\n";}
  
  int position = this -> search(pKey); //get the position of the record to be deleted
  
  if ( position != -1 )
  {
    records[position] = ""; //delete the record
    recordCount--;  //decrement record count
    if(DEBUG) {cout << "Elements of Constructed block after deleting record: \"" ;
        for(int i = 0; i < RECORDSPERBLOCK; i++){if(records[i] == null_str){cout << "null";}else{cout << records[i];}}
        cout << "\".\n";}
    sortRecord(); //sort the record
    if(DEBUG) {cout << "Elements of Constructed block after sorting record: \"" ;
        for(int i = 0; i < RECORDSPERBLOCK; i++){if(records[i] == null_str){cout << "null";}else{cout << records[i];}}
        cout << "\".\n";}
    return true;
  }
	else
	{
	  if(DEBUG) {cout << "Record not found in block. Could not delete"  << "\".\n";}
	  return false;
	}
}
 
bool Block::addRecord(string pKey)
{
  if(DEBUG) {cout << "Adding a record to "<< relativeBlockNumber <<".\n";}
  if(DEBUG) {cout << "Elements of Constructed block before adding record: \"" ;
      for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i];}
      cout << "\".\n";}
  
  for(int i = 0; i < RECORDSPERBLOCK; i++) //go through the block to see if there is empty record
  {
    if( records[i] == null_str) //if there is an empty record
    {
      records[i] = pKey;  //fill the record with the pKey
      recordCount++;  //increment record count
      if(DEBUG) {cout << "Elements of Constructed block after adding record: \"" ;
            for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i];}
            cout << "\".\n";}
      sortRecord(); //sort the record
      if(DEBUG) {cout << "Elements of Constructed block after sorting record: \"" ;
            for(int i = 0; i < RECORDSPERBLOCK; i++){cout << records[i];}
            cout << "\".\n";}
      return true;
    }
  }
 
  if(DEBUG) {cout << "Block Full. Could not add record."  << "\".\n";}

  return false;
}
 
void Block::getRecords(Record block[])
{
  if(DEBUG) {cout << ".\n";}
  
  Record record;
  record.set_field("ZIP", "56303");
}
 
void Block::sortRecord()
{
  if(DEBUG) {cout << "Sorting the records in the block.\n";}

  int int_records_array[RECORDSPERBLOCK]; //to convert the string of records to integers
  convertStrArrToIntArr(records, int_records_array, RECORDSPERBLOCK);

  int n = sizeof(int_records_array)/sizeof(int_records_array[0]); 
  sort(int_records_array, int_records_array+n); 

  //convert back to strings and store in records array of string
  convertIntArrToStrArr(records, int_records_array, RECORDSPERBLOCK);
}

/** Searches block for record by primary key
 * @pre Primary key
 * @post Returns true if found otherwise returns false
 */
int binarySearch(const string arr[], string x, int n)
{ 	
	int int_arr[n];
	int int_string;
	
	//convert the records (array of strings) to array of int
	for (int i = 0; i < n; i++)
	{
    if(arr[i] != null_str)
		  int_arr[i] = stoi(arr[i]);
	}
	
	//convert string to find to int
	int_string = stoi(x);
	
    int l = 0 ; 
    int r = n - 1; 
    while (l <= r)  
    { 
      int m = l + (r - l) / 2; 
		  if(DEBUG) {cout << "mid: " << m <<endl;}
  
      if(DEBUG) {cout << "comparing " << int_string << " and " << int_arr[m] <<endl;}

    	if ( int_arr[m] == int_string ){
        if(DEBUG) {cout << "record found" <<endl;}
        return m; 
		  }
           
      // If x is greater, ignore left half 
      if ( int_arr[m] < int_string ){ 
        l = m + 1;
      if(DEBUG) {cout << "new l: " << l <<endl;}
      }

        // If x is smaller, ignore right half 
      else{
        r = m - 1; 
        if(DEBUG) {cout << "new r: " << l <<endl;}
      }
    } 

    return -1; 
}

/** String to integer
 * @pre An array of strings
 * @post An array of integers
 */
void convertStrArrToIntArr(const string strArr[], int intArr[], int ArrLength)
{
	//convert the records (array of strings) to array of int
	for (int i = 0; i < ArrLength; i++)
	{
    if(strArr[i] == null_str) //if the record is null
      intArr[i] = NULL_INT;
    else
      intArr[i] = stoi(strArr[i]);
	}
}

/** Integer to string
 * @pre An array of integers
 * @post An array of strings
 */
void convertIntArrToStrArr(string strArr[], int intArr[], int ArrLength)
{
  //convert the records (array of strings) to array of int
	for (int i = 0; i < ArrLength; i++)
	{
    if(intArr[i] == NULL_INT)//if the record is null
      strArr[i] = null_str;
    else
      strArr[i] = to_string(intArr[i]);
	}
}
