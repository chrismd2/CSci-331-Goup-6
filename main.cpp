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
void HeaderProgramming(string);  /**<Programs values into the header.cpp file as comments*/

int main(){
    if(DEBUG){
        cout << "Hello World\n";
    }

  //HeaderProgramming("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
  blockTester();
}

void blockTester(){
  Block aBlock;
  ofstream sequenceSetFile;
  string fileName = "Sequence_Set.txt";
  sequenceSetFile.open(fileName);
  sequenceSetFile << "Hello File";
  sequenceSetFile.close();

  string records[4] = {"501", "544", "1001", ""};
  string blockInfo = "   501   544  1001";

  Block anotherBlock(records);
  anotherBlock.write(fileName);
  anotherBlock.getRecords();
}

void HeaderProgramming(string endString){
  fstream postalCodes;
  postalCodes.open("us_postal_codes_full.txt");
  ofstream Header;
  Header.open("Header.cpp", ios_base::app);
  string str;
  int headerLength = 0;
  while(str != endString){
    getline(postalCodes, str);
    headerLength += str.length() + 1;
  }
  getline(postalCodes, str);
  Header << "\n//Record length: " << str.length()+1;
  Header << "\n//Header length: " << headerLength;
  postalCodes.close();
  Header.close();
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
