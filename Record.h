/**---------------------------------------------------------------------------
// @Record.h
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

#include <iostream>
#include <string>
using namespace std;

class Record
{ 
    // Access specifier 
    public: 
    Record();
    Record(string _zip_code, string _place_name, string _state, string _county, Grid _gridPoint);
    Record(string _zip_code, string _place_name, string _state, string _county, string latitude, string longitude);
    void display();
    void display(string field); //This might benefit from calling get_field
    string get_field(string field); //This should have a switch statement
    /**/
    string get_zip_code();
    string get_place_name();
    string get_state();
    string get_county();
    /**/
    float get_latitude();
    float get_longitude();


    // Data Members 
    private:
    bool isEmpty;
    string zip_code;
    string place_name;
    string state;
    string county;
    Grid gridPoint;
  
}; 
