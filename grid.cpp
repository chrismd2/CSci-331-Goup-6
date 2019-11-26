/**---------------------------------------------------------------------------
 * @Grid.cpp
 * Class Grid (manages a zipcode's grid information)
 * @author Seth Pomahatch, Ryan Sweeney, and Sushan Tiwari  (Additional 
 * comments by Mark Christenson)
 *---------------------------------------------------------------------------
 * Grid class:  Used by Record Class
 *   includes additional features:
 *   -- Return the latitude
 *   -- Return the longitude
 *   -- Return distance to a provided grid from this grid
 *---------------------------------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
using namespace std;
	
/** Grid class
 *  
 *  Variables for latitude and longitude, constructor for setting
 *  0 to both latitude and longitude (default constructor) and a
 *	constructor for setting latitude and longitude to input values.
 *
 *  Methods for setting and getting latitude and longitude and for
 *  getting the distance between two points.
 */
class Grid {
  private:
		float latitude; /**< Variable for latitude */
		float longitude; /**< Variable for longitude */

  public:
  	Grid();
  	Grid(float, float);
  	void setLatitude(float);
  	void setLongitude(float);
  	void setLatitude(string);
  	void setLongitude(string);
  	float getLatitude();
		float getLongitude();
		float getDistance(Grid);
};

/** Default constructor
 *  @pre none
 *  @post sets values for latitude and longitude to 0
 */
Grid::Grid(){
  latitude = 0;
  longitude = 0;
}

/** Constructor requiring both latitude and longitude
 *  @pre Values for latitude and longitude as float
 *  @post Sets values for latitude and longitude
 */
Grid::Grid(float _latitude, float _longitude){
	latitude = _latitude;
	longitude = _longitude;
}

/** Sets Latitude for this grid object
 *  @pre _latitude must follow rules regarding floats
 *  @post Sets latitude for grid object
 */
void Grid::setLatitude(float _latitude){
	latitude = _latitude;
}

/** Sets Latitude for this grid object
 *  @pre _latitude must follow rules regarding string to float
 *  @post Sets latitude for grid object
 */
void Grid::setLatitude(string _latitude){
	setLatitude(stof(_latitude));
}

/** Sets Longitude for this grid object
 *  @pre _longitude must follow rules regarding floats
 *  @post Sets longitude for grid object
 */
void Grid::setLongitude(float _longitude){
	longitude = _longitude;  
}

/** Sets Longitude for this grid object
 *  @pre _longitude must follow rules regarding string to float
 *  @post Sets longitude for grid object
 */
void Grid::setLongitude(string _longitude){
	setLongitude(stof(_longitude));  
}

/**  Gets Latitude for this grid object
 *   @pre none
 *   @post returns latitude for grid object as float
 */
float Grid::getLatitude(){
  return latitude;
}

/**  Gets Longitude for this grid object
 *   @pre none
 *   @post returns longitude for grid object as float
 */
float Grid::getLongitude(){
	return longitude;
}

/**  Gets Distance from this grid object to another grid object
 *   @pre grid object must be provided
 *   @post returns distance from this grid object to another grid object as float
 */
float Grid::getDistance(Grid _grid){
  float distance = pow(latitude - _grid.getLatitude(),2) + pow(longitude - _grid.getLongitude(),2);
  distance = sqrt(distance);
  return distance;
}
