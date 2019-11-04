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

void Grid::setLatitude(float _latitude){
	latitude = _latitude;
}

void Grid::setLongitude(float _longitude)
{
longitude = _longitude;  
}


float Grid::getLatitude(){
  return latitude;
}

float Grid::getLongitude(){
		return longitude;
}

float Grid::getDistance(Grid _grid){
  float distance = pow(latitude - _grid.getLatitude(),2) + pow(longitude - _grid.getLongitude(),2);
  distance = sqrt(distance);
  return distance;
}
