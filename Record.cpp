/**---------------------------------------------------------------------------
 * @Record.cpp
 * Class Record (Contains information about individual zipcodes)
 * @author Tyler Lahr, Ryan Sweeney, and Seth Pomahatch
 * (Additional comments by Mark Christenson)
 *----------------------------------------------------------------------------
 * Record class:  Used by Sequence Set Class
 *   includes additional features:
 *   -- Display the whole record it represents
 *   -- Display a field within the record
 *   -- Return a field as a string
 *   -- Return the latitude
 *   -- Return the longitude
 *----------------------------------------------------------------------------
 */

#include "Record.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

Record::Record()
{
  zip_code = "";
  place_name = "";
  state = "";
  county = "";
  this -> set_longitude_latitude( 0.0, 0.0 );
  if(DEBUG) {cout << "Made an empty record.\n";}
}

Record::Record(string _zip_code, string _place_name, string _state, string _county, Grid _gridPoint)
{
  zip_code = _zip_code;
  place_name = _place_name;
  state = _state;
  county = _county;
  this -> set_grid_point( _gridPoint );
  if(DEBUG) {cout << "Made a filled record using a gridPoint.\n";}
}

Record::Record(string _zip_code, string _place_name, string _state, string _county, string latitude, string longitude)
{
  float lon;
  float lat;

  try{
    lon = string_to_float( longitude );
  }
  catch(...){
    cout << "ERROR SETTING LONGITUDE, SETTING IT TO 0\n";
    lon = 0;
  }

  try{
    lat = string_to_float( latitude );
  }
  catch(...){
    cout << "ERROR SETTING LATITUDE IN " << zip_code << ", SETTING IT TO 0\n";
    lat = 0;
  }

  zip_code = _zip_code;
  place_name = _place_name;
  state = _state;
  county = _county;
  this -> set_longitude_latitude( lon, lat );
  if(DEBUG) {cout << "Made a filled record using string lat/longs.\n";}
}

void Record::display()
{
    if(DEBUG) {cout << "Displaying the whole record from the record.\n";}
    cout << endl
       << "Zipcode:\t" << get_field("Zip")
       << "\nPlace:\t\t" << get_field("City")
       << "\nState:\t\t" << get_field("State")
       << "\nCounty:\t\t" << get_field("County")
       << "\nLongitude:\t" << get_field("Longitude")
       << "\nLatitude:\t" << get_field("Latitude")
       << endl;
}

void Record::display(string field)
{
  if(DEBUG) {cout << "Displaying the "<< field <<" portion of the record.\t";}
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }

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

string Record::get_field(string field)
{
  if(DEBUG) {cout << "Retrieving the "<< field <<" portion of the record.\t";}
  string returnString;
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }

  if(field=="Z" || field=="ZIP")
    returnString = zip_code;
  else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
    returnString = place_name;
  else if(field=="STATE")
    returnString = state;
  else if(field=="COUNTY")
    returnString = county;
  else if(field=="G" || field=="GRID")
    returnString = to_string(gridPoint.getLatitude()) + " " + to_string(gridPoint.getLongitude());
  else if(field == "LAT" || field == "LATITUDE")
    returnString = to_string(gridPoint.getLatitude());
  else if(field == "LONG" || field == "LONGITUDE")
    returnString = to_string(gridPoint.getLongitude());
  else
    returnString = "ERROR";

  return returnString;
}

void Record::set_field(string field, string data)
{
  if(DEBUG) {cout << "Setting the "<< field <<" portion of the record from "<< get_field(field) << " to"<< data <<".\n";}
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }

  for(int i = 0; data[i] != NULL; i++){
      data[i] = toupper(data[i]);
  }
  
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
  float float_value = stof(str, &size);

  return float_value;
}










// /**---------------------------------------------------------------------------
//  * @Record.cpp
//  * Class Record (Contains information about individual zipcodes)
//  * @author Tyler Lahr, Ryan Sweeney, and Seth Pomahatch
//  * (Additional comments by Mark Christenson)
//  *---------------------------------------------------------------------------
//  * Record class:  Used by Sequence Set Class
//  *   includes additional features:
//  *   -- Display the whole record it represents
//  *   -- Display a field with in the record
//  *   -- Return a field as a string
//  *   -- Return the latitude
//  *   -- Return the longitude
//  *---------------------------------------------------------------------------
//  */

// #include "Record.h"
// #include <stdio.h>
// #include <stdlib.h>
// using namespace std;
 
// Record::Record()
// {
//   zip_code = "";
//   place_name = "";
//   state = "";
//   county = "";
//   this -> set_longitude_latitude( 0.0, 0.0 );
//   if(DEBUG) {cout << "Made an empty record.\n";}
// }

// Record::Record(string _zip_code, string _place_name, string _state, string _county, Grid _gridPoint)
// {
//   zip_code = _zip_code;
//   place_name = _place_name;
//   state = _state;
//   county = _county;
//   this -> set_grid_point( _gridPoint );
//   if(DEBUG) {cout << "Made a filled record using a gridPoint.\n";}
// }

// Record::Record(string _zip_code, string _place_name, string _state, string _county, string latitude, string longitude)
// {
//   float lon = string_to_float( longitude );
//   float lat = string_to_float( latitude );

//   zip_code = _zip_code;
//   place_name = _place_name;
//   state = _state;
//   county = _county;
//   this -> set_longitude_latitude( lon, lat );
//   if(DEBUG) {cout << "Made a filled record using string lat/longs.\n";}
// }

// void Record::display()
// {
//   if(DEBUG) {cout << "Displaying the whole record from the record.\n";}
//   cout << endl
//     	 << "Zipcode: " << get_field("Zip")
//     	 << " Place: " << get_field("Place_name")
//        << " State: " << get_field("State")
//        << " County: " << get_field("County")
//        << " Longitude: " << get_field("Longitude")
//        << " Latitude: " << get_field("Latitude")
//        << endl;
// }

// void Record::display(string field)
// {
//   if(DEBUG) {cout << "Displaying the "<< field <<" portion of the record.\n";}
//   for(int i = 0; field[i] != NULL; i++){
//     field[i] = toupper(field[i]);
//   }

//   if(field=="Z" || field=="ZIP")
//     cout << zip_code << endl;
//   else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
//     cout << place_name << endl;
//   else if(field=="STATE")
//     cout << state << endl;
//   else if(field=="COUNTY")
//     cout << county << endl;
//   else if(field=="G" || field=="GRID")
//     cout << gridPoint.getLatitude() << " " << gridPoint.getLongitude() << endl;
//   else if(field == "LAT" || field == "LATITUDE")
//     cout << gridPoint.getLatitude() << endl;
//   else if(field == "LONG" || field == "LONGITUDE")
//     cout << gridPoint.getLongitude() << endl;
//   else
//     cout << "Invalid field has been entered." << endl;
// }

// string Record::get_field(string field)
// {
//   if(DEBUG) {cout << "Retrieving the "<< field <<" portion of the record.\n";}
//   string returnString;
//   for(int i = 0; field[i] != NULL; i++){
//     field[i] = toupper(field[i]);
//   }

//   if(field=="Z" || field=="ZIP")
//     returnString = zip_code;
//   else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
//     returnString = place_name;
//   else if(field=="STATE")
//     returnString = state;
//   else if(field=="COUNTY")
//     returnString = county;
//   else if(field=="G" || field=="GRID")
//     returnString = to_string(gridPoint.getLatitude()) + " " + to_string(gridPoint.getLongitude());
//   else if(field == "LAT" || field == "LATITUDE")
//     returnString = to_string(gridPoint.getLatitude());
//   else if(field == "LONG" || field == "LONGITUDE")
//     returnString = to_string(gridPoint.getLongitude());
//   else
//     returnString = "ERROR";

//   return returnString;
// }

// void Record::set_field(string field, string data)
// {
//   if(DEBUG) {cout << "Setting the "<< field <<" portion of the record from "<< get_field(field) << " to"<< data <<".\n";}
//   for(int i = 0; field[i] != NULL; i++){
//       field[i] = toupper(field[i]);
//   }

//   for(int i = 0; data[i] != NULL; i++){
//       data[i] = toupper(data[i]);
//   }
  
//   if(field=="Z" || field=="ZIP")
//     zip_code = data;
//   else if(field=="CITY" || field=="P" || field=="PLACE_NAME")
//     place_name = data;
//   else if(field=="STATE")
//     state = data;
//   else if(field=="COUNTY")
//     county = data;
//   else if(field=="G" || field=="GRID")
//     cout << "grid setter needs to implemented";
//   else if(field == "LAT" || field == "LATITUDE")
//     gridPoint.setLatitude(data);
//   else if(field == "LONG" || field == "LONGITUDE")
//     gridPoint.setLongitude(data);
//   else
//     cout << "ERROR" << endl;
// }

// void Record::set_longitude_latitude(float longitude, float latitude)
// {
//   gridPoint.setLatitude( latitude );
//   gridPoint.setLongitude( longitude );
// }

// void Record::set_grid_point(Grid _gridPoint)
// {
//   gridPoint.setLatitude( _gridPoint.getLatitude() );
//   gridPoint.setLongitude ( _gridPoint.getLongitude() );
// }

// float Record::string_to_float(string str)
// {
//   size_t size;
//   float float_value = stof(str, &size);

//   return float_value;
// }

// //   if gridPoint.setLatitude(data);
// //   else if(field == "LONG" || field == "LONGITUDE")
// //     gridPoint.setLongitude(data);
// //   else
// //     cout << "ERROR" << endl;
// // }

// void Record::set_longitude_latitude(float longitude, float latitude)
// {
//   gridPoint.setLatitude( latitude );
//   gridPoint.setLongitude( longitude );
// }

// void Record::set_grid_point(Grid _gridPoint)
// {
//   gridPoint.setLatitude( _gridPoint.getLatitude() );
//   gridPoint.setLongitude ( _gridPoint.getLongitude() );
// }

// float Record::string_to_float(string str)
// {
//   size_t size;
//   float float_value = stof(str, &size);

//   return float_value;
// }