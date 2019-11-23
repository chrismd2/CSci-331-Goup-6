/**---------------------------------------------------------------------------
 * @SequenceSet.cpp
 * Block (Manages blocks)
 * @author Seth Pomahatch, Tiwari Sushan, Mark Christenson, Tyler Lahr, Ryan Sweeney
 *---------------------------------------------------------------------------
 * SequenceSet:
 *   includes additional features:
 *   --
 *   --
 *---------------------------------------------------------------------------
 */

#include "SequenceSet.h"
#include <iostream>
#include "Truncate.h"
#include "Record.h"
#include "Block.h"
#include "SequenceSet.h"
#include <string>
#include <fstream>

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
}

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
}

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
}

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
}

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

  int position = binarySearchSS(pKey);
  if(DEBUG) {cout << "Searching "<< pKey << " returned: " << position << endl;}
  if(position>=0 && pKey != ""){
    data.seekg(offsetIndex.at(binarySearchSS(pKey)));
    getline(data, returnString);
  }
  data.close();

  return returnString;
}

string SequenceSet::fetch(unsigned int pKey){
  return fetch(to_string(pKey));
}

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
}

/** Searches block for record by primary key
 * @pre Primary key
 * @post Returns true if found otherwise returns false
 */
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
}

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
}

void SequenceSet::writeBlocks(){
  Block * currentBlock = headBlock;
  for(auto i = 0; i < blockCount; i ++){
    if(DEBUG){cout << "Writing block "<< i <<" from the chain." << endl;}
    currentBlock->write(SSFileName);
    currentBlock = currentBlock->getNextBlock();
  }
}

void SequenceSet::fillRecordBlock(unsigned long long blockID){
  string str, zip, passed;
  Block * currentBlock = headBlock;
  for(auto i = 0; i < blockID; i++){
    currentBlock = currentBlock->getNextBlock();
  }

  currentBlock->getRecords(recordBlock);
  for(auto i = 0; i < RECORDSPERBLOCK; i++){
    passed = fetch(recordBlock[i].get_field("ZIP"));
    if(DEBUG){
      cout  << "\n******************************************" 
            << "\nString passed to fill record: " << passed << endl;
    }
    if(passed != " not found.\n"){
      recordBlock[i] = fillRecord(passed);
      if(DEBUG){recordBlock[i].display();}
    }
  }
}

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

    return 0;
}