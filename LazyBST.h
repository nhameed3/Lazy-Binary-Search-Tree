// File: Graph.h
//Nauman Hameed
// CMSC 341 Spring 2017
// Header file for LazyBST class
#ifndef _LAZYBST_H_
#define _LAZYBST_H_
#include <iostream>
using namespace std;

class LazyBST{
  private:
    struct Node{
      int value; // The value in the node
      Node *left; // Pointer to left child node
      Node *right; // Pointer to right child node
      int height;
      int size;
      Node(int key);
    };

  
    Node *root; //Pointer to the root node

  public:
    void insertNode(Node *&nodePtr, Node *&newNode);
    void ClearTree(Node *&nodePtr);
    void inorderTraversal(Node *nodePtr);
    int nodeHeight(Node *&nodePtr);
    int nodeSize(Node *&nodePtr);
    void removeNode( int x, Node *&nodePtr );
    int findMax(Node *node );
    void rebalance(Node *&nodePtr);
    void intoArray(int *treeArray, Node *&nodePtr, int &index );
    bool locateNode( const char *position, Node* nodePtr, int& key, int index);
    Node* arrayToBST(int *treeArray, int start, int end);
    void copyConstruct(Node*& newNode, Node* const &oldNode);



    LazyBST() ;

    LazyBST(const LazyBST& other) ;

    ~LazyBST() ;

    const LazyBST& operator=(const LazyBST& rhs) ;

    void insert (int key) ;

    bool remove(int key) ;

    bool find(int key) ;

    void inorder() ;

    bool locate(const char *position, int& key) ;
};

#endif