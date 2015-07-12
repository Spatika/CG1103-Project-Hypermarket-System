#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;

struct Date{
	int day;
	int month;
	int year;
};

class Product
{
protected:
	
	string Name;
	string Category;
	int Barcode;
	double Price;
	string Manufacturer;
	int SoldPerMonth;
	int Stock;

public:

	Product(string, int, string, double, string, int, int);

	string getName();

	int getBarcode();

	double getPrice();

	string getManu();

	int getSold();
	void addSold(int);

	int getStock();
	void restock(int);

	string getCategory();

	void Reset();
	void setstock(int) ;

	virtual char producttype();
	virtual Date getDate();
	virtual double getDiscount();
	virtual void printproduct();
} ;
#endif