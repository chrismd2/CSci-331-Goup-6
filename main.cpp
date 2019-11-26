#include <iostream>
#include "Truncate.h"
#include "Record.h"
#include "Block.h"
#include "SequenceSet.h"
#include <string>
#include <fstream>

using namespace std;

void truncateTester(); /**<Tests the Truncate Class*/
void recordTester();
void blockTester();
void nullblockTester();
void SSDeleteAndAddRecordTester();
int main_menu();
void addNewRecord();
void searchForRecord();
void deleteRecord();
void quitProgram();
void extremeCoord();
void test();

SequenceSet SSClass;
bool quit = false;

int main(){
  
  int choice;
  cout << "Sequence Set Created." << endl;
	
  while( !quit )
  {
    cout << endl << endl;
    
    choice = main_menu();

    switch( choice )
    {
      case 1: addNewRecord();
          break;
      case 2: searchForRecord();
          break;
      case 3: deleteRecord();
          break;
      case 4: quitProgram();
          break;
      case 5: extremeCoord();
          break;
      case 6: test();
          break;
      default: cout << "Selecting menu option canceled." << endl;
    }
  }
  
  return 0;
}

void test(){
  recordTester();
  blockTester();
  nullblockTester();
  SSDeleteAndAddRecordTester();
}

void extremeCoord()
{
  string state, dir;
  char direction;
  cout << "Please enter the state you wish to search in its two letter code with CAPS.\n\t";
  cin >> state;
  cout  << "Please enter the direction you wish to find the extreme with a "
        <<"character by choosing n, s, e, or w.\n\t";
  cin >> direction;
  switch(direction){
  case 'n':
    dir = "nothern";
    break;
  case 'e':
    dir = "eastern";
    break;
  case 's':
    dir = "southern";
    break;
  case 'w':
    dir = "western";
    break;
  default:
    dir = "ERROR";
  }
  cout  << "The details of the "<< dir <<" most zipcode\n\t" 
        << SSClass.fetch(SSClass.extremeCoord(state, direction));
}

void quitProgram()
{
	quit = true;
}

void deleteRecord()
{
	string field;
	
	//ask user for pKey
	while(true)
	{
		cout << "Please enter the Zip Code of the Record to delete:" << endl;
		cin  >> field;
		if(field.length() > 6 || field.length() < 1)
		{
			cout << "Invalid Zip Code entered. Please try again." << endl;
		}
		else
		{
			break;
		}
	}
	
	cout << endl << "Searching for Record" << endl;
	int position = SSClass.binarySearchSS(field);
	if(position != -1)
	{
		cout << "Deleting Record from Sequence Set." << endl;
		if ( SSClass.deleteRecord( stoi( field ) ) )
		{
			cout << "Record deleted Successfully." << endl;
		}
		else
		{
			cout << "Error Deleting Record." << endl;
		}
	}
	else
	{
		cout << "Record not found in Sequence Set" << endl;
	}
}

void searchForRecord()
{
	string field;
	
	//ask user for pKey
	while(true)
	{
		cout << "Please enter the Zip Code of the Record to find:" << endl;
		cin  >> field;
		if(field.length() > 6 || field.length() < 1)
		{
			cout << "Invalid Zip Code entered. Please try again." << endl;
		}
		else
		{
			break;
		}
	}
	
	cout << endl << "Searching for Record" << endl;
	int position = SSClass.binarySearchSS(field);
	if(position != -1)
	{
		cout << "Record found in Sequence Set." << endl;
		cout << "Displaying Record:" << endl << endl;
		cout << SSClass.fetch(field) << endl;
	}
	else
	{
		cout << "Record not found in Sequence Set" << endl;
	}
	
}

void addNewRecord()
{
	string field;
	Record record;
	
	//ask user for zip code
	while(true)
	{
		cout << "Please enter the Zip Code of the Record:" << endl;
		cin  >> field;
		if(field.length() > 6 || field.length() < 1)
		{
			cout << "Invalid Zip Code entered. Please try again." << endl;
		}
		else
		{
			record.set_field("zip", field);
			break;
		}
	}
	
	//ask user for city
	while(true)
	{
		cout << "Please enter the City of the Record: (use underscore _ as space)" << endl;
		cin  >> field;
		if(field.length() > 31 || field.length() < 1)
		{
			cout << "Invalid City entered. Please try again." << endl;
		}
		else
		{
			for(int i = 0; i < field.length(); i++)
			{
				if(field[i] == '_')
					field[i] = ' ';
			}
			record.set_field("city", field);
			break;
		}
	}
	
	//ask user for state
	while(true)
	{
		cout << "Please enter the State of the Record (two character format: MN):" << endl;
		cin  >> field;
		if( field.length() != 2 )
		{
			cout << "Invalid State entered. Please try again." << endl;
		}
		else
		{
			record.set_field("state", field);
			break;
		}
	}
	
	//ask user for county
	while(true)
	{
		cout << "Please enter the County of the Record:" << endl;
		cin  >> field;
		if(field.length() > 38 || field.length() < 1)
		{
			cout << "Invalid County entered. Please try again." << endl;
		}
		else
		{
			record.set_field("county", field);
			break;
		}
	}
	
	//ask user for longitude
	while(true)
	{
		cout << "Please enter the Longitude of the Record:" << endl;
		cin  >> field;
		if(field.length() > 8 || field.length() < 1)
		{
			cout << "Invalid Longitude entered. Please try again." << endl;
		}
		else
		{
			record.set_field("long", field);
			break;
		}
	}
	
	//ask user for latitude
	while(true)
	{
		cout << "Please enter the Latitude of the Record:" << endl;
		cin  >> field;
		if(field.length() > 9 || field.length() < 1)
		{
			cout << "Invalid Latitude entered. Please try again." << endl;
		}
		else
		{
			record.set_field("lat", field);
			break;
		}
	}
	
	cout << endl << "New Record Created." << endl;
	SSClass.addRecord( record );
	cout << "New Record added to Sequence Set." << endl;
}

int main_menu()
{
  int userResponce;
  while(true)
  {
	  cout << "Please select an option:" << endl;
	  cout << "1. Add a new Record" << endl;
	  cout << "2. Search for and Display a Record" << endl;
	  cout << "3. Delete a Record" << endl;
	  cout << "4. Quit Program" << endl;
	  cout << "5. Find the X-treme coordinate of a state" << endl;
	  cout << "6. Testing" << endl;
	  cin  >> userResponce;
	  
	  if(userResponce < 1 || userResponce > 6)
		  cout << "Please enter a valid option" << endl;
	  else
		return userResponce;
  }
}

void SSDeleteAndAddRecordTester()
{
  SequenceSet SSClass;
  
  SSClass.deleteRecord(1008);
  SSClass.deleteRecord(1003);
  SSClass.deleteRecord(1004);
  
  string zip = "563";
  string place = "Little Falls";
  string state = "MN";
  string county = "Morrison";
  string longitude = "-74.25";
  string latitude = "79.72";
  Record testRecord(zip, place, state, county, longitude, latitude);
  SSClass.addRecord(testRecord);
  
  zip = "1024";
  Record testRecord2(zip, place, state, county, longitude, latitude);
  SSClass.addRecord(testRecord2);
  
  zip = "1025";
  Record testRecord3(zip, place, state, county, longitude, latitude);
  SSClass.addRecord(testRecord3);
  
  zip = "1051";
  Record testRecord4(zip, place, state, county, longitude, latitude);
  SSClass.addRecord(testRecord4);
  
  zip = "1052";
  Record testRecord5(zip, place, state, county, longitude, latitude);
  SSClass.addRecord(testRecord5);
  
  zip = "300";
  Record testRecord6(zip, place, state, county, longitude, latitude);
  SSClass.addRecord(testRecord6);
  
  SSClass.rewriteSSFile();
}

void nullblockTester(){
  Block * aBlock;
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
  aBlock = new Block(1);
  cout << "Return 1 if the record was found: " << aBlock->search( recordTest ) << endl;

  recordTest = "103";
  aBlock->addRecord(recordTest);

  recordTest = "103";
  aBlock->addRecord(recordTest);

  recordTest = "544";
  aBlock->deleteRecord(recordTest);

  recordTest = "514";
  aBlock->deleteRecord(recordTest);
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
  string longitude = "-74.25";
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
