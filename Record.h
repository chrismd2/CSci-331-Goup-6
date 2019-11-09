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

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include "grid.cpp"
using namespace std;

class Record
{ 
    // Access specifier 
    public: 
    /**  Default constructor
         Preconditions:   None
         Postconditions:  A blank record object is created*/
    Record(); 
    /**  Constructor with a grid object
         Preconditions:   Grid object is provided
         Postconditions:  A filled record object is created with a grid object*/
    Record(string, string, string, string, Grid);
    /**  Constructor with a grid as lat/long
         Preconditions:   Grid is provided in the order latitude, longitude
         Postconditions:  A filled record object is created with a grid object*/
    Record(string, string, string, string, string, string);
    /**  Empty display function
         Preconditions:   None
         Postconditions:  Record object will display all of its own data*/
    void display();
    /**  Empty display function
         Preconditions:   None
         Postconditions:  Record object will display all of its own data*/
    void display(string); //This might benefit from calling get_field
    /**  Specified display function
         Preconditions:   Provided string must match the name of a field in the record
         Postconditions:  Record object will display the specified field from its own data*/
    string get_field(string); //This should have a switch statement
    /**  Specified get_field function
         Preconditions:   Provided string must match the name of a field in the record
         Postconditions:  Record object will return the specified field from its own data*/
    
    /**  Specified set function
         Preconditions: First provided string must match the name of a field in the record
                        Second provided string must be the appropriate length for the field
         Postconditions:  Record object will display the specified field from its own data*/
    void set_field(string, string);

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
    //helper functions
    float string_to_float(string);
}; 

#include "Record.cpp"

#endif