#ifndef DCLL_H
#define DCLL_H
#include "ListBase.h"
#include <iostream>
using namespace std;

template <class T>
class dcll: public ListBase{
	struct listnode
	{
		T p;
		listnode *next;
		listnode *prev;
	} *tail;
public:
	dcll();
	~dcll();

	//function to add a product to the list
	bool insert(T p) ;
	
	//function to remove a product from the list based on its name or barcode
	bool remove(int index);

	//retrieval
	bool retrieve(int index,T &p ); 


	//search 1->name 2->category 3-> marnufacturer return number of same entries
//	int search(string s,int a,Product** p);//array of pointers of size getlength()
//	int search(int a ,Product*&p);
};

#endif