#ifndef PERISHABLES_H
#define PERISHABLES_H
#include "Product.h"

class Perishables: public Product
{
	Date E_Date;
	double Discount;

public:

	Perishables(string, int, string, double, string, int, int, double, int, int, int);

	Date getDate();
	double getDiscount();

	char producttype();
	void printproduct();
};

#endif