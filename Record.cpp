//file Record.h

#include "Record.h"

Record::Record()
{
  zip_code = "";
  place_name = "";
  state = "";
  county = "";
  this -> set_longitude_latitude( 0.0, 0.0 );
}

Record::Record(string _zip_code, string _place_name, string _state, string _county, Grid _gridPoint)
{
  zip_code = _zip_code;
  place_name = _place_name;
  state = _state;
  county = _county;
  this -> set_grid_point( _gridPoint );
}

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

void Record::display()
{
    cout << endl
       << "Zipcode: " << get_zip_code()
       << " Place: " << get_place_name()
       << " State: " << get_state()
       << " County: " << get_county()
       << " Longitude: " << get_longitude()
       << " Latitude: " << get_latitude()
       << endl;
}

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
    returnString = gridPoint.getLatitude() + " " + gridPoint.getLongitude();
  else if(field == "LAT" || field == "LATITUDE")
    returnString = gridPoint.getLatitude();
  else if(field == "LONG" || field == "LONGITUDE")
    returnString = gridPoint.getLongitude();
  else
    returnString = "ERROR" + endl;
  
  return returnString;
}

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
