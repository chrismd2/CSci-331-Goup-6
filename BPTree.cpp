#include <iostream>
#include <string>

using namespace std;

struct node{
  bool testing = false;
  node * LNode; /**< Left Node*/
  node * MNode;	/**< Middle Node*/
  node * RNode;	/**< Right Node*/
  node * TNode;	/**< temporary Node*/
  int AData;		/**< Values less than this go left, values grater than this but less than B go middle*/
  int BData;		/**< Values greater than this go right, values less than this but greater than A go middle*/
  int TData;		/**< Used for splitting*/
  bool isLeaf;	/**< Checks if value is a leaf*/

  node(){
    LNode = nullptr;
    MNode = nullptr;
    RNode = nullptr;
    TNode = nullptr;
    
    AData = 0;
    BData = 0;
    TData = 0;

    isLeaf = true;
  };

 /** Insert
  *   @pre New value to be put into the tree
  *   @post Value is placed into the tree
  */
  bool insert(int newData){
    bool hasSplit = false;
    if(isLeaf){
      if(AData > 0){
        if(BData > 0){
          TData = newData;
        }
        else{BData = newData;}
      }
      else{AData = newData;}
    }
    if(!isLeaf){
      if(MNode != nullptr && AData < newData && (BData == 0 || BData > newData)){
        if(MNode->insert(newData)){
          if(BData == 0 && RNode == nullptr){
            BData = newData;
            RNode = new node;
            if(RNode->insert(newData)){
              //This is the space where RNode is full
              hasSplit = true;
            }
            MNode->TData = 0;
            MNode->TNode = nullptr;
          }
        }
      }
      if(0 < BData && BData < newData){
        if(RNode->insert(newData)){
          //This is the space where RNode is full
          TNode = RNode->TNode;
          TData = RNode->TData;
          hasSplit = true;
        }
      }
    }

    if(TData > 0){
      hasSplit = true;
    }

    if(hasSplit){
      if(testing){
        cout << "node needs to split\n";
        displayNode();
      }
      TNode = split();
      if(testing){
        cout << "node after the split\n";
        displayNode();
        cout << "TNode after the split\n";
        TNode->displayNode();
      }
    }

    if(hasSplit){
      TData = TNode->AData;
    }

    if(BData == 0 && hasSplit){
      //BData = TData
    }

    if(testing && TData == 0){displayNode();}

    return hasSplit;
  }

 /** Display Node
  *   @pre none
  *   @post Displays The blocks within itself and the blocks pointed to by its children pointers.
  */
  void displayNode(){
    cout << "LNodeBData\tMNodeAData\tRNodeAData\tTNodeAData\tAData\t\tBData\t\tTData\t\tisLeaf\n";
    if(LNode != nullptr){cout << LNode->BData << "\t\t";}
    if(LNode == nullptr){cout << "NULL\t\t";}
    if(MNode != nullptr){cout << MNode->AData << "\t\t";}
    if(MNode == nullptr){cout << "NULL\t\t";}
    if(RNode != nullptr){cout << RNode->AData << "\t\t";}
    if(RNode == nullptr){cout << "NULL\t\t";}
    if(TNode != nullptr){cout << TNode->AData << "\t\t";}
    if(TNode == nullptr){cout << "NULL\t\t";}

    cout << AData << "\t\t" << BData << "\t\t" << TData << "\t\t" << isLeaf << endl << endl;
  }

  node * oldsplit(){
    node * newNode = new node;
    
    newNode->LNode = MNode;
    newNode->MNode = RNode;
    newNode->AData = BData;
    newNode->BData = TData;
    newNode->isLeaf = isLeaf;
    if(testing){cout << "newNode set\n";}
    
    MNode = nullptr;
    RNode = nullptr;
    TNode = nullptr;
    
    BData = 0;
    TData = 0;

    return newNode;
  };

  node * split(){
    node * newNode = new node;
    
    newNode->LNode = RNode;
    newNode->MNode = TNode;
    newNode->AData = TData;
    newNode->BData = 0;
    newNode->isLeaf = isLeaf;
    if(testing){cout << "newNode set\n";}
    
    RNode = nullptr;
    TNode = nullptr;
    
    TData = 0;

    return newNode;
  }

  node * newsplit(){
    node * newNode = new node;

    if(RNode != nullptr){
      newNode->LNode = MNode;
      newNode->MNode = RNode;
      newNode->AData = BData;
      newNode->BData = TData;
      newNode->isLeaf = isLeaf;
      if(testing){cout << "newNode set\n";}
      
      MNode = nullptr;
      RNode = nullptr;
      TNode = nullptr;
      
      BData = 0;
    }
    else{
      newNode->LNode = RNode;
      newNode->MNode = TNode;
      newNode->AData = TData;
      newNode->BData = 0;
      newNode->isLeaf = isLeaf;
      if(testing){cout << "newNode set\n";}
      
      RNode = nullptr;
      TNode = nullptr;
       
    }

    TData = 0; 
    
    return newNode;
  }
};


struct handler{
  node * aNode = new node;

 /**  Build
  *   @pre Count of number of elements to be put into the tree, to be replaced with link list.
  *   @post A built Tree.
  */
  void build(int count){   
    for(int i = 1; i < count; i++){
      cout << "Inserting " << i << endl;
      if(aNode->insert(i)){
        node * t = new node;
        node * newRoot = new node;
        newRoot->isLeaf = false;
        t = aNode->TNode;
        aNode->TNode = nullptr;
        aNode->TData = 0;

        if(aNode->isLeaf){
          newRoot->LNode = aNode;
          newRoot->MNode = t;
          newRoot->AData = t->AData;
          aNode = newRoot;
        }

        else if(aNode->BData < aNode->TData && aNode->RNode != nullptr){
          node * newLNode = new node;
          node * newMNode = new node;
          newLNode->isLeaf = false;
          newMNode->isLeaf = false;
          newLNode->LNode = aNode->LNode;
          newLNode->MNode = aNode->MNode;
          newMNode->LNode = aNode->RNode;
          newMNode->MNode = t;
          newRoot->LNode = newLNode;
          newRoot->MNode = newMNode;
          aNode = newRoot;
        }

        else{
          newRoot->LNode = aNode;
          newRoot->MNode = t;
          newRoot->AData = (newRoot->LNode)->BData;
          //(newRoot->LNode)->BData = 0;
          aNode = newRoot;
        }
        cout << "Least " << getLeastNode() << endl << endl;
      }

      cout << "\n\nRoot " << i << endl;
      DisplayRoot();
    }

    cout << "Fill complete\n";
  }

 /** Display Root
 	*   @pre none
 	*   @post Displays The blocks within itself and the blocks in its children.
 	*/
  void DisplayRoot(){
    aNode->displayNode();

    if(aNode->LNode != nullptr){
      (aNode->LNode)->displayNode();
    }  
    
    if(aNode->MNode != nullptr){
      (aNode->MNode)->displayNode();
    }  
    
    if(aNode->RNode != nullptr){
      (aNode->RNode)->displayNode();
    }  
  }

 	/**  Get Least Node
 	 *   @pre none
 	 *   @post Return the smallest RBN.
 	 */
  int getLeastNode(){
    int least = 0;
    node * currentNode = aNode->RNode;
    while(currentNode != nullptr){
      least = currentNode->AData;
      currentNode = currentNode->LNode;
    }
  }
};

	 /**  Get Greatest Node
 		*   @pre none
 		*   @post Returns the largest RBN.
 		*/

	 /** 	Search
 		*   @pre Record
 		*   @post Block Pointer
 		*/

int main(){
  handler tree;

  tree.build(14);
}