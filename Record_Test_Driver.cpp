//g++ -std=c++11  -o record_test Record_Test_Driver

#include "Record.cpp"
#include<iostream>
#include<string>

using namespace std;

enum Field
{
    Z,
    ZIP,
    CITY,
    P,
    PLACE_NAME,
    STATE,
    COUNTY,
    G,
    GRID
};

int main()
{
  //test default constructor
	Record testRecord;
  cout << "Default constructor record:";
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

  //test constructor 2
  string longitude_string = "74.25";
  string latitude_string = "79.72";

  Record testRecord2(zip, place, state, county, longitude_string, latitude_string);

  cout << "Constructor2 record (long/lat are strings):";
  testRecord2.display();
	
	//test constructor 3
  Grid grid_test(longitude, latitude);

  Record testRecord3(zip, place, state, county, grid_test);

  cout << "Constructor3 record (long/lat are gridPoint):";
  testRecord3.display();

  cout << endl << "check enum:";
  testRecord3.display(CITY);
  cout << "~expected: Little Falls" << endl;

  testRecord3.display(STATE);
  cout << "~expected: Minnesota" << endl;

	return 0;
}