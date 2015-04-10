// FILE: Rbt.cpp
// Erik Mudrak, Transy U
// CS 2444, Fall 2014
//
//      Implementation of Red Black Tree
//
#include    <iostream>
#include    "Rbt.h"
using namespace std;

// symbolic constants for color
const bool BLACK = 0;
const bool RED = 1;

/////
//// public member functions:
///

// constructor
Rbt::Rbt () {
    root = 0;
}

// destructor
Rbt::~Rbt () {
    kill (root);
}

// put  [public wrapper]	
bool Rbt::put  (const DataType& newItem) {
    if (put (root, newItem)) {
    root->color = BLACK;
    return true;
    } 
    return false;
}

// get [public wrapper]
bool Rbt::get (const KeyType& searchKey, DataType& foundItem) const {
    return get (root, searchKey, foundItem);
}

/////
//// private member functions:
///

//// put  [private overload]
///		put <newItem> in the tree, if it's not already there
//
bool Rbt::put (Node*& pRoot, const DataType& newItem) {
// base cases
    if (!pRoot) {
        pRoot = new Node (newItem);
        return true;
    }
    if (newItem == pRoot -> dataItem)
        return false;

// Checks if a split is needed before adding or rebalancing
    if (pRoot-> color == BLACK) {
	split(pRoot);
    }

// recursive cases, does not return right away, but instead saves the value for later
    bool futureReturnValue = (newItem > pRoot -> dataItem) ?
    		put (pRoot-> right, newItem) : 
      	   	put (pRoot-> left, newItem);
  
// On the way up the tree: 
//	detect 2 red nodes in a row after a black node and balance tree in each case

    if (pRoot->color == BLACK) {
	// Case 1: Left - Left, kids and grandkids: 2 red nodes
	if ((pRoot-> left) && (pRoot->left->color == RED) &&
	(pRoot->left->left) && (pRoot->left->left->color == RED)) {
		rebalanceLeftLeft(pRoot);
		cout << endl << "Case: L-L";
	} 
	// Case 2: Left - Right
	if ((pRoot-> left) && (pRoot->left->color == RED) &&
	(pRoot->left->right) && (pRoot->left->right->color == RED)) {
		rebalanceLeftRight(pRoot);
		cout << endl << "Case: L-R";
	} 
	// Case 3: Right - Left
	if ((pRoot-> right) && (pRoot->right->color == RED) &&
	(pRoot->right->left) && (pRoot->right->left->color == RED)) {
		rebalanceRightLeft(pRoot);
		cout << endl << "Case: R-L"; 
	}
	// Case 4: Right - Right
	if ((pRoot-> right) && (pRoot->right->color == RED) &&
	(pRoot->right->right) && (pRoot->right->right->color == RED)) {
		rebalanceRightRight(pRoot);
		cout << endl << "Case: R-R";
	}

   }
   // it's back: use the recursive cases now that we've tried to balance
   return futureReturnValue;
}

/// Split Function 
/// 		Checks children to see if they exist, and if they are red. 
//		If both conditions are true, they are recolored and put into a new 'box'

void Rbt::split(Node*& pRoot) {
	if ((pRoot->left) && (pRoot-> left-> color == RED) && (pRoot-> right) && (pRoot->right-> color == RED)) {
	pRoot->color = RED;
	pRoot-> left-> color = BLACK;
	pRoot-> right-> color = BLACK;
	}
}
//// Rebalance Functions
///		Re-balances tree in each case using cascading assignment statements to rotate nodes
//

// Case 1: 
void Rbt::rebalanceLeftLeft(Node*& pRoot) {
	
	Node* temp;
	temp = pRoot;
	pRoot = temp-> left;
	temp-> left = pRoot-> right;
	pRoot-> right = temp;
	// colors:
	pRoot-> right-> color = RED;		
	pRoot-> color = BLACK;
}	

// Case 2:
void Rbt::rebalanceLeftRight(Node*& pRoot) {
	
	Node* temp;
	temp = pRoot;
	pRoot = temp-> left-> right;
	temp-> left-> right = pRoot-> left;
	pRoot-> left = temp-> left;
	temp-> left = pRoot-> right;
	pRoot-> right = temp;
	// colors:
	pRoot-> left-> color = RED;
	pRoot-> right-> color = RED;
	pRoot-> color = BLACK;
}	

// Case 3:
void Rbt::rebalanceRightLeft(Node*& pRoot) {
 
	Node* temp;
	temp = pRoot;
	pRoot = temp-> right-> left;
	temp-> right-> left = pRoot-> right;
	pRoot-> right = temp-> right;
	temp-> right = pRoot-> left;
	pRoot-> left = temp;
	// colors: 
	pRoot-> left-> color = RED;
	pRoot-> color = BLACK;
}

// Case 4:
void Rbt::rebalanceRightRight(Node*& pRoot) {	

	Node* temp;
	temp = pRoot;
	pRoot = temp-> right;
	temp-> right = pRoot-> left;
	pRoot-> left = temp;
	// colors:
	pRoot-> left-> color = RED;
	pRoot-> color = BLACK;
}

//// get [private overload]
///		retrieve <foundItem> that matches <searchKey>, if it's here
//
bool Rbt::get (Node* pRoot, const KeyType& searchKey, DataType& foundItem) const  {
// base cases
    if (!pRoot)
        return false;
    if (searchKey == pRoot -> dataItem) {
        foundItem = pRoot -> dataItem;
        return true;
    }

// recursive cases
    return (searchKey > pRoot -> dataItem) ?
            get (pRoot -> right, searchKey, foundItem) :
            get (pRoot -> left, searchKey, foundItem);
}

//// kill
///     destroy this node and all of its descendants
//		[Q: Which traversal?]
//
void Rbt::kill (Node* pRoot) {
    if (pRoot) {
        kill (pRoot -> left);
        kill (pRoot -> right);
        delete pRoot;
    }
}


//// printDEBUG
///     display the current contents of the tree
//      [Q: Which traversal?]
//
void Rbt::printDEBUG (Node *pRoot) const {
    if (pRoot) {
        printNode (pRoot);
        printDEBUG (pRoot -> left);
        printDEBUG (pRoot -> right);
    }
}


//// printColor
///		display the color of each node
//
void Rbt::printColor (Node *pRoot) const {
    if (pRoot->color)
	cout << " [color: Red]" << endl;
    else 
	cout << " [color: Black]" << endl;	
}

//// printNode
///		display the current contents of a node
//
void Rbt::printNode (Node *pRoot) const {
    cout << endl << "data: " << pRoot -> dataItem;
    printColor(pRoot);
    cout << endl << "\tleft: ";
    if (pRoot -> left) {
        cout << pRoot->left->dataItem;
   	printColor(pRoot->left);	
    } 
    else {
        cout << "[EXTERNAL]";
	//printColor(pRoot);
    }
    cout << endl << "\tright: ";
    if (pRoot -> right) {
        cout << pRoot->right->dataItem;
	printColor(pRoot->right);
    }
    else {
        cout << "[EXTERNAL]";
	//printColor(pRoot);
    cout << endl;
    }
}


