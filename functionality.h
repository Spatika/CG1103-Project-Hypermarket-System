#ifndef FUNC_H
#define FUNC_H

//#include "SortedList.h"
//#include "dcll.h"
//#include "ListVector.h"
#include "Perishables.h"
#include "DAList.h"

#include <fstream>
#include <iostream>
#include <ctime>
#include <time.h>
#include<conio.h>
using namespace std;

template <typename T> 
class functionality
{
	T ob;
	void setcolor(unsigned int color) ;
	
	//structure to help in the top manufacturers statistic
	struct manu
	{
		string name;
		double rev;
	};

public:

	//destructor to finally write all the details onto a file
	~functionality();

	//search for the existance of a product with a given barcode; exists = true does not is false 
	bool search(int);

	//to search the database
	int search(int barcode, Product*&);
	int search(string, int, Product**);

	//get the stock available for a given product
	int obtstock(int);

	//to get the number of products in the store
	int getnop();
	int length();

	//to add products
	bool add(string, int, string, double, string, int, int);
	bool add(string, int, string, double, string, int, int, double, int, int, int);

	//to delete products
	bool scrap(string, int) ;
	bool scrap(int) ;

	void reset() ;

	//to make sales
	bool sale(string, int, int);
	bool sale(int, int);

	//to restock products
	bool restock(string, int, int);
	bool restock(int, int);

	int IfExpired(string, int) ;
	int IfExpired(int) ;

	void print();
	void pageprint();

	//loading and writing from file
	bool loaddata(string);
	bool writedata();

	//generating statistics
	bool topsales(int);
	bool botsales(int);
	bool ctop(string);
	bool mtop();
	bool expire();

	//special functions for batchprocessing
	bool batchscrap(int);
	bool batchrestock(int,int);
	bool batchsale(int,int);
	bool batchreset(int) ;
	bool batchIfExpired(int, int) ;
};

#endif