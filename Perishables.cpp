#include "Perishables.h"
#include <string>
#include <iostream>
using namespace std;


Perishables::Perishables(string name, int code, string manu, double price, string category, int stock, int sold, double x, int d, int m, int y)
	:Product(name, code, manu, price, category, stock, sold) 
{
	Discount = x;
	E_Date.day = d;
	E_Date.month = m;
	E_Date.year = y;
}

Date Perishables:: getDate()
{
	return E_Date;
}

double Perishables:: getDiscount()
{
	return Discount;
}

char Perishables::producttype()
{
	return 'y';
}

void Perishables::printproduct()
{
	cout<<"\nName\t:"<<getName();
	cout<<"\nCategory:"<<getCategory();
	cout<<"\nManufacturer :"<<getManu();
	cout<<"\nPrice\t:"<<getPrice();
	cout<<"\nBarcode\t:"<<getBarcode();
	cout<<"\nStocks Available :"<<getStock();
	cout<<"\nSold Per Month :"<<getSold();
	cout<<"\nExpiry Date\t:"<<getDate().day<<'/'<<getDate().month<<'/'<<getDate().year;
	cout<<"\nDiscount Percentage "<<getDiscount();
}