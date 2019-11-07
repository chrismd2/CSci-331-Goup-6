/**
@file
@author Christenson, Mark
*/
const bool DEBUG = false;

#include "Truncate.h"
#include <string>

Truncate::Truncate(){
    if (DEBUG)
    {
        cout << "Truncate object made";
    }
}
Truncate::Truncate(int _size){
    maxLength = _size;
}

string Truncate::truncatedString(string _string) {
    string newStr = _string;
    newStr.resize(maxLength);

    return newStr;
}

string Truncate::modifyString(string & _originalStr) {
    _originalStr.resize(maxLength);

    return _originalStr;
}
