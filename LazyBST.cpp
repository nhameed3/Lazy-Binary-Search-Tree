/*Title: LazyBST.cpp
Author: Nauman Hameed
Date: 4/11/17
CMSC 341 Spring 2017
Description: LazyBST, binary search tree 
this file uses Dr. Park's implementation
*/
#include "LazyBST.h"

//Default constructor
 LazyBST::LazyBST(){
  root = NULL;
}

//Copy constructor for the BST, passes to another helepr function
 LazyBST::LazyBST(const LazyBST& other){
    copyConstruct(this->root, other.root);
 }

//Creates a deep copy of the binary search tree
void LazyBST::copyConstruct(Node*& newNode, Node* const &oldNode){
  //handles case that the tree is empty
  if(oldNode == NULL){
    newNode = NULL;
  }
  else{
    //creates a new node to replicate the bst node
    newNode = new Node(oldNode->value);
    newNode->size = oldNode->size;
    newNode->height = oldNode->height;
    newNode->left = oldNode->left;
    newNode->right = oldNode->right;
    //recursive calls for the left and right subtree
    copyConstruct(newNode->left, oldNode->left);
    copyConstruct(newNode->right, oldNode->right);
  }
}

//Destructor, calls a function that takes in the root
 LazyBST::~LazyBST(){
    ClearTree(root);
 }

//Constructor for node
LazyBST::Node::Node(int key){
  value = key;
  left = NULL;
  right = NULL;
  height = 0;
  size = -1;
}

//Called to destroy subtree, free memory
void LazyBST::ClearTree(Node *&nodePtr){
 if (nodePtr)
 {
  if (nodePtr->left)
    ClearTree(nodePtr->left);
  if (nodePtr->right)
    ClearTree(nodePtr->right);
   //after the tree is gone, takes care of the node
  delete nodePtr;
  nodePtr=NULL;
 }
} 

//Assignment operator overloaded to allow one BST to become another
const LazyBST& LazyBST::operator=(const LazyBST& rhs){
  ClearTree(root);
  copyConstruct(root, rhs.root);
  return *this;
}

//Creates a node and then passes to a function that takes care of the insertion
void LazyBST::insert (int key){
  if(find(key)){ 
    return;
  }
  Node *newNode = NULL; // Pointer to a new node
  // Create a new node and stores the key in it.
  newNode = new Node(key);
  insertNode(root, newNode); 
}

//Tests a variety of cases for the proper insertion of the node created 
void LazyBST::insertNode(Node *&nodePtr, Node *&newNode){
  // Top down check for rebalancing
  if(nodePtr != NULL && nodePtr->height > 3){
    //making sure left and right exist
    if(nodePtr->right !=NULL && nodePtr->left !=NULL){
       //if one of the subtree's is twice or more the size of the other then rebalance
      if(nodePtr!= NULL &&  nodePtr->right->size >= (nodePtr->left->size *2) ){
        rebalance(nodePtr);
      }
       //if one of the subtree's is twice or more the size of the other then rebalance
      else if(nodePtr!= NULL &&  (nodePtr->left->size) >= (nodePtr->right->size *2) ){
        rebalance(nodePtr);
      }  
    }
  }
  if (nodePtr == NULL)
    nodePtr = newNode; // Insert the node
  //if value is less than nodePtr 
  else if (newNode->value < nodePtr->value){
    // Search the left branch
    insertNode(nodePtr->left, newNode);
  }  
  //if value is greater than nodePtr
  else if(newNode->value > nodePtr->value){
    // Search the right branch
    insertNode(nodePtr->right, newNode); 
  }
  
  //updates height and size, bottom up
  nodePtr->height = nodeHeight(nodePtr);
  nodePtr->size = nodeSize(nodePtr);
} 


//Returns the height of the node being passed in;
int LazyBST::nodeHeight(Node *&nodePtr){
  int left = -1;
  int right = -1;
  if(nodePtr == NULL){
    return -1;
  }
  //Setting heights for the left and right 
  else{
    if(nodePtr->left != NULL){
      left = nodePtr->left->height;
    }
    if(nodePtr->right != NULL){
      right = nodePtr->right->height;
    }
    //maximum height
    return nodePtr->height = max(left, right)+1;
  }
}

//Returns the size of the node being passed in
int LazyBST::nodeSize(Node *&nodePtr){
  if(nodePtr == NULL){
    return 0;
  }
  int right = 0;
  int left = 0;
  
  //Setting heights for the left and right
  if(nodePtr->right != NULL){
    right = nodePtr->right->size;
  }
  
  if(nodePtr->left != NULL){
    left = nodePtr->left->size;
  }
  //Getting the total size
  return nodePtr->size = (left + right) +1;
}




//Converts the subtree into a sorted array
void LazyBST::intoArray(int *treeArray, Node *&nodePtr, int &index ){
  if(nodePtr){
    //steps through the array using recursion and inserts those values
    intoArray( treeArray, nodePtr->left, index);
    treeArray[index] = nodePtr->value;
    index++;
    intoArray( treeArray, nodePtr->right, index);
  } 
}

//Rebalances the height of the subtree when necessary
void LazyBST::rebalance(Node *&nodePtr){
  //Array that will hold the values
  int sizeArray = nodePtr->size;
  int Array[sizeArray];
  int *treeArray = Array;
  int startIndex =0;
  intoArray( treeArray, nodePtr, startIndex );
  //Destroys that subtree converted into an array
  ClearTree(nodePtr);
  //Adds the node returned with its subtree back to where it was taken away
  nodePtr = arrayToBST(treeArray, 0, sizeArray-1);
}


// A function that constructs Balanced Binary Search Tree from a sorted array 
LazyBST::Node* LazyBST::arrayToBST(int *treeArray, int start, int end)
{  
    if (start > end)
      return NULL;
 
    // Get the middle element and make it the root 
    int mid = (start + end)/2;
    Node *nodePtr = new Node(treeArray[mid]);
 
    // Recursively construct the left subtree and make it left child of root 
    nodePtr->left = arrayToBST(treeArray, start, mid-1);
 
    // Recursively construct the right subtree and make it right child of root 
    nodePtr->right = arrayToBST(treeArray, mid+1, end);
    
    //updates the height and the size of the node
    nodePtr->height = nodeHeight(nodePtr);
    nodePtr->size = nodeSize(nodePtr);
    
    //returns a node
    return nodePtr;
}




//If the node is in the tree, this functions passes desired removal to helper function.
bool LazyBST::remove(int key){
  if(find(key)){ 
    removeNode(key, root);
    return true;
  }
  //Message to alert the user.
  else{
    cout << "NODE NOT FOUND" << endl;
    return false;
  }
 }



void LazyBST::removeNode( int x, Node *& nodePtr ){
  // Top down check for rebalancing
  if(nodePtr != NULL && nodePtr->height > 3){
    //making sure left and right exist
     if(nodePtr->right !=NULL && nodePtr->left !=NULL){
       //if one of the subtree's is twice or more the size of the other then rebalance
        if(nodePtr!= NULL &&  nodePtr->right->size >= (nodePtr->left->size *2) ){
          rebalance(nodePtr);
        }
        //if one of the subtree's is twice or more the size of the other then rebalance
        else if(nodePtr!= NULL &&  (nodePtr->left->size) >= (nodePtr->right->size *2) ){
          rebalance(nodePtr);
      }
     }
  }
  
  // if null, do nothing
  if( nodePtr == NULL ){
    return; 
  } 
  
  // continue to traverse until we find the element
  //left 
  if( x < nodePtr->value ){ 
    removeNode( x, nodePtr->left ); 
    nodePtr->height = nodeHeight(nodePtr);
    nodePtr->size = nodeSize(nodePtr);
  }
  
  //right
  else if( nodePtr->value < x ){
    removeNode( x, nodePtr->right ); 
    nodePtr->height = nodeHeight(nodePtr);
    nodePtr->size = nodeSize(nodePtr);
  }
  
  // two children
  else if( nodePtr->left != NULL && nodePtr->right != NULL ){
    // finding left’s greatest value
    nodePtr->value = findMax( nodePtr->left );
    // deleting that found value
    removeNode( nodePtr->value, nodePtr->left );
    //updating height
    nodePtr->height = nodeHeight(nodePtr);
    nodePtr->size = nodeSize(nodePtr);
  }
  
  // zero or one child
  else{
    Node *oldNode = nodePtr;
    nodePtr = ( nodePtr->left != NULL ) ? nodePtr->left : nodePtr->right;
    delete oldNode; 
    oldNode=NULL;
  }
} 

//Finds the maximum value of the subtree
int LazyBST::findMax(Node *node){
   Node* nodePtr = node;
  // loop down to find the rigthmost leaf 
  while (nodePtr->right != NULL) {
    nodePtr = nodePtr->right;
  }
  //returns the value of the greatest node of the subtree
  return(nodePtr->value);
}

//Searches the binary search tree for a specified value.
bool LazyBST::find(int key){
  Node *nodePtr = root;
  while (nodePtr){
  if (nodePtr->value == key)
    return true;
  else if (key < nodePtr->value)
    nodePtr = nodePtr->left;
  else
    nodePtr = nodePtr->right;
  }
  return false; 
}


//inorder traversal of the tree
void LazyBST::inorder(){
  //passes it off to a function that takes in the root
  inorderTraversal(root);
}

void LazyBST::inorderTraversal(Node *nodePtr){
  //only done if found
  if (nodePtr)
  {
    cout << '(' ;
    inorderTraversal(nodePtr->left);
    cout << nodePtr->value << ":" << nodePtr->height << ":" << nodePtr->size;
    inorderTraversal(nodePtr->right);
    cout << ')';
  } 
}


//Locates a node in a tree, using characters as direction.
bool LazyBST::locate(const char *position, int& key){
    return locateNode(position, root, key, 0);
}

//Function uses characters to search through tree.
bool LazyBST::locateNode( const char *position, Node* nodePtr, int& key, int index){
  bool boolean = false;
  if(nodePtr){
    //if char is R then increase index and  recursively call locateNode with nodePtr->right 
    if(position[index]=='R'){
        index++;
        boolean = locateNode(position, nodePtr->right, key, index);
    }
    //if char is L then increase index and  recursively call locateNode with nodePtr->left 
    else if(position[index]=='L'){
        index++;
        boolean = locateNode(position, nodePtr->left, key, index);
    }
    //Once the node with such value is found, store it, return true
    else{
      key = nodePtr->value;
      boolean = true;
      return boolean;
    }
  }
  else{
    boolean = false;
    return boolean;
  }
  return boolean;
}