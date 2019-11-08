/**---------------------------------------------------------------------------
// @Record.cpp
// Class Record (Contains information about individual zipcodes)
// @author Tyler Lahr and Ryan Sweeney  (Additional comments by Mark Christenson)
//---------------------------------------------------------------------------
// Record class:  Used by Sequence Set Class
//   includes additional features:
//   -- Display the whole record it represents
//   -- Display a field with in the record
//   -- Return a field as a string
//   -- Return the latitude
//   -- Return the longitude
//---------------------------------------------------------------------------**/

#include "Record.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/**  Default constructor
     Preconditions:   None
     Postconditions:  A blank record object is created*/
Record::Record()
{
  zip_code = "";
  place_name = "";
  state = "";
  county = "";
  this -> set_longitude_latitude( 0.0, 0.0 );
}

/**  Constructor with a grid object
     Preconditions:   Grid object is provided
     Postconditions:  A filled record object is created with a grid object*/
Record::Record(string _zip_code, string _place_name, string _state, string _county, Grid _gridPoint)
{
  zip_code = _zip_code;
  place_name = _place_name;
  state = _state;
  county = _county;
  this -> set_grid_point( _gridPoint );
}

/**  Constructor with a grid as lat/long
     Preconditions:   Grid is provided in the order latitude, longitude
     Postconditions:  A filled record object is created with a grid object*/
Record::Record(string _zip_code, string _place_name, string _state, string _county, string latitude, string longitude)
{
  float lon = string_to_float( longitude );
  float lat = string_to_float( latitude );

  zip_code = _zip_code;
  place_name = _place_name;
  state = _state;
  county = _county;
  this -> set_longitude_latitude( lon, lat );
}

/**  Empty display function
     Preconditions:   None
     Postconditions:  Record object will display all of its own data*/
void Record::display()
{
    cout << endl
       << "Zipcode: " << get_field("Zipcode")
       << " Place: " << get_field("Place")
       << " State: " << get_field("State")
       << " County: " << get_field("County")
       << " Longitude: " << get_field("Longitude")
       << " Latitude: " << get_field("Latitude")
       << endl;
}

/**  Empty display function
     Preconditions:   None
     Postconditions:  Record object will display all of its own data*/
void Record::display(string field)
{
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }
  //The following if else-if statements replace the case statement variation
  if(field=="Z" || field=="ZIP")
    cout << zip_code << endl;
  else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
    cout << place_name << endl;
  else if(field=="STATE")
    cout << state << endl;
  else if(field=="COUNTY")
    cout << county << endl;
  else if(field=="G" || field=="GRID")
    cout << gridPoint.getLatitude() << " " << gridPoint.getLongitude() << endl;
  else if(field == "LAT" || field == "LATITUDE")
    cout << gridPoint.getLatitude() << endl;
  else if(field == "LONG" || field == "LONGITUDE")
    cout << gridPoint.getLongitude() << endl;
  else
    cout << "Invalid field has been entered." << endl;
}

/**  Specified display function
     Preconditions:   Provided string must match the name of a field in the record
     Postconditions:  Record object will display the specified field from its own data*/
string Record::get_field(string field)
{
  string returnString;
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }
  //The following if else-if statements replace the case statement variation
  if(field=="Z" || field=="ZIP")
    returnString = zip_code;
  else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
    returnString = place_name;
  else if(field=="STATE")
    returnString = state;
  else if(field=="COUNTY")
    returnString = county;
  else if(field=="G" || field=="GRID")
    returnString = itoa(gridPoint.getLatitude()) + " " + itoa(gridPoint.getLongitude());
  else if(field == "LAT" || field == "LATITUDE")
    returnString = itoa(gridPoint.getLatitude());
  else if(field == "LONG" || field == "LONGITUDE")
    returnString = itoa(gridPoint.getLongitude());
  else
    returnString = "ERROR" + endl;

  return returnString;
}

/**  Specified get_field function
     Preconditions:   Provided string must match the name of a field in the record
     Postconditions:  Record object will return the specified field from its own data*/

/**  Specified set function
     Preconditions: First provided string must match the name of a field in the record
                    Second provided string must be the appropriate length for the field
     Postconditions:  Record object will display the specified field from its own data*/
void Record::set_field(string field, string data)
{
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }
  for(int i = 0; data[i] != NULL; i++){
      data[i] = toupper(data[i]);
  }

  //The following if else-if statements replace the case statement variation
  if(field=="Z" || field=="ZIP")
    zip_code = data;
  else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
    place_name = data;
  else if(field=="STATE")
    state = data;
  else if(field=="COUNTY")
    county = data;
  else if(field=="G" || field=="GRID")
    cout << "grid setter needs to implemented";
  else if(field == "LAT" || field == "LATITUDE")
    gridPoint.setLatitude(data);
  else if(field == "LONG" || field == "LONGITUDE")
    gridPoint.setLongitude(data);
  else
    cout << "ERROR" << endl;
}

void Record::set_longitude_latitude(float longitude, float latitude)
{
  gridPoint.setLatitude( latitude );
  gridPoint.setLongitude( longitude );
}

void Record::set_grid_point(Grid _gridPoint)
{
  gridPoint.setLatitude( _gridPoint.getLatitude() );
  gridPoint.setLongitude ( _gridPoint.getLongitude() );
}

//helper functions

float Record::string_to_float(string str)
{
  size_t size;
  float float_value = stof( str, &size );

  return float_value;
}
