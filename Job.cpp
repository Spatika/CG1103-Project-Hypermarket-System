#include "Job.h"
#include <iostream>
using namespace std;
#include <string>

Job::Job(string act, string name, string cat, int bc, double price, string manu, int stock)
{
	Action = act;
	Name = name;
	Category = cat;
	Barcode = bc;
	Price = price;
	Manufacturer = manu;
	Stock = stock;
	Date = 0; //sold why not initialized
}

Job::Job(string act, int bc) //for delete
{
	Action = act; 
	Name = "";
	Category = "";
	Barcode = bc;
	Price = 0;
	Manufacturer = "";
	Stock = 0;
	Date = 0;
}

Job::Job(string act, int first, int scnd) //for restock, sale, dispose
{
	Action = act;

	if(Action == "RESTOCK") 
	{
		Name = "";
		Category = "";
		Barcode = first;
		Price = 0;
		Manufacturer = "";
		Stock = scnd;
		Date = 0;
	}
	else
		if(Action == "SALE")
		{
			Name = "";
			Category = "";
			Barcode = first;
			Price = 0;
			Manufacturer = "";
			Stock = -scnd; //can add to stock later when doing processing in process() function
			Date = 0;
		}
		else //DISPOSE (set stock to 0)  -> just created current date in Date of Job
		{
			Name = "";
			Category = "";
			Barcode = first;
			Price = 0;
			Manufacturer = "";
			Stock = 0;
			Date = scnd;
		}
}

string Job::getAction()
{
	return Action;
}

string Job::getName()
{
	return Name;
}
	
string Job::getCat()
{
	return Category;
}


int Job::getBar()
{
	return Barcode;
}

int Job::getSale()
{
	return Sold;
}

double Job::getPrice()
{
	return Price;
}

string Job::getMan()
{
	return Manufacturer;
}

int Job::getStock()
{
	return Stock;
}

int Job::getDate()
{
	return Date;
}


