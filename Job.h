#ifndef JOB_H //QueueLL of Job objects
#define JOB_H
#include <iostream>
using namespace std;


class Job
{
private:
	string Action;
	string Name; //name of product?
	string Category;
	int Barcode;
	double Price;
	string Manufacturer;
	int Stock, Sold;
	int Date;  //here is an integer -> how is it compared with struct Date?

public:

	Job(string, string, string, int , double, string, int) ; //why 3 ctors
	Job(string, int);
	Job(string, int, int);

	string getAction();
	string getName();
	string getCat();
	int getBar();
	int getSale();
	double getPrice();
	string getMan();
	int getStock();
	int getDate();
};


#endif