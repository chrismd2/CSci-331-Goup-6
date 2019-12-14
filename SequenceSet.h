/**-------------------------------------------------------------------------------------------------
 * @SequenceSet.h
 * Class Sequence set
 * @author Tyler Lahr, Seth Pomahatch, Sushan Tiwari, Ryan Sweeney, Mark Christenson
 *--------------------------------------------------------------------------------------------------
 * Block class:  Used by Sequence Set Class
 *   includes additional features:
 *   --Make record offsets
 *   --Fill Index
 *   --fillRecordBlock
 *   --extremeCoord
 *   --deleteRecord
 *   --addRecord
 *   --rewriteSSClass
 *   --writeToTxt
 ---------------------------------------------------------------------------------------------------
 */

#ifndef SEQUENCESET_H
#define SEQUENCESET_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "Block.h"
#include "Record.h"

using namespace std;

/*
//new material for b+tree
struct node{
  Block * ABlock;
  Block * BBlock;
  Block * TBlock;
  node * LNode;
  node * MNode;
  node * RNode;
  node * TNode;
  bool isLeaf;

  node(){
    if(DEBUG){cout << "node constructor called\n";}

    ABlock = new Block;
    BBlock = new Block;
    TBlock = new Block;

    LNode = nullptr;
    MNode = nullptr;
    RNode = nullptr;
    if(DEBUG){cout << "node's nodes set to nullptr\n";}
    isLeaf = true;
  }//end node constructor

  Block * insert(Block * newData ){
    bool testing = true;
    if(testing){cout << "node insert called\n";}
    Block * r = new Block;
    if(testing){cout << "isLeaf: " << isLeaf << endl;}
    r->setRBN(0);
    if(isLeaf){ //if the node is a leaf node
      if(testing){cout << "Node is a leaf\n";}
      if(ABlock != nullptr && ABlock->getRBN() > 0){ //if the first block in the node is already filled 
        if(BBlock != nullptr && BBlock->getRBN() > 0){ //if the second block in the node is already filled
          if(testing){cout << "filling temp data\n";}
          TBlock = newData; //then fill the third block in the node
        }
        else{
          if(testing){cout << "filling 2nd data\n";}
          BBlock = newData; //then fill the second block in the node
        }
      }
      else{
        if(testing){cout << "filling 1st data\n";}
        ABlock = newData; //then fill the first block in the node
      }
    }
    if(!isLeaf){
      if(BBlock != nullptr && BBlock->getRBN() < newData->getRBN()){
        cout << "in not leaf, BBlock not null\n";
        RNode = new node;
        TBlock = RNode->insert(newData);
      }
      else if(BBlock == nullptr){
        cout << "in not leaf, BBlock is null\n";
        BBlock = new Block;
        TBlock = MNode->insert(newData);
        ///this is where the internal node needs to split if tnode is not 0
        if(TBlock != nullptr && TBlock->getRBN() > 0){
          RNode = MNode;
          BBlock = RNode->ABlock;

          MNode->BBlock = nullptr;
          MNode->ABlock = TBlock;

          if(testing){cout << "internal node fixed\n";}

          if(testing){displayNode();}
        }
      }
    }
    
    //end of the newdata is > old data case, unsorted data will require other cases, but our linked list is sorted

    if(testing){cout << "Retrieving temp RBN\n";}
    if(TBlock != nullptr && TBlock->getRBN() > 0){
      if(testing){cout << "TBlock RBN > 0\n";}
      Block * t = new Block;
      t->setRBN(0);
      r = ABlock;
      ABlock = BBlock;
      BBlock = TBlock;
      TBlock = t;
      if(testing){cout << "End of pointer train\n";}
      
      //The data is carted left and up but not the node pointers
      //This node should become the right and the parent should handle the left

    }

    if(testing){displayNode();}

    return r;
  }//end of node insert

  void displayNode(){
    bool testing = true;
    if(testing){cout << "Displaying node\n";}
    if(TBlock != nullptr){cout  << "\t\t" << "Temp: "<< TBlock->getRBN() << "\n\t";}
    if(ABlock != nullptr){cout  << ABlock->getRBN();}
    if(BBlock != nullptr){cout  << " " << BBlock->getRBN();}
    cout << "\n";
    if(LNode != nullptr){
      if(LNode->ABlock != nullptr){cout  << (LNode->ABlock)->getRBN() << " ";}
      if(LNode->BBlock){cout  << (LNode->BBlock)->getRBN() << "\t";}
    }
    if(MNode != nullptr){
      if(MNode->ABlock != nullptr){cout << (MNode->ABlock)->getRBN() << " ";}
      if(MNode->BBlock != nullptr){cout  << (MNode->BBlock)->getRBN() << "\t";}
    }
    if(RNode != nullptr){
      if(RNode->ABlock != nullptr){cout << (RNode->ABlock)->getRBN();}
      if(RNode->BBlock != nullptr){cout << " " << (RNode->BBlock)->getRBN();}
    }
    cout << endl;
  }// end of displayNode

  void ___WriteTreeFile(){
    ofstream treeFile;
    treeFile.open("Tree.txt", ios_base::app);
    treeFile << ABlock->getRBN() << "\t" << BBlock->getRBN();
    string str;
    if(LNode != nullptr){
      str = "\nWriting a left node\n";
      treeFile << str;
      treeFile.close();
      LNode->___WriteTreeFile();
      treeFile.open("Tree.txt", ios_base::app);
    }
    if(MNode != nullptr){
      str = "\nWriting a mid node\n";
      treeFile << str;
      treeFile.close();
      MNode->___WriteTreeFile();
      treeFile.open("Tree.txt", ios_base::app);
    }
    if(RNode != nullptr){
      str = "\nWriting a right node\n";
      treeFile << str;
      treeFile.close();
      RNode->___WriteTreeFile();
      treeFile.open("Tree.txt", ios_base::app);
    }
    str = "\nNode Completed\n\n";
    treeFile << str;
    treeFile.close();
  }//end of recursive write

  void WriteTreeFile(){
    ofstream treeFile;
    treeFile.open("Tree.txt");
    treeFile << "Tree Data\n";
    treeFile.close();
    treeFile.open("Tree.txt", ios_base::app);
    if(ABlock!=nullptr){treeFile << ABlock->getRBN();}
    if(BBlock!=nullptr){treeFile << "\t" << BBlock->getRBN();}
     
    string str;
    if(LNode != nullptr){
      str = "\nWriting a left node\n";
      treeFile << str;
      treeFile.close();
      LNode->___WriteTreeFile();
      treeFile.open("Tree.txt", ios_base::app);
    }
    if(MNode != nullptr){
      str = "\nWriting a mid node\n";
      treeFile << str;
      treeFile.close();
      MNode->___WriteTreeFile();
      treeFile.open("Tree.txt", ios_base::app);
    }
    if(RNode != nullptr){
      str = "\nWriting a right node\n";
      treeFile << str;
      treeFile.close();
      RNode->___WriteTreeFile();
      treeFile.open("Tree.txt", ios_base::app);
    }
    str = "\nNode Completed\n\n";
    treeFile << str;
    treeFile.close();
  }
};//end of node struct

struct handler{
  bool testing = true;
  node * root;
  Block * keyBlock;
  handler(){
    if(DEBUG){cout << "handler constructor called\n";}
    root = new node;
    keyBlock = new Block;
  }//end handler constructor
  void insert(Block * newData){
    if(testing){cout << "handler insert called\n";}
    keyBlock = root->insert(newData);//this is where we get the r value from a root node
    if(keyBlock != nullptr && keyBlock->getRBN() > 0){
      //Missing a case in this if Statement
      //The first split is fine, but it needs to work into RNode after
      if(testing){cout << "keyBlock > 0, root needs to split\n";}
      node * ANode = new node;
      node * BNode = new node;

      ANode->LNode = root->LNode;
      ANode->ABlock = keyBlock;
      if(testing){cout << "ANode filled\n";}

      BNode->LNode = root->MNode;
      BNode->ABlock = root->ABlock;
      BNode->MNode = root->RNode;
      BNode->BBlock = root->BBlock;
      if(testing){cout << "BNode filled\n";}

      root->LNode = ANode;
      root->MNode = BNode;
      root->BBlock = nullptr;
      root->TBlock = nullptr;
      root->isLeaf = false;
      if(testing){cout << "root fixed\n";}

      if(testing){root->displayNode();}
    }
  }//end handler insert
  void test(){
    cout << "testing\n" ;
    if(false){
      cout << (root->ABlock)->getRBN() << endl;//AND THIS
      cout << (root->BBlock)->getRBN() << endl;
      root->ABlock = root->BBlock;
      root->BBlock = new Block;
      cout << (root->ABlock)->getRBN() << endl;//AND THIS
    }

    ofstream treeFile;
    treeFile.open("Tree.txt");

    if(false){
      bool testingFile = false;
      node * currentNode = root;
      while(currentNode != nullptr){
        treeFile << (currentNode->ABlock)->getRBN();
        treeFile << "\t";
        treeFile << (currentNode->BBlock)->getRBN();
        treeFile << "\t";
        treeFile << (currentNode->TBlock)->getRBN();
        treeFile << "\n";
        currentNode = currentNode->LNode;
      }
    }

    treeFile.close();
    root->WriteTreeFile();
  }// end of Test
};//end of handler struct */

class SequenceSet
{
private:
    string SSFileName = "Sequence_Set.txt";	/**< Variable for Sequence_set.txt*/
    string recordAvailListFileName = "availRecordList.txt";	/**< Variable for availRecordList.txt*/
    unsigned long long headerLength(string);	/**< Gets length of header*/
    unsigned long long blockCount;	/**< Holds number of blocks*/
    unsigned int recordCount;	/**< Holds number of records */
    //unsigned int indexArray[getRecordCount()][2];
    vector<unsigned int>pKeyIndex;	/**< Primary key zipcode to be used with offsetIndex*/
    vector<unsigned int>offsetIndex;	/**< Find a pKey position in pKeyIndex go to that 
                                         * position here to retrieve the offet for that 
                                         * record
																				 */
    vector<vector<string>>stateZips;    /**< States zipcodes*/
    vector<vector<string>>sKeyCounty;	/**< Secondary key for county*/
    vector<vector<string>>sKeyPlace;	/**< Secondary key for place (city)*/
    vector<Block*>blockAvailList;	/**< Stack of empty blocks*/
    Record recordBlock[RECORDSPERBLOCK];  /**< This is where the block is loaded into memory*/
    Block * headBlock = new Block;	/**< Start of the block list*/

    ///New Material for B+Tree
    bool isLessThan(Block*, Block*);
    bool isGreaterThan(Block*, Block*);
    handler tree;

    /**A tree builder
		 *	@pre		Linked list must be sorted by RBN and tree is empty
		 *	@post		A B+tree that points at the blocks in the linked list is built
		 */    
    void treeBuilder();

    /**Add block state key
		 *	@pre		Block ID is less than block count(ie the block is in the block chain)
		 *	@post		A block in the chain is added to the state keys
		 */
    void addBlockStateKey(unsigned long long blockID);

    /**Add block state key builder
		 *	@pre		None
		 *	@post		Builds the secondary index for states
		 */
    void sKeyStateBuilder();
    

public:
    //public new material for b+tree
    Block * TreeSearch(string);
    
		/** Default constructor
		* @pre File with a name that matches DATAFILENAME in Header.cpp must exist
    *      and it must contain a line equal to HEADERENDSTRING in Header.cpp
		* @post Sequence Set Class is made
		*/
    SequenceSet();

    /**  Make record offsets
    *    @pre		File must have fixed length primary keys
    *         	equal to the "ziplength" in globals.cpp
    *    @post  An index file is made for the provided file name
    */
    void makeRecordOffsets(string fileName);

    /**  Fill Index
    *    @pre		"RecordOffsets.txt" file must exist
    *            makeRecordOffsets can be ran to be sure of this
    *    @post   The index is made and stored here, in the Sequence Set
    */
    void fillIndex();

    /**  Fill record block
    *    @pre		blockID must be less than the block count
    *    @post	Block is loaded into a record block
    */
    void fillRecordBlock(unsigned long long blockID);

    /**  Write blocks
    *    @pre		None
    *    @post	All blocks are called to run their write function
    */
    void writeBlocks();

    /**  Fill record
    *    @pre		Record string must follow parameter conventions
    *           Record string must be complete, call fetch if needed
    *    @post	A record string is loaded into a record object
    */
    Record fillRecord(string RecordString);

    /**  Get record count
    *    @pre		Files must be available and the header in data
    *           file must contain "Records:"
    *    @post	RecordCount is returned
    */
    unsigned int getRecordCount();

    /**  Fetch string
    *    @pre		None
    *    @post	returns the whole record as a string
    */
    string fetch(string pKey);

    /**  Fetch unsigned int
    *    @pre		None
    *    @post	returns the whole record as a string
    */
    string fetch(unsigned int pKey);

    /** Extreme coordinate
    *	@pre	State of type string and Direction of type Char (N, E, S, W)
    *       State code must be in the list of states or the last state in list is used
    *	@post Returns the zipcode containing the most extreme point of said direction
    */
    string extremeCoord(string, char);

		/** Delete record
		 * @pre A primary key (zipcode)
		 * @post Deletes record with given zipcode
		 */
    bool deleteRecord(int pKey);
		
		/** Add record
		 * @pre A record object
		 * @post Adds the record
		 */
    void addRecord(Record record);
    void rewriteSSFile();/**< */

		/** WriteToTxt
		 * @pre Inputs should match source length requirements
		 * @post Writes the record to the data file (us_postal_codes.txt)
		 */
    void writeToTxt(Record, string, string);

		/** Searches block for record by primary key
		* @pre Primary key
		* @post Returns true if found otherwise returns false
		*/
    int binarySearchSS(string x);
    
    /**
    * @pre None
    * @post Returns the various tester results
    */
    int test();
};

#include "SequenceSet.cpp"

#endif

