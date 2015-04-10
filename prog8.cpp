//	FILE: prog8.cpp
//	Erik Mudrak, Transy U
//  	CS 2444, Fall 2014
//
//    Test driver for P8 Rbt class
//
//    Build command: g++ prog8.cpp Rbt.cpp -o prog8
//          
#include	<iostream>
#include	"DataType.h"
#include	"Rbt.h"
using namespace std;

// symbolic constants
const KeyType SENTINEL = (KeyType)(-1);
const int QUIT = 0, PUT = 1, GET = 2;

// function prototypes
void  testPut (Rbt& t);
void  testGet (Rbt& t);
int   getMenuResponse (void);


/////
//// main program
///
//
int main (void) {
	Rbt  t;
	cout << endl << endl
	     << "TEST DRIVER FOR RBT CLASS" << endl << endl;

// see everything?
	char response;
	cout << "Show Rbt contents after each operation? [y/n]: ";
	cin >> response;
	bool showTree = (toupper (response) == 'Y');

// loop as long as user wants
	bool stop = false;
	do {
		if (showTree) {
           		cout << endl << endl << "   Current tree contents:" << endl;
           		t.printDEBUG ();
         	}
     
		switch (getMenuResponse ()) {
		case QUIT:		
			stop = true;
			break;
		case PUT:	
			testPut (t);
			break;
		case GET:		
			testGet (t);
			break;
		default:
			cout << "Not a valid response. Try again." << endl;
			break;
		}

	} while (!stop);
	cout << endl << endl;

	return 0;
}

// getMenuResponse
//	display a menu; read response from the keyboard
int getMenuResponse (void) {
	cout << endl << endl
		 << "Type \t" << PUT << " for put " << endl
		 << '\t' << GET << " for get" << endl
		 << '\t' << QUIT << " to quit" << endl << ": ";		
	int response;
	cin >> response;
	cout << endl;
	return response;
}

// testPut
//	try out the put  function for a Rbt object
void testPut (Rbt& t) {
	DataType value;
	cout << "\nItem to put : ";
	cin >> value;
	cout << endl << "Put operation "
             << ((t.put  (value)) ? "" : "NOT ")
             << "successful";
}

// testGet
//	try out the get function for a Rbt object
void testGet (Rbt& t) {
     KeyType key;
     DataType value;
     cout << endl << endl << "Next key to get: ";
     cin >> key;
     if (t.get (key, value)) {
	     cout << endl << "Success! Got this from tree:" << endl;
	     cout << value;
     }
     else {
	     cout << endl << "Get operation FAILED on tree for key " << key << endl;
     }
}

