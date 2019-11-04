//file Record.h

#include <iostream>
#include <string>
using namespace std;

class Record
{ 
    // Access specifier 
    public: 
    Record();
    void display();
    void display(string field);
    string get_zip_code();
    string get_place_name();
    string get_state();
    string get_county();
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