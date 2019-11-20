/**---------------------------------------------------------------------------
// @SequenceSet.h
// Class Block (Contains Records)
// @author Tyler Lahr and Sushan Tiwari  (Additional comments by Mark Christenson)
//---------------------------------------------------------------------------
// Block class:  Used by Sequence Set Class
//   includes additional features:
//   --
//   --
//   --
//   --
//   --
//---------------------------------------------------------------------------**/

#ifndef SEQUENCESET_H
#define SEQUENCESET_H

#include <iostream>
#include <string>
#include <fstream>
#include "Block.h"
using namespace std;

class SequenceSet
{
private:
    unsigned long long headerLength(string);
public:
   /**  makeRecordOffsets
    *    Preconditions:     File must have fixed length primary keys
    *                       equal to the "ziplength" in globals.cpp
    *    Postconditions:    An index file is made for the provided file name
    */
   void makeRecordOffsets(string fileName);


   /**  getRecordCount
    *    Preconditions:     Files must be available and the header in data
    *                       file must contain "Records:"
    *    Postconditions:    RecordCount is returned
    */
    unsigned int getRecordCount();

   /**  test
    *    Preconditions:     This is not a permanent function
    *    Postconditions:    See precondition
    */
    int test();
};

#include "SequenceSet.cpp"

#endif
