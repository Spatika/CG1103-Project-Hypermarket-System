#include <iostream>
#include <string>
#include "Product.h"
using namespace std;

Product::Product(string name, int code, string manu, double price, string category, int stock, int sold)
{
	Name = name;
	Barcode = code;
	Manufacturer = manu;
	Price = price;
	Category = category;
	SoldPerMonth = sold;
	Stock = stock;
}

string Product::getName()
{
	return Name;
}


int Product::getBarcode()
{
	return Barcode;
}


double Product::getPrice()
{
	return Price;
}


string Product::getManu()
{
	return Manufacturer;
}


int Product::getSold()
{
	return SoldPerMonth;
}

void Product::addSold(int x)
{
	SoldPerMonth += x;
	Stock -=x;
	return;
}

int Product::getStock()
{
	return Stock;
}


void Product::Reset()
{
	SoldPerMonth = 0;
}

void Product::setstock(int newstock)
{
	Stock = newstock ;
}

string Product::getCategory()
{
	return Category;
}


char Product::producttype()
{
	return 'n';
}

void Product::restock(int qty)
{
	Stock += qty;
}

void Product::printproduct()
{
	cout<<"\nName\t:"<<getName();
	cout<<"\nCategory:"<<getCategory();
	cout<<"\nManufacturer :"<<getManu();
	cout<<"\nPrice\t:"<<getPrice();
	cout<<"\nBarcode\t:"<<getBarcode();
	cout<<"\nStocks Available :"<<getStock();
	cout<<"\nSold Per Month :"<<getSold();
}

Date Product:: getDate()
{
	Date D={0,0,0};
	return D;
}
double Product::getDiscount()
{
	return -1; //non perishable discount is -1 
}