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
#include "grid.cpp"
using namespace std;

class Record
{ 
    // Access specifier 
    public: 
    Record();
    Record(string _zip_code, string _place_name, string _state, string _county, Grid _gridPoint);
    Record(string _zip_code, string _place_name, string _state, string _county, string latitude, string longitude);
    void display();
    void display(string); //This might benefit from calling get_field
    string get_field(string); //This should have a switch statement
    /**/
    string get_zip_code();
    string get_place_name();
    string get_state();
    string get_county();
    /**/
    float get_latitude();
    float get_longitude();
    Grid get_grid_point();
    /**/
    void set_zip_code(string);
    void set_place_name(string);
    void set_state(string);
    void set_county(string);
    void set_longitude_latitude(float, float);
    void set_grid_point(Grid);

    // Data Members 
    private:
    bool isEmpty;
    string zip_code;
    string place_name;
    string state;
    string county;
    Grid gridPoint;
  
}; 
