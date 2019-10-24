#include <iostream>
#include "Truncate.h"
#include <string>

using namespace std;

void truncateTester(); /**<Tests the Truncate Class*/

int main(){
  cout << "Hello World"; //Hacked
  //new stuff

  truncateTester();
}

void truncateTester(){
  Truncate t;
  Truncate t2(5);
  string str = "123456789AB";

  cout << endl << "The String is " << str;
  cout << endl << "The String AS it is modified is " << t.modifyString(str);
  cout << endl << "The String IF it was modified is " << t2.truncatedString(str);
  cout << endl << "The String is " << str;
}
