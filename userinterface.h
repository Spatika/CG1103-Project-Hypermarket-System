#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include<iostream>
#include<iomanip>
#include <string>
#include <conio.h>

#include "functionality.h"



class UI
{	 
	int choicemenu() ;
	
	
public:

	int mainmenu();
	void heading();

	int choice1() ; //for updating inventory menu

	int addmenu() ;
	int addproduct(int choice, string &name, int &code, string &manu, float &price, string &category, int &stock, int &sold, float &discount, int &d, int &m, int &y);
	
	int Delete() ;
	void reset() ;
	int sell() ;
	int restock() ;
	int checkexpired() ;

	int searchmenu();

	int statsmenu();
	int toplow(int ch) ; //controller calls this for finding X in topX selling products

	string loaddata() ;
	void listall() ; 
	
	string getattribute(int) ; /*1name 2category 3manufacturer 4barcode */
	string getattribute(int, int&, string) ;

	int getbarcode() ;
	int getbarcode(int&,string) ;

	void setcolor(unsigned int) ;
	void gotoxy(short int, short int) ;

	void quit(string);
	
	
};

#endif