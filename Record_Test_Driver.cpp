//g++ -std=c++11  -o record_test Record_Test_Driver

#include "Record.cpp"
#include<iostream>
#include<string>

using namespace std;


int main()
{
  //test default constructor
	Record testRecord;

  testRecord.display();
	
	 
	return 0;
}