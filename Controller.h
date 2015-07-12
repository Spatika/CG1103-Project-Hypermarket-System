#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "functionality.h"
#include "stack.h" //stack of 'Submission' objects = each one has name of person who submitted jobs and a QueueLL of their Job objects (each Job object has Action, Manufacturer, barcode, category, date, price 
#include "QueueLL.h"
#include "userinterface.h"
#include <iostream>

using namespace std;	

//Submission is a struct
//why is Submission a struct and Job a class?

class controller
{

	functionality<DAList<Product*>> Ob;
	Stack<Submission> WhoseTurn; 
	UI view;

	bool add();
	bool del();
	bool resetsales();
	bool makesale();
	bool stockup();
	bool checkexpire();
	bool stats();
	void loaddata();
	bool load();
	void process();
	bool search(); //what is Controller's search for??

	bool menu1();

public:
	void initiate(string);
	
};

#endif