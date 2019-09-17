/**
@file
@author Christenson, Mark
*/

#include "Truncate.h"
#include <string>

Truncate::Truncate(){
    maxLength = maxLength;
}
Truncate::Truncate(int _size = 6){
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
