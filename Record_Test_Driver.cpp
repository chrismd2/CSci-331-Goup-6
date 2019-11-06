//g++ -std=c++11  -o record_test Record_Test_Driver

#include "Record.cpp"
#include<iostream>
#include<string>

using namespace std;


int main()
{
  //test default constructor
	Record testRecord;
  cout << "Default constructor Record:";
  testRecord.display();

  //test fill record
  string zip = "56345";
  string place = "Little Falls";
  string state = "Minnesota";
  string county = "Morrison";
  float longitude = 74.25;
  float latitude = 79.72;

  testRecord.set_zip_code( zip );
  testRecord.set_place_name( place );
  testRecord.set_state( state );
  testRecord.set_county( county );
  testRecord.set_longitude_latitude( longitude, latitude );

  cout << "Filled Record:";
  testRecord.display();
	
	 
	return 0;
}