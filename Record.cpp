//file Record.h

#include "Record.h"

Record::Record()
{
  isEmpty;
  zip_code;
  place_name;
  state;
  county;
  gridPoint;
}

void Record::display()
{
  //test commit
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
  return gridPoint.get_latitude();
}

float Record::get_longitude()
{
  return gridPoint.get_longitude();
}
