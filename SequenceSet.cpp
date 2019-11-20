/**---------------------------------------------------------------------------
 * @SequenceSet.cpp
 * Block (Manages blocks)
 * @author Seth Pomahatch, Tiwari Sushan, Mark Christenson, Tyler, Ryan
 *---------------------------------------------------------------------------
 * SequenceSet:
 *   includes additional features:
 *   -- Sets primary key of the record
 *   -- Search the block
 *	 -- Remove a record
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

int SequenceSet::test(){
    string fileName = "us_postal_codes.txt";
    string field;
    string str = "";
    char c;
    fstream data;
    unsigned int recordCount = getRecordCount();

    data.open("RecordOffsets.txt");

    unsigned int index[recordCount][2];
    for(unsigned int i = 0; i < recordCount; i++){
        string recordData = "";
        getline(data, recordData);
        if(DEBUG){cout << "recordData: " << recordData << endl;}
        str = "";
        for(int j = 0; j < ZIPLENGTH; j++){
          str += recordData[j];
        }
        index[i][0] = stoi(str);  //five chars of string
        if(DEBUG){cout << "String: " << str << endl;}
        if(DEBUG){cout << "index[i][0]: " << index[i][0] <<endl;}
        str = "";
        for(int j = ZIPLENGTH; j < recordData.length(); j++){
          str += recordData[j];
        }
        index[i][1] = stoi(str);  //the rest of the string
        if(DEBUG){cout << "String: " << str << endl;}
        if(DEBUG){cout << "index[i][1]: " << index[i][1] <<endl;}
    }
    data.close();

    int randomRecord = rand() % recordCount;
    cout << "Retrieving record: " << index[randomRecord][0] << endl;
    data.open(fileName);
    data.seekg(index[randomRecord][1]);
    getline(data, str);
    cout << str << endl;

    return 0;
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
