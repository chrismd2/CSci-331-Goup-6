/**---------------------------------------------------------------------------
 * @Record.h
 * Class Record (Contains information about individual zipcodes)
 * @author Tyler Lahr, Ryan Sweeney, and Seth Pomahatch
 * (Additional comments by Mark Christenson)
 *---------------------------------------------------------------------------
 * Record class:  Used by Sequence Set Class
 *   includes additional features:
 *   -- Display the whole record it represents
 *   -- Display a field with in the record
 *   -- Return a field as a string
 *   -- Return the latitude
 *   -- Return the longitude
 *---------------------------------------------------------------------------
 */

#ifndef RECORD_H
#define RECORD_H

#include <iostream>
#include <string>
#include "grid.cpp"
using namespace std;

class Record
{ 
  public: 
		/** Default constructor
 	 	 *  @pre None
 	 	 *  @post A blank record object is created
 	 	 */
  	Record(); 

		/** Constructor with a grid object
 		 *  @pre Grid object is provided
 		 *  @post A filled record object is created with a grid object
 		 */
    Record(string, string, string, string, Grid);

		/** Constructor that also takes latitude, and longitude
 		 *  @pre String is provided in order of latitude, longitude
 		 *  @post A filled record object is created with a latitude and longitude
 		 */
    Record(string, string, string, string, string, string);

		/** Displays all fields of the record
 		 *  @pre None
 		 *  @post Record object will display all of its own data
 		 */
    void display();

		/** Displays the specified field
 		 *  @pre None
 		 *  @post Record object will display specified field
 		 */
    void display(string); //This might benefit from calling get_field

		/** Get the desired field in the record to display a field from its data
 		 *  @pre Provided string must match the name of a field in the record
 		 *  @post Record object will display the specified field from its own data
 		 */
    string get_field(string); //This should have a switch statement

		/** 
 		 *  @pre First provided string must match the name of a field in the record
 		 *  Second provided string must be the appropriate length for the field
 		 *  @post Record object will display the specified field from its own data
 		 */
    void set_field(string, string);

		/** Sets the latitude and longitude
 		 *  @pre Provide longitude and latitude as floats
 		 *  @post Set the latitude and longitude of the record
 		 */
    void set_longitude_latitude(float, float);
		
		/** Sets the Latitude and longitude based on a grid point
 		 *  @pre A grid point of type Grid
 		 *  @post Sets latitude and longitude based on grid point recieved
 		 */
    void set_grid_point(Grid);

  private:
    bool isEmpty; /**<  Checks if empty */
    string zip_code; /**< Zip code */
    string place_name; /**< City */
    string state;	/**< State */
    string county; /**< Country */
    Grid gridPoint;	/**< Latitude and longitude */
		
    /** Turn a string into a float
 		 *  @pre A string is provided
 		 *  @post returns the string characters as float
 		 */
    float string_to_float(string);
}; 

#include "Record.cpp"

#endif