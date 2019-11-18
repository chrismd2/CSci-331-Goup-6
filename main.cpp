#include <iostream>
#include "Truncate.h"
#include "Record.h"
#include "Block.h"
#include <string>
#include <fstream>

using namespace std;

void truncateTester(); /**<Tests the Truncate Class*/
void recordTester();
void blockTester();
unsigned long long headerLength(string _fileName);
void makeRecordOffsets(string);

int main(){
  //makeRecordOffsets("us_postal_codes.txt");
  //blockTester();

  string fileName = "us_postal_codes.txt";
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
  data.open("RecordOffsets.txt");

  unsigned int index[recordCount][2];
  for(unsigned int i = 0; i < recordCount; i++){
    string recordData = "";
    getline(data, recordData);
    if(DEBUG && false){cout << "recordData: " << recordData << endl;}
    str = "";
    for(int j = 0; j < ZIPLENGTH; j++){
      str += recordData[j];
    }
    index[i][0] = stoi(str);  //five chars of string
    if(DEBUG && false){cout << "String: " << str << endl;}
    if(DEBUG && false){cout << "index[i][0]: " << index[i][0] <<endl;}
    str = "";
    for(int j = ZIPLENGTH; j < recordData.length(); j++){
      str += recordData[j];
    }
    index[i][1] = stoi(str);  //the rest of the string
    if(DEBUG && false){cout << "String: " << str << endl;}
    if(DEBUG && false){cout << "index[i][1]: " << index[i][1] <<endl;}
  }
  data.close();

  int randomRecord = rand() % recordCount;
  cout << "Retrieving record: " << index[randomRecord][0] << endl;
  data.open(fileName);
  data.seekg(index[randomRecord][1]);
  getline(data, str);
  cout << str << endl;
}


void blockTester(){
  Block aBlock;
  ofstream sequenceSetFile;
  string fileName = "Sequence_Set.txt";
  sequenceSetFile.open(fileName);
  sequenceSetFile << "Hello File\n";
  sequenceSetFile.close();

  string records[4] = {"501", "544", "1001", ""};
  string blockInfo = "   501   544  1001  1002";

  //test block constructor
  Block anotherBlock(blockInfo);
  anotherBlock.write(fileName);

  //test block search method
  string recordTest = "1002";
  cout << "Return 1 if the record was found: " << anotherBlock.search( recordTest ) << endl;

  recordTest = "103";
  anotherBlock.addRecord(recordTest);
  
  recordTest = "103";
  anotherBlock.addRecord(recordTest);

  recordTest = "544";
  anotherBlock.deleteRecord(recordTest);
  
  recordTest = "514";
  anotherBlock.deleteRecord(recordTest);
}

void makeRecordOffsets(string fileName){
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

unsigned long long headerLength(string _fileName){
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
    if(str == "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"){
      L = length;
      if(DEBUG){cout<<"L defined: "<< L <<"\n";}
    }
  }
  
  data.close();

  return L;
}

void truncateTester(){
  Truncate t;
  Truncate t2(5);
  string str = "123456789AB";

  cout << endl << "The String is " << str;
  cout << endl << "The String AS it is modified is " << t.modifyString(str);
  cout << endl << "The String IF it was modified is " << t2.truncatedString(str);
  cout << endl << "The String is " << str << endl;
}

void recordTester(){
  //test default constructor
	Record testRecord;
  cout << "Default constructor record (should be empty):";
  testRecord.display();
  cout << endl;

  //test fill record
  string zip = "56345";
  string place = "Little Falls";
  string state = "Minnesota";
  string county = "Morrison";
  string longitude = "74.25";
  string latitude = "79.72";

  cout << "Fill Record with : " << zip << " " << place << " " << state << " " << county << " " << longitude << " " << latitude;

  testRecord.set_field( "z", zip );
  testRecord.set_field( "place", place );
  testRecord.set_field( "STATE", state );
  testRecord.set_field( "c", county );
  testRecord.set_field( "long", longitude );
  testRecord.set_field( "lat", latitude );

  testRecord.display();
  cout << endl;

  //test constructor 2
  float longitude_float = 74.25;
  float latitude_float = 79.72;

  Record testRecord2(zip, place, state, county, longitude, latitude);

  cout << "Constructor2 record (record should be full):";
  testRecord2.display();
	
	//test constructor 3
  Grid grid_test(longitude_float, latitude_float);

  Record testRecord3(zip, place, state, county, grid_test);

  cout << "Constructor3 record (record should be full):";
  testRecord3.display();

  //test display field
  cout << endl << "Test Display Field, display city:";
  testRecord3.display("CITY");
  cout << "~expected: Little Falls" << endl;

  cout << "Test Display Field, display state:";
  testRecord3.display("STATE");
  cout << "~expected: Minnesota" << endl;
}
