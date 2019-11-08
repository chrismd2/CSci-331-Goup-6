/**
@file
@author Christenson, Mark
*/

//#include "Truncate.h"
#include <string>
#include "Header.cpp"

Truncate::Truncate(){
    if (true)
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
