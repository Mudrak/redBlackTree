// FILE: Rbt.h
// Erik Mudrak, Transy U
// CS 2444, Fall 2014
//
//      Interface for Red Black Tree
//

#ifndef	Rbt_H
#define	Rbt_H

#include     "DataType.h"

class Rbt {

public:
////// public member functions:	
    Rbt (void);
    ~Rbt (void);

//// put 
//      put <newItem> in the Table, if it's not already there
    bool put (const DataType& newItem);

//// get
//      retrieve the <item> that matches <key>, if it's here
    bool get (const KeyType& searchKey, DataType& foundItem) const;

//// printDEBUG
//      display the current contents of the Table
    void printDEBUG (void) const { printDEBUG (root); } //This may need to be edited for prog8



private:
////// private data:
    struct Node {
        DataType    dataItem;
        Node        *left, *right;
	bool	    color;	
	// Or more brute force: "turn around and check kids and grandkids 
	//	for red nodes in a row" : Not sure how to do this though

    // Node constructor
        Node (const DataType& newItem) {
            dataItem = newItem;
            left = right = 0;
	    color = 1;
        }
    } *root;

////// private member functions:
    void kill (Node *pRoot);
    bool put (Node*& pRoot, const DataType& newItem);
    bool get (Node* pRoot, const KeyType& searchKey, DataType& foundItem) const;
    void split(Node*& pRoot);
    void rebalanceLeftLeft(Node*& pRoot);
    void rebalanceLeftRight(Node*& pRoot);
    void rebalanceRightLeft(Node*& pRoot);
    void rebalanceRightRight(Node*& pRoot);
    void printDEBUG (Node *pRoot) const;
    void printColor (Node *pRoot) const;
    void printNode (Node *pRoot) const;

};

#endif

