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