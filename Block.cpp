// @Block.cpp

#include "Block.h"
#include "fstream"

using namespace std;

/** Default constructor
 *  @pre None
 *  @post A blank Block object is created
 */
Block::Block()
{
  if(DEBUG) {cout << "Made an empty block.\n";}
}

/** Constructor with record numbers
 *  @pre None
 *  @post A blank Block object is created
 */
Block::Block(string _blockData)
{
    if(DEBUG) {cout << "Making a block with \"" << _blockData << "\".\n";}
}
Block::moveReadWriteHead(fstream file, streampos pos){
    file.seekp(pos);
    file.seekg(pos);
}

Block::write(fstream file)
{
	if(DEBUG) {cout << "Writing block number " << relativeBlockNumber << " to a file.\n";}

	moveReadWriteHead(relativeBlockNumber * BLOCKLENGTH);

	file << relativeBlockNumber;
	if(DEBUG){cout << relativeBlockNumber;}
	for(int i = 0;  i < recordCount; i++){
        string record = records[i];
        for(int i = record.length() - ZIPLENGTH; i > 0; i--){
            file << " ";
            if(DEBUG){cout << " ";}
        }

        file << record;
        if(DEBUG){cout << record;}
	}
}

bool Block::search(string pKey)
{
	if(DEBUG) {cout << "Searching for " << pkey << " in this block\n";}

	Record[ RECORDSPERBLOCK ] block; //allocate
	this -> getRecords( block );


}

Block::getNextBlock()
{


	if(DEBUG) {cout << ".\n";}
}

Block::deleteRecord(string pKey)
{
	if(DEBUG) {cout << "Deleting record " << pkey << " in block "<< relativeBlockNumber <<"\n";}

	unsigned long long index = 1;

	while(!search(pKey) && index < RECORDSPERBLOCK){
        index++;
	}

	while(index < RECORDSPERBLOCK)
    {
        records[index] = records[index+1];
        index++;
	}

    records[index] = 0;
}

Block::addRecord(string pKey)
{


if(DEBUG) {cout << ".\n";}
}

Block::getRecords(Record[] block)
{


if(DEBUG) {cout << ".\n";}
}

Block::moveAroundRecord(string pKey)
{


if(DEBUG) {cout << ".\n";}
}
