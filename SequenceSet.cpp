 /**-------------------------------------------------------------------------------------------------
 * @SequenceSet.cpp
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
 
#include "SequenceSet.h"
#include <iostream>
#include "Truncate.h"
#include "Record.h"
#include "Block.h"
#include "SequenceSet.h"
#include <string>
#include <fstream>
#include <vector>
#include <stdio.h>

#include <time.h>

using namespace std;

//binarySearch recycled from block
int binarySearchSS(const string arr[], string x, int n);

SequenceSet::SequenceSet(){
  ofstream SSFile;
  SSFile.open(SSFileName);
  SSFile << "Sequence Set File\n";
  SSFile.close();
  recordCount = getRecordCount();
  fillIndex();
  Block * currentBlock = headBlock;
  blockCount = 0;
  for(unsigned long long i = 0; i < recordCount; i++){
    if(i%BLOCKFILLCOUNT == 0 && i != 0){
	    if(DEBUG){cout << "Making a new block for the chain." << endl;}
      blockCount++;
      Block * newBlock = new Block(blockCount);
      currentBlock->setNextBlock(newBlock);
      newBlock->setPrevBlock(currentBlock);
      currentBlock = newBlock;
    }
    if(DEBUG){cout<<"Passing "<<to_string(pKeyIndex.at(i))<<" into the add function."<<endl;}
    currentBlock->addRecord(to_string(pKeyIndex.at(i)));
  }
  writeBlocks();

  //reset the record avail list
  ofstream recordAvailList;
  recordAvailList.open(recordAvailListFileName);
  recordAvailList << "";
  recordAvailList.close();
  sKeyStateBuilder();

  /*
  ///New Material for B+Tree
  bool testing = true;
  if(testing){cout << "Calling treeBuilder()\n";}
  treeBuilder();
  tree.test();
  */

  cout << "finished constructor\n";
}// End default constructor

/*
///New functions for B+Tree 
void SequenceSet::treeBuilder(){
  bool testing = true;
  Block * currentBlock = headBlock;
  if(testing){cout << "currentBlock set to headBlock\n";}
  unsigned int index = 0;

  while(currentBlock != NULL && (!testing ^ index < 5)){
    if(testing){cout << "inserting RBN " << currentBlock->getRBN() << " to the tree\n";}
    tree.insert(currentBlock);
    if(testing){cout << "Retrieving the next block\n";}
    currentBlock = currentBlock->getNextBlock();
    if(testing){index++;}
  }
  if(currentBlock == NULL){cout << "TreeBuilder exit\n";}
}

//Returns true if Block A < Block B
bool SequenceSet::isLessThan(Block* A, Block* B){
  return ( A -> getLastRecordPKey() < B -> getLastRecordPKey() );
}

//Returns true if Block A > Block B
bool SequenceSet::isGreaterThan(Block* A, Block* B){
  return ( A -> getLastRecordPKey() > B -> getLastRecordPKey() );
}

Block * SequenceSet::TreeSearch(string pKey){
  bool done = false;
  bool found = false;
  unsigned int index = 1;
  Block * currentBlock;

  cout << "Stopped at Block " << currentBlock->getRBN() << ": " << currentBlock->blockData() << endl;

  return currentBlock;
}

///End of new functions for B+Tree 
*/


unsigned long long SequenceSet::headerLength(string _fileName){
  fstream data;
  unsigned long long length = 0;
  unsigned long long L = 0;
  data.open(_fileName);
  string str;

  if(DEBUG){cout << "String outside while loop, in headerLength: " << str << endl;}
  while(data.peek() != EOF){
    if(DEBUG && false){cout << "String in headerLength: " << str << endl;}
    getline(data, str);
    length += str.length();
    length++;
    if(str == HEADERENDSTRING){
      L = length;
      if(DEBUG){cout<<"L defined: "<< L <<"\n";}
    }
  }

  data.close();

  return L;
}// End headerLength

unsigned int SequenceSet::getRecordCount(){
    string fileName = DATAFILENAME;
    string field;
    string str = "";
    char c;
    fstream data;
    unsigned int recordCount = 0;
    data.open(fileName);
    getline(data, field); //Skip title
    while(data.peek() != ':' ){
        data.get(c);
        field += c;
        if(DEBUG && true){cout << "Char c: " << c << endl;}
    }

    //This while is to skip non number values before approaching what to do with the values
    while(data.peek() < '0' || data.peek() > '9' ){
        data.get(c);
    }
    getline(data, str);

    recordCount = stoi(str);

    if(DEBUG) {cout << "String: " << str << "\nrecords: " << recordCount << endl;}
    if(field == "Records"){
        getline(data, str);
        recordCount = stoi(str);
        if(DEBUG){cout << "Record Count: " << recordCount << endl;}
    }
    data.close();

    return recordCount;
}// End getRecordCount

void SequenceSet::fillIndex(){
    string field;
    string str = "";
    char c;
    fstream data;

    data.open("RecordOffsets.txt");

    for(unsigned int i = 0; i < recordCount; i++){
        string recordData = "";
        getline(data, recordData);
        if(DEBUG){cout << "recordData: " << recordData << endl;}
        str = "";
        for(int j = 0; j < ZIPLENGTH; j++){
          str += recordData[j];
        }
        //index[i][0] = stoi(str);  //five chars of string
        pKeyIndex.push_back(stoi(str));
        if(DEBUG){cout << "String: " << str << endl;}
        if(DEBUG){cout << "pKeyIndex.at(i): " << pKeyIndex.at(i) <<endl;}
        str = "";
        for(int j = ZIPLENGTH; j < recordData.length(); j++){
          str += recordData[j];
        }
        //index[i][1] = stoi(str);  //the rest of the string
        offsetIndex.push_back(stoi(str));
        if(DEBUG){cout << "String: " << str << endl;}
        if(DEBUG){cout << "offsetIndex.at("<<i<<"): " << offsetIndex.at(i) <<endl;}
    }
    data.close();
}// End fillIndex

string SequenceSet::fetch(string pKey){
  fstream data;
  data.open(DATAFILENAME);
  string returnString = "";
  for(int i = ZIPLENGTH - pKey.length(); i > 0; i--){
    if(DEBUG){cout << "For loop in fetch. i = " << i << endl;}
    returnString += " ";
  }
  returnString = pKey;
  returnString += " not found.\n";

  int position;
  if(pKey != ""){
    position = binarySearchSS(pKey);
  }
  if(DEBUG) {cout << "Searching "<< pKey << " returned: " << position << endl;}
  if(position>=0 && pKey != ""){
    data.seekg(offsetIndex.at(binarySearchSS(pKey)));
    getline(data, returnString);
  }
  data.close();

  return returnString;
}// End fetch with string

string SequenceSet::fetch(unsigned int pKey){
  return fetch(to_string(pKey));
}// End fetch with int

void SequenceSet::makeRecordOffsets(string fileName){
    string zip = "      ";
    fstream data;
    ofstream index;
    string str;
    index.open("RecordOffsets.txt");
    unsigned long long offset = headerLength(fileName);
    data.open(fileName);
    data.seekg(offset);

    if(DEBUG && false){cout << "String in makeRecordOffsets is: " << str << endl;}
    getline(data, str);

    while(data.peek()!=EOF){
      if (DEBUG && false){cout << str << endl;}
    for(int i = 0; i < ZIPLENGTH; i++){
      zip[i] = str[i];
    }
    if(DEBUG && false){cout<<zip<< " is at " << offset <<endl;}
    index << zip << offset << endl;
    getline(data, str);
    offset += str.length();
    offset++;
    }

    data.close();
    index.close();
}//End makeRecordOffsets

int SequenceSet::binarySearchSS(string x)
{
	//int int_arr[n];
	unsigned int n = recordCount;
	int int_string;
/*
	//convert the records (array of strings) to array of int
	for (unsigned int i = 0; i < n; i++)
	{
    if(arr[i] != null_str)
		  int_arr[i] = stoi(arr[i]);
	}
*/
	//convert string to find to int
	if(DEBUG){cout << "(stoi)ing this string: \"" << x << "\"\n";}
	try{
    int_string = stoi(x);    unsigned int l = 0 ;
    unsigned int r = n - 1;
    while (l <= r)
    {
      int m = l + (r - l) / 2;
		  if(DEBUG) {cout << "mid: " << m <<endl;}

      //if(DEBUG) {cout << "comparing " << int_string << " and " << int_arr[m] <<endl;}
      if(DEBUG) {cout << "comparing " << int_string << " and " << pKeyIndex.at(m) <<endl;}

    	if ( pKeyIndex.at(m) == int_string ){
        if(DEBUG) {cout << "record found" <<endl;}
        return m;
		  }

      // If x is greater, ignore left half
      if ( pKeyIndex.at(m) < int_string ){
        l = m + 1;
        if(DEBUG) {cout << "new l: " << l <<endl;}
      }

        // If x is smaller, ignore right half
      else{
        r = m - 1;
        if(DEBUG) {cout << "new r: " << l <<endl;}
      }
    }
}
	catch(...){cout << "ERROR (stoi)ING THIS STRING: \"" << x << "\"\n";}

    return -1;
}// End binarySearchSS

Record SequenceSet::fillRecord(string RecordString){
  string zip_code, place_name, state, county, latitude, longitude;
  int position = 0;
  if(DEBUG){cout  << "In fillRecord for Sequence Set Class\n\tRecordString: " 
                  << RecordString << endl;}
  zip_code = "";
  for(auto i = 0; i < ZIPLENGTH	; i++){
    if(RecordString[position] != ' '){
      zip_code += RecordString[position];
    }
    position++;
  }

  place_name = "";
  for(int i = 0; i < 31/*Length of place name*/; i++){
    if(RecordString[position] != ' '){
      place_name += RecordString[position];
    }
    position++;
  }

  state = "";
  for(int i = 0; i < 2/*Length of state*/; i++){
    if(RecordString[position] != ' '){
      state += RecordString[position];
    }
    position++;
  }

  county = "";
  for(int i = 0; i < 38/*Length of county*/; i++){
    if(RecordString[position] != ' '){
      county += RecordString[position];
    }
    position++;
  }

  latitude = "";
  for(int i = 0; i < 9/*Length of latitude*/; i++){
    if(RecordString[position] != ' '){
      latitude += RecordString[position];
    }
    position++;
  }

  longitude = "";
  for(int i = 0; i < 8/*Length of longitude*/; i++){
    if(RecordString[position] != ' '){
      longitude += RecordString[position];
    }
    position++;
  }
  if(DEBUG){cout  << "\tRecordElements: " << "\n\t\t" 
                  << zip_code << "\n\t\t" << place_name << "\n\t\t" 
		              << state << "\n\t\t" << county << "\n\t\t" 
                  << latitude << "\n\t\t" << longitude << endl;}

  Record returnRecord(zip_code, place_name, state, county, latitude, longitude);

  if(DEBUG){returnRecord.display();}

  return returnRecord;  
}// End fillRecord

void SequenceSet::writeBlocks(){
  Block * currentBlock = headBlock;
  for(auto i = 0; i < blockCount; i ++){
    if(DEBUG){cout << "Writing block "<< i <<" from the chain." << endl;}
    currentBlock->write(SSFileName);
    currentBlock = currentBlock->getNextBlock();
  }
}// End writeBlocks

void SequenceSet::fillRecordBlock(unsigned long long blockID){
  string str, zip, passed;
  Block * currentBlock = headBlock;
  for(auto i = 0; i < blockID; i++){
    currentBlock = currentBlock->getNextBlock();
  }

  currentBlock->getRecords(recordBlock);
  for(auto i = 0; i < currentBlock->getRecordCount(); i++){
    passed = fetch(recordBlock[i].get_field("ZIP"));
    if(DEBUG){
      cout  << "\n******************************************" 
            << "\nString passed to fill record: " << passed << endl;
    }
    if(passed != " not found.\n" && passed != " not found."){
      recordBlock[i] = fillRecord(passed);
      if(DEBUG){recordBlock[i].display();}
    }
  }
}// End fillRecordBlock

void SequenceSet::addBlockStateKey(unsigned long long blockID){
  fillRecordBlock(blockID);
  Block * currentBlock = headBlock;

  for(auto i = 0; i < blockID; i++){
    currentBlock = currentBlock->getNextBlock();
  }

  for(auto i = 0; i < currentBlock->getRecordCount(); i++){
    string state = recordBlock[i].get_field("state");

    for(auto i = 0; i < RECORDSPERBLOCK; i++){
      string state = recordBlock[i].get_field("state");

      if(state != ""){
	bool stateFound = false;
	unsigned int index = 0;

	if(stateZips.size() == 0){
	        vector <string> newRow;
        	newRow.push_back(state);
	        stateZips.push_back(newRow);
	}

	while(index < stateZips.size() && !stateFound){
		if(stateZips[index].at(0) == state){
			if(DEBUG){cout << "Found " << state << " at index = " << index << endl;}
			stateFound = true;
		}
		else{index++;}
	}

	if(!stateFound){
		if(DEBUG){cout << state<<" not found.\n";}
	        vector <string> newRow;
        	newRow.push_back(state);
	        stateZips.push_back(newRow);
		if(DEBUG){cout << stateZips[index].at(0)<<" pushed successfully.\n";}
		if(DEBUG){
			stateZips[index].push_back(":)");
			cout << "Pushing a smily :)\n";
			cout << stateZips[index].at(1) << endl;
			stateZips[index].pop_back();
		}
	}

	if(DEBUG){cout << "Pushing " << recordBlock[i].get_field("zip") <<" to "<< index <<" column.\n";}
	stateZips[index].push_back(recordBlock[i].get_field("zip"));
	//if(DEBUG){cout << stateZips[index].at(stateZips[index].size() - 1)<<" pushed successfully.\n";}


	if(DEBUG){cout	<< stateZips[index].at(0) << ": " 
		<< stateZips[index].at(stateZips[index].size()-1) << endl;}
      }
    }
  }
}// End addBlockStateKey


bool SequenceSet::deleteRecord(int pKey)
{
  //search if the record is in the sequence set
  int position = binarySearchSS( to_string(pKey) );
  if(DEBUG) {cout << "Searching for "<< pKey << " returned: " << position << endl;}
  if(position == -1){
    cout << "Record does not exist in Sequence Set." << endl;
    return false;
  }
  else{
    //add deleted record offset to avail list
	string strTemp = "";
	string newString = "";
	fstream recordAvailListIn;
	recordAvailListIn.open(recordAvailListFileName);
	while(recordAvailListIn.peek() != EOF){
		strTemp += recordAvailListIn.get();
		if(DEBUG){cout << strTemp << endl;}
    }
	newString = to_string( offsetIndex.at(position) ) + "/" + to_string( position ) + "\n" + strTemp;
	if(DEBUG){cout << newString << " result" << endl;}
	recordAvailListIn.close();
	
    ofstream recordAvailList;
    recordAvailList.open(recordAvailListFileName);
    recordAvailList << newString;
    recordAvailList.close();

    //delete record from us_postal_codes.txt
    fstream usPostalCodes;
    usPostalCodes.open("us_postal_codes.txt");
    usPostalCodes.seekg(offsetIndex.at(position));
    for(int i = 0; i < 94; i++){ //94 is the length of record
      usPostalCodes << " ";
    }
    usPostalCodes.close();

    //delete record in index vector 
    pKeyIndex.erase(pKeyIndex.begin() + position);
    offsetIndex.erase(offsetIndex.begin() + position);
	  if(DEBUG) {position = binarySearchSS( to_string(pKey) );}
    if(DEBUG) {cout << "Deleted record in index vector. Researching for "<< pKey << " returned: " << position << endl;}
    recordCount--; //decrement the total record count

    //delete record in linked list of blocks
    Block * currentBlock = headBlock;
    for(auto i = 0; i < blockCount; i ++){
      if(DEBUG){cout << "Searching block "<< i <<" from the chain." << endl;}
      if( pKey <= currentBlock->getLastRecordPKey() ){
        currentBlock->deleteRecord( to_string(pKey) );
        break;
      }
      else{
        currentBlock = currentBlock->getNextBlock();
      }
    }

    //merge blocks if needed
    if( currentBlock->getRecordCount() < RECORDSPERBLOCK / 2 ){
      //check next block to see if it can merge
      if( (currentBlock->getNextBlock())->getRecordCount() == RECORDSPERBLOCK / 2 ){
        currentBlock->getRecords( recordBlock ); //get the pkeys
        for(int i = 0; i < currentBlock->getRecordCount(); i++){
          (currentBlock->getNextBlock())->addRecord(recordBlock[i].get_field("zip"));
          currentBlock->deleteRecord( recordBlock[i].get_field("zip") );
        }
          //add the pointer to the current block to the avail vector
          blockAvailList.push_back( currentBlock );
          //change the pointers to avoid the empty block
          currentBlock->getPreviousBlock()->setNextBlock( currentBlock->getNextBlock() );
          currentBlock->getNextBlock()->setPrevBlock( currentBlock->getPreviousBlock() );
          blockCount--;
      }
      //check if previous block can merge
      else if( (currentBlock->getPreviousBlock())->getRecordCount() == RECORDSPERBLOCK / 2 ){
        currentBlock->getRecords( recordBlock ); //get the pkeys
        for(int i = 0; i < currentBlock->getRecordCount(); i++){
          (currentBlock->getPreviousBlock())->addRecord(recordBlock[i].get_field("zip"));
          currentBlock->deleteRecord( recordBlock[i].get_field("zip") );
        }
          //add the pointer to the current block to the avail vector
          blockAvailList.push_back( currentBlock );
          //change the pointers to avoid the empty block
          currentBlock->getPreviousBlock()->setNextBlock( currentBlock->getNextBlock() );
          currentBlock->getNextBlock()->setPrevBlock( currentBlock->getPreviousBlock() );
          blockCount--;
      }
      //check if next block can redistribute
      else if( (currentBlock->getNextBlock())->getRecordCount() > RECORDSPERBLOCK / 2 ){
        (currentBlock->getNextBlock())->getRecords( recordBlock ); //get the pkeys
        currentBlock->addRecord( recordBlock[0].get_field("zip") );
        (currentBlock->getNextBlock())->deleteRecord( recordBlock[0].get_field("zip") );
      }
    }
	rewriteSSFile();
    return true;
  }
}// End deleteRecord

string SequenceSet::extremeCoord(string state, char direction)
{
  direction = toupper(direction);
	float extremePoint = 0;
	string zip = "";
  for(int i = 0; i < 2; i++){
    zip+=toupper(state[i]);
  }
  state = zip;
	zip = "";
  Record currentRecord;
  string str = state;

  bool found = false;
  unsigned int index = 0;
  while(index < stateZips.size() - 1 && !found){
    if(stateZips[index][0] == str){found = true;}
    else{index++;}
  }
  currentRecord = fillRecord(fetch(stateZips[index][1]));
  
	switch(direction)
	{
		case 'N':
		{
      extremePoint = stof(currentRecord.get_field("Lat"));
      zip = currentRecord.get_field("zip");
			for(int i = 1; i < stateZips[index].size(); i++)
			{
				currentRecord = fillRecord(fetch(stateZips[index][i]));
				if(extremePoint < stof(currentRecord.get_field("Lat")))
				{
          zip = currentRecord.get_field("zip");
					extremePoint = stof(currentRecord.get_field("Lat"));
				}
			}
		}
		break;

		case 'E':
		{
			extremePoint = stof(currentRecord.get_field("Long"));
			zip = currentRecord.get_field("zip");
			for(int i = 1; i < stateZips[index].size(); i++)
			{
				currentRecord = fillRecord(fetch(stateZips[index][i]));
				if(extremePoint < stof(currentRecord.get_field("Long")))
				{
          zip = currentRecord.get_field("zip");
					extremePoint = stof(currentRecord.get_field("Long"));
				}
			}
		}
		break;

		case 'S':
		{
			extremePoint = stof(currentRecord.get_field("Lat"));
			zip = currentRecord.get_field("zip");
			for(int i = 1; i < stateZips[index].size(); i++)
			{
				currentRecord = fillRecord(fetch(stateZips[index][i]));
				if(extremePoint > stof(currentRecord.get_field("Lat")))
				{
          zip = currentRecord.get_field("zip");
					extremePoint = stof(currentRecord.get_field("Lat"));
				}
			}
		}
		break;

		case 'W':
		{
			extremePoint = stof(currentRecord.get_field("Long"));
			zip = currentRecord.get_field("zip");
			for(int i = 1; i < stateZips[index].size(); i++)
			{
				currentRecord = fillRecord(fetch(stateZips[index][i]));
				if(extremePoint > stof(currentRecord.get_field("Long")))
				{
          zip = currentRecord.get_field("zip");
					extremePoint = stof(currentRecord.get_field("Long"));
				}
			}
		}
		break;

    default:
    {
      cout << "UNDEFINED OPTION\n";
    }
	}
	return zip;
}// End extremeCoord

int SequenceSet::test(){
    string field;
    string str = "";
    char c;
    fstream data;

    int randomRecord = rand() % recordCount;
    //cout << "Retrieving record: " << index[randomRecord][0] << endl;
    cout << "Retrieving record: " << pKeyIndex.at(randomRecord) << endl;
    data.open(DATAFILENAME);
    //data.seekg(index[randomRecord][1]);
    data.seekg(offsetIndex.at(randomRecord));
    getline(data, str);
    cout << str << endl;

    cout << fetch(1721) << endl;
    fillRecordBlock(88);

    for(auto i = 0; i < RECORDSPERBLOCK; i++){
      if(DEBUG){cout <<"\n***********************************\n";}
      recordBlock[i].display();
    }

    sKeyStateBuilder();
    
    unsigned int index = 0;
    unsigned int record = 1;
    Record currentRecord;
    
    str = "MN";
    bool found = false;
    while(index < stateZips.size() && !found){
      if(stateZips[index][0] == str){found = true;}
      else{index++;}
    }

    while(record < stateZips[index].size() - 1){
      str = fetch(stateZips[index][record]);
      cout << str << endl;
      currentRecord = fillRecord(str);
      currentRecord.display();
      record++;
    }

    cout << extremeCoord(str, 'n') << endl;

    return 0;
}// End test


void SequenceSet::sKeyStateBuilder(){
    if(DEBUG){cout << "Building sKeys for states.\n";}
    Block * currentBlock = headBlock;
    unsigned int index = 0;
    while(currentBlock!=NULL){
      addBlockStateKey(index);
      currentBlock = currentBlock->getNextBlock();
      index++;
    }
}//End sKeyStateBuilder

void SequenceSet::addRecord(Record record)
{
	//search record in linked list of blocks
	Block * currentBlock = headBlock;
	for(auto i = 0; i < blockCount; i ++){
		if(DEBUG){cout << "Searching block "<< i <<" from the chain." << endl;}
		if( stoi( record.get_field("zip") ) <= currentBlock->getLastRecordPKey() ){ //find the right block
      if(currentBlock->getRecordCount() == RECORDSPERBLOCK){ //if the block is full, do block splitting
        if( !blockAvailList.empty() ){  //if there exists a current empty block
          Block* tempBlockPtr = blockAvailList.back(); //get the pointer to the empty block
          blockAvailList.pop_back();  //delete the pointer from the avail list
          //add the relative block to the linked list
          tempBlockPtr->setNextBlock( currentBlock->getNextBlock() );
          tempBlockPtr->setPrevBlock( (currentBlock->getNextBlock())->getPreviousBlock() );
          (currentBlock->getNextBlock())->setPrevBlock(tempBlockPtr);
          currentBlock->setNextBlock(tempBlockPtr);
          //split the data into the new block number
          currentBlock->getRecords( recordBlock ); //get the pkeys
          for(int i = RECORDSPERBLOCK / 2; i < RECORDSPERBLOCK; i++){
            (currentBlock->getNextBlock())->addRecord(recordBlock[i].get_field("zip"));
            currentBlock->deleteRecord( recordBlock[i].get_field("zip") );
          }
          //add the new record to the block
          currentBlock->addRecord( record.get_field("zip") );
          blockCount++;
          break; //stop searching through linked list of blocks
        }
        else{  //if a current empty block doesn't exist, create a new block......
          Block* newBlockPtr = new Block;
          newBlockPtr->setRBN(blockCount);
          newBlockPtr->setNextBlock( currentBlock->getNextBlock() );
          newBlockPtr->setPrevBlock( (currentBlock->getNextBlock())->getPreviousBlock() );
          (currentBlock->getNextBlock())->setPrevBlock(newBlockPtr);
          currentBlock->setNextBlock(newBlockPtr);
          //split the data into the new block number
          currentBlock->getRecords( recordBlock ); //get the pkeys
          for(int i = RECORDSPERBLOCK / 2; i < RECORDSPERBLOCK; i++){
            (currentBlock->getNextBlock())->addRecord(recordBlock[i].get_field("zip"));
            currentBlock->deleteRecord( recordBlock[i].get_field("zip") );
          }
          //add the new record to the block
          currentBlock->addRecord( record.get_field("zip") );
          blockCount++;
          break; //stop searching through linked list of blocks
        }
      }
      else{
        currentBlock->addRecord( record.get_field("zip") );
      }
			break; //stop searching through linked list of blocks
		}
		else{
			currentBlock = currentBlock->getNextBlock();
		}
	}

  //add record to us_postal_codes.txt
  fstream recordAvailList;
  string str = "";
  string strTemp = "";
  string offset = "";
  string position = "";
  recordAvailList.open(recordAvailListFileName);
  if( recordAvailList.peek() != EOF ){ //if recordAvailList is not empty
    fstream usPostalCodes;
    usPostalCodes.open("us_postal_codes.txt");
    getline(recordAvailList, str); //get the offset and vector position from avail list
	int i = 0;
	while( str[i] != '/' ){ //parse the offset from the string
		offset += str[i];
		if(DEBUG){cout << offset << endl;}
		i++;
	}
	i++;
	while( i < str.length()  ){ //parse the position from the string
		position += str[i];
		if(DEBUG){cout << position << endl;}
		i++;
	}
    writeToTxt(record, offset, "us_postal_codes.txt");
    usPostalCodes.close();
	recordAvailList.close();
	//update the recordAvailList
	recordAvailList.open(recordAvailListFileName);
	str += "\n";
	if(DEBUG){cout << str << " str to delete" << endl;}
	while(recordAvailList.peek() != EOF){
		strTemp += recordAvailList.get();
		if(DEBUG){cout << strTemp << endl;}
        if(strTemp == str){
            strTemp = "";
        }
    }
	recordAvailList.close();
	remove("availRecordList.txt");
	ofstream recordAvailListOut;
	recordAvailListOut.open(recordAvailListFileName, ios::app);
	if(DEBUG){cout << strTemp << " result" << endl;}
	recordAvailListOut << strTemp;
    recordAvailListOut.close();
	//add record to index vector
	if(DEBUG){for(int i=0; i<20; ++i)std::cout << pKeyIndex[i] << ' ';}
	pKeyIndex.push_back(stoi( record.get_field("zip") ) );
	sort(pKeyIndex.begin(), pKeyIndex.end() );
	int position = binarySearchSS( record.get_field("zip") );
    offsetIndex.insert(offsetIndex.begin() + position, stoi( offset ) );
	if(DEBUG){cout <<endl;}
	if(DEBUG){for(int i=0; i<20; ++i)std::cout << pKeyIndex[i] << ' ';}
  }
  else{ //if recordAvailList is empty
	unsigned int nextOffset = offsetIndex.back() + 95;//95 is record length+1
	if(DEBUG){cout << nextOffset << " nextoffset" << endl;}
	if(DEBUG){for(int i=0; i<20; ++i)std::cout << pKeyIndex[i] << ' ';}
	pKeyIndex.push_back(stoi( record.get_field("zip") ) );
	sort(pKeyIndex.begin(), pKeyIndex.end() );
	int position = binarySearchSS( record.get_field("zip") ); 
    offsetIndex.insert(offsetIndex.begin() + position, nextOffset );
	if(DEBUG){cout <<endl;}
	if(DEBUG){for(int i=0; i<20; ++i)std::cout << pKeyIndex[i] << ' ';}
	writeToTxt(record, to_string( nextOffset ), "us_postal_codes.txt");
	ofstream usPostalCodes;
    usPostalCodes.open("us_postal_codes.txt", ios::app);
	usPostalCodes << endl;
	usPostalCodes.close();
  }
  
  rewriteSSFile();
}// End addRecord

void SequenceSet::rewriteSSFile()
{
	//rewrite the squence set file with missing record
    remove("Sequence_Set.txt");
    ofstream SSFile;
    SSFile.open(SSFileName);
    SSFile << "Sequence Set File\n";
    SSFile.close();
    writeBlocks();
}//End rewriteSSFile

//write the record to the postal codes file
void SequenceSet::writeToTxt(Record record, string offset, string _fileName)
{
	fstream data;
	data.open(_fileName);
	data.seekg( stoi( offset ) );
	   
	string dataString = "";
	string totalString = "";
	
	dataString = record.get_field("Zip");
	int fieldLength = 6;
	for(int i = 0; i < fieldLength - dataString.length(); i++){
		totalString += " ";
	}
	totalString += dataString;
	
	dataString = record.get_field("city");
	fieldLength = 31;
	totalString += dataString;
	for(int i = 0; i < fieldLength - dataString.length(); i++){
		totalString += " ";
	}
	
	dataString = record.get_field("state");
	totalString += dataString;
	
	dataString = record.get_field("county");
	fieldLength = 38;
	totalString += dataString;
	for(int i = 0; i < fieldLength - dataString.length(); i++){
		totalString += " ";
	}
	
	dataString = record.get_field("long");
	while(dataString.length() > 7){
		dataString.pop_back();
	}
	fieldLength = 8;
	for(int i = 0; i < fieldLength - dataString.length(); i++){
		totalString += " ";
	}
	totalString += dataString;
	
	dataString = record.get_field("lat");
	fieldLength = 9;
	while(dataString.length() > 8){
		dataString.pop_back();
	}
	for(int i = 0; i < fieldLength - dataString.length(); i++){
		totalString += " ";
	}
	totalString += dataString;
	
	data << totalString;
	
	data.close();
}// End writeToTxt