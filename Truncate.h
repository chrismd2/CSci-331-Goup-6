#ifndef TRUNCATE_H
#define TRUNCATE_H
#include <string>

using namespace std;

class Truncate {
public:
    /**  Default constructor
         Preconditions:   None
         Postconditions:  A truncate object will be created with a size of default for max length*/
    Truncate();
    /**  Default constructor
         Preconditions:   Input must be an int
         Postconditions:  A truncate object will be created with a size of the input for max length*/
    Truncate(int);
    /**  String modifier
         Preconditions:   Input must be a string
         Postconditions:  The truncate object will truncate the input string and return it*/
    string modifyString(string&);
    /**  Temporary string modifier
         Preconditions:   Input must be a string
         Postconditions:  The truncate object will copy the input string and return the truncated string
                            without modifying the original*/
    string truncatedString(string);
private:
    int maxLength = 10;
};

#include "Truncate.cpp"

#endif
