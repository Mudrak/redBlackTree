// FILE: DataType.h
// R England, Transy U
// CS 2444, Fall 2014
//
//	Define a common data type and key type for testing a Table implementation
//

#ifndef DATATYPE_H
#define DATATYPE_H

#define USE_MP3
#ifdef  USE_MP3

#include "Mp3.h"
typedef Code	KeyType;
typedef Mp3   	DataType;

#else

typedef int KeyType;
typedef int DataType;

#endif
#endif
