/**---------------------------------------------------------------------------
// @Grid.cpp
// Class Grid (manages a zipcode's grid information)
// @author Seth Pomahatc and Sushan Tiwari  (Additional comments by Mark Christenson)
//---------------------------------------------------------------------------
// Grid class:  Used by Record Class
//   includes additional features:
//   -- Return the latitude
//   -- Return the longitude
//   -- Return distance to a provided grid from this grid
//---------------------------------------------------------------------------**/

#include <iostream>
#include <math.h>
const bool DEBUG = true;

using namespace std;
	

class Grid {
  private:
	float latitude;
	float longitude;

  public:
  Grid();
  Grid(float, float);
  void setLatitude(float);
  void setLongitude(float);
  float getLatitude();
	float getLongitude();
	float getDistance(Grid);
};

Grid::Grid(){
  latitude = 0;
  longitude = 0;
}

Grid::Grid(float _latitude, float _longitude){
	latitude = _latitude;
	longitude = _longitude;
}

void Grid::setLatitude(float _latitude){/**<setLatitude
// Set Latitude for this grid object
//   @pre _latitude must follow rules regarding floats
//   @post Sets latitude for grid object*/
	latitude = _latitude;
}

void Grid::setLongitude(float _longitude){/**<setLatitude
// Set Longitude for this grid object
//   @pre _longitude must follow rules regarding floats
//   @post Sets longitude for grid object*/
longitude = _longitude;  
}


float Grid::getLatitude(){/**<getLatitude
// Get Latitude for this grid object
//   @pre none
//   @post returns latitude for grid object as float*/
  return latitude;
}

float Grid::getLongitude(){/**<getLongitude
// Get Longitude for this grid object
//   @pre none
//   @post returns longitude for grid object as float*/
		return longitude;
}

float Grid::getDistance(Grid _grid){/**<getDistance
// Get Distance from this grid object to another grid object
//   @pre grid object must be provided
//   @post returns distance from this grid object to another grid object as float*/
  float distance = pow(latitude - _grid.getLatitude(),2) + pow(longitude - _grid.getLongitude(),2);
  distance = sqrt(distance);
  return distance;
}
