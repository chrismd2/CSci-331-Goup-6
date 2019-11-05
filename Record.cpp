//file Record.h

#include "Record.h"

Record::Record()
{
  isEmpty = 1;
  zip_code = "";
  place_name = "";
  state = "";
  county = "";
  gridPoint = Grid();
}

void Record::display()
{
    cout << "Zipcode: " << get_zip_code()
       << " Place: " << get_place_name()
       << " State: " << get_state()
       << " County: " << get_county()
       << " Longitude: " << get_longitude()
       << " Latitude: " << get_latitude();
}

void Record::display(string field)
{
  for(int i = 0; field[i] != NULL; i++){
      field[i] = toupper(field[i]);
  }
  switch(field){
    case "Z":
    case "ZIP":
      cout << zip_code << endl;
      break;
    case "CITY":
    case "P":
    case "PLACE_NAME":
      cout << place_name << endl;
      break;
    case "STATE":
      cout << state << endl;
      break;
    case "COUNTY":
      cout << county << endl;
      break;
    case "G":
    case "GRID":
      cout << gridPoint.getLatitude << " " << gridPoint.getLongitude << endl;
      break;
  }
}

string Record::get_zip_code()
{
  return zip_code;
}

string Record::get_place_name()
{
  return place_name;
}

string Record::get_state()
{
  return state;
}

string Record::get_county()
{
  return county;
}

float Record::get_latitude()
{
  return gridPoint.getLatitude();
}

float Record::get_longitude()
{
  return gridPoint.getLongitude();
}

Grid Record::get_grid_point()
{
  return gridPoint;
}

void Record::set_zip_code(string _zip_code)
{
  zip_code = _zip_code;
}

void Record::set_place_name(string _place_name)
{
  place_name = _place_name;
}

void Record::set_state(string _state)
{
  state = _state;
}

void Record::set_county(string _county)
{
  county = _county;
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
