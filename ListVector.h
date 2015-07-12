#ifndef LISTVECTOR_H
#define LISTVECTOR_H

#include "ListBase.h"
#include<vector>
#include<string>
using namespace std ;

template <typename T> //T to be substituted by Product * for CICMS
class ListVector: public ListBase
{

private:
	
  vector<T> List ;

public:

	bool insert(T) ;
	bool remove(int) ; //remove by int argument = index
	bool retrieve(int, T&) ; //retrieve by index (int argument), assign found node of list to T, passed by reference
	
} ;

#endif
