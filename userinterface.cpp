#include "userinterface.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <Windows.h>
using namespace std ;


void UI::gotoxy ( short x, short y )
{
  COORD coord = {x, y};
  SetConsoleCursorPosition ( GetStdHandle ( STD_OUTPUT_HANDLE ), coord );
}

void UI::setcolor(unsigned int color) 
{                                    
    if (color >15 || color <=0)
    {
        cout <<"Error." <<endl;
        
    }
    else
    {    
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,color);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE) ;
    }
} 


int UI::mainmenu()
{
	
	heading() ;

	int choice;
	setcolor(10) ; //light blue
	gotoxy(20,6) ;
	std::cout << "CICMS Menu" ;
	gotoxy(20,8) ;
	setcolor(10) ;
	std::cout<<"1. Update the Inventory" ; //done
	gotoxy(20,9) ;
	std::cout << "2. Search Inventory" ;  //choice2
	gotoxy(20,10) ;
	std::cout << "3. Generate Statistics" ; //statsmenu function
	gotoxy(20,11) ;
	std::cout << "4. Perform Batch Processing" ; //no UI function
	gotoxy(20,12) ;
	std::cout << "5. List Inventory" ; //same
	gotoxy(20,13) ;
	std::cout << "6. Load Data" ; //same
	gotoxy(20,14) ;
	std::cout << "7. Log Out" ; //no function in UI for quit 
	gotoxy(20,16) ;
	std::cout << "Enter a choice: " ;
	std::cin >> choice ;
	std::cout << endl ;
	return choice ; //controller calls corresponding UI functions for 1-7, for anything else the user has entered, calls ui.wrongchoice() 
} 

//this function is called for choice=1
int UI::choice1()
{
	heading() ;
	int ch ;
	setcolor(10) ; //light green
	gotoxy(20,7) ;
	std::cout << "Update Inventory Menu" ;
	setcolor(11) ;
	gotoxy(20,9) ;
	std::cout << "1. Add a product" ;
	gotoxy(20,10) ;
	std::cout << "2. Delete a product" ;
	gotoxy(20,11) ;
	std::cout << "3. Reset product sales" ;
	gotoxy(20,12) ;
	std::cout << "4. Sell a product" ;
	gotoxy(20,13) ;
	std::cout << "5. Restock a product" ;
	gotoxy(20,14) ;
	std::cout << "6. Return to the main menu" ;
	gotoxy(20,16) ;
    cout << "Enter your choice (1-6): " ;
	
	cin >> ch ;
	return ch ;  //controller checks calls either ui.wrongchoice() or addmenu, deletemenu whatever accordingly...

}


//this function is called for choice=1
int UI::addmenu()
{
	system("cls") ;
	heading() ;
	gotoxy(20,8) ;
	setcolor(10) ;
	cout << "You have chosen to add a new product." ;
	setcolor(9) ; //light blue 
	
	int choice;
	cout << endl << endl ;
	cout<<"1. Add a new product "<<endl;
	cout<<"2. Add a new perishable product"<<endl;
	cout<<"3. Return to main menu"<<endl<<endl;
	cout<<"Please enter your choice (a number from 1-3): ";
	cin>>choice ; //possible error if user enters something other than 1, 2 or 3
    return choice ; //to controller
}

int UI::addproduct(int choice, string &name, int &code, string &manu, float &price, string &category, int &stock, int &sold, float &discount, int &d, int &m, int &y)
{
    system("cls");
    heading();
    setcolor(15) ;
 
	cout<<"\nEnter the details of the product to be added\t:";

	/*if choice=3 is returned from addmenu(), then the controller displays main menu again DOES NOT CALL addproduct()
	if 1 is returned, then controller needs to call addproduct with int argument choice=1, if 2 is returned from addmenu(), choice for addproduct is 2.
	if addproduct() returns 1, then controller calls successmessage(1). */
 
    cout<<"\n\nName of product\t:";
    getline(cin, name);
    getline(cin, name);
 
    cout<<"\nCategory\t:";
    getline(cin, category);
 
    cout<<"\nBarcode Number\t:";
    cin>>code;
 
    cout<<"\nPrice\t:";
    cin>>price;
 
    cout<<"\nManufacturer\t:";
    getline(cin, manu);
    getline(cin, manu);
 
    cout<<"\nNumber in Stock\t:";
    cin>>stock;
 
    cout<<"\nSold Per Month\t:";
    cin>>sold;
 
    switch(choice)
    {
    case 1:
        return 1;
    case 2:
        cout<<"\nExpiry date\t:"<<endl;
        cout<<"Day: ";
        cin>>d;
        cout<<endl;
        cout<<"Month: ";
        cin>>m;
        cout<<endl;
        cout<<"Year: ";
        cin>>y;
        cout<<endl;
                   
        cout<<"\nDiscount Percentage\t:";
        cin>>discount;
 
        return 1;
       
    }
	return 0;
}
	
//controller calls this if choice=2
int UI::Delete()
{
  		
		system("cls") ;
		heading();
		setcolor(10) ;
		gotoxy(20,8) ;
		std::cout<<"Delete product by\t:"<<endl<<endl;
		
		return choicemenu() ; 


		//controller takes the choice 1name 2category 3manufacturer 4barcode 5mainmenu 
		//if choice is 5 controller calls mainmenu() again (and therefore needs to perform the switch again!!)
		//if choice is 1-4 your controller needs to ask for name/category/manufacturer/barcode i.e. call getattribute with int argument!!
}		
		
	
//this function is called BY THE CONTROLLER for choice=3 and then calls the UI::successmessage(3)
void UI::reset()
{
	system("cls") ;
	heading() ;
	setcolor(10) ;
	gotoxy(20,8) ;
	std::cout<<"Resetting sales!" ;
	setcolor(15) ;
}

//controller calls this function for choice=4 
int UI::sell()
{
	system("cls");
	heading();
	setcolor(10) ;
	gotoxy(20,8) ;
	std::cout<<"Sell product by\t:"<<endl<<endl;

	return choicemenu() ;
	
	//depending on choice returned here, controller class calls getattribute with int argument,and another int argument passed by reference for the quantity
	//or getbarcode also
}

			
//called by the controller for choice=5
int UI::restock()
{
	system("cls");
	heading();
	setcolor(10) ;
	gotoxy(20,8) ;
		
	std::cout<<"Restock Product by:" <<endl<<endl;

	return choicemenu() ; //depending on this, controller calls either getattribute or getbarcode
		
}
		
//called by controller for choice=6
int UI::checkexpired()
{
		system("cls");
		heading();
		gotoxy(20,6) ;
		cout << "You have chosen to check if a product has expired." ;
		gotoxy(20,8) ;
		cout<<"Search for the expiry of a product by  :" ;
		return choicemenu() ; //this goes to controller, then controller calls getattribute() or getbarcode()
}
		


//controller calls this for the search menu
int UI::searchmenu()
{
	system("cls");
	heading();
	int choice;

	gotoxy(20,10) ;
	cout<<"Search for product(s) by\t:\t";

	gotoxy(20,12) ;
	std::cout << "1.Name" ;
	gotoxy(20,13) ;
	std::cout << "2.Category" ;
	gotoxy(20,14) ;
	std::cout << "3.Manufacturer" ;
	gotoxy(20,15) ;
	std::cout << "4.Barcode" ; 
	gotoxy(20,16);
	std::cout << "5.Check if a product has expired";

	gotoxy(20,18) ;
	cout << "OR" ;
	gotoxy(20,20) ;
	cout << "6.Return to main menu" ;
	gotoxy(20,21) ;
	cout<< "Please enter your choice (1-6): ";
	cin >> choice;
	return choice ;

}


//controller calls this when choice=3
int UI::statsmenu()
{
	system("cls");
	heading() ;
	
	int choice;
	gotoxy(20,8) ;
	setcolor(10) ;
  	cout<<"Statistical Information" ;
	setcolor(9) ; //blue
	gotoxy(20,10) ;
	cout<<"1. Top X selling product" ;//can be 5,10,15,20,etc
	gotoxy(20,11) ;
	cout<<"2. Best selling product in a category" ;
	gotoxy(20,12) ;
	cout<<"3. Best selling manufacturer" ;
	gotoxy(20,13) ;
	cout << "4. Bottom X selling product" ;
	gotoxy(20,14) ;
	cout << "5. Products set to expire within 1 week" ;
	gotoxy(20,15) ;
	cout<<"6. Return to main menu" ;
	gotoxy(20,17) ;
	cout<<"Enter a number (1-6): ";
	cin >> choice;
	return choice ; //controller checks if this is a valid choice, then calls stats functions (topX or...) accordingly
}

int UI::toplow(int ch)
{
	heading() ;
	int X;
	setcolor(15) ;
	cout<<"\n\nPlease enter the number of ";
	if(ch == 1)
		cout<<"top";
	else
		cout<<"lowest";
	cout<<" selling products you would like to see: ";
	cin >> X ;
	return X ;;
}
	
//controller calls this for choice=10, then calls successmessage(10) or failmessage(10) depending...
string UI::loaddata() 
{
	heading() ;
	string s ;
	setcolor(15) ;
	gotoxy(20,6) ;
	cout<<"You have chosen to load data from a file." ; 
	gotoxy(20,7) ;
	cout<<"Please enter the name of the file: ";
	cin>> s ; 
	return s ; //goes to controller 
}


//controller calls this for choice = 9 or successmessage(9) maybe instead, so we don't have to use this function??
void UI::listall()
{
	heading() ;
	gotoxy(20,6) ;
	setcolor(10) ;
	cout << "You have chosen to list all products." ;
	setcolor(15) ;
}

		
	
void UI::heading()

{
	system("cls") ;
	setcolor(10) ; //light green
	cout<<setw(75) <<setfill('*')<<'*' <<endl;
	setcolor(9) ; //light blue
	cout<<"*         CEG Hypermarket Inventory Control and Monitoring System         *"<<endl;
	setcolor(10) ;//lightgreen
	cout<<setw(75) <<setfill('*')<<'*' <<endl;
}



int UI::choicemenu()
{
	
	int choice ;
	gotoxy(20,12) ;
	std::cout << "1.Name" ;
	gotoxy(20,13) ;
	std::cout << "2.Category" ;
	gotoxy(20,14) ;
	std::cout << "3.Manufacturer" ;
	gotoxy(20,15) ;
	std::cout << "4.Barcode" ; 

	gotoxy(20,16) ;
	cout << "OR" ;
	gotoxy(20,17) ;
	cout << "5.Return to main menu" ;
	gotoxy(20,18) ;
	cout<< "Please enter your choice (1-5): ";
	cin >> choice;
	getchar();
	return choice ;
}


string UI::getattribute(int x) 
{
	setcolor(15) ;
	string s ;
	cout<<"\nEnter the ";
	
	 if(x==1)
		cout<<"name of the product(s) :  ";
	 else if(x == 2)
		cout<<"category of the product(s) :  ";
	 else if(x == 3)
		cout<<"manufacturer of the product(s) :  ";
	 cin >> s ;
	 return s ;
}

string UI::getattribute(int x, int & qty, string action) 
{
	setcolor(15) ;
	string s ;
	std::cout<<"\nEnter the ";
	
	 if(x==1)
		cout<<"name: ";
	 else if(x == 2)
		cout<<"category: ";
	 else if(x == 3)
		cout<<"manufacturer: ";
	 std::getline(cin,s) ;
	 //std::getline(cin,s) ;

	std::cout << "\nEnter the quantity to be " << action << " :  " ; 
	std::cin >> qty ;
	return s ;

	
}

int UI::getbarcode()
{
	setcolor(15) ;
	int code ;
	std::cout << "\nEnter the barcode: " ;
	std::cin >> code ;
	return code ;
}
//action is a string = either "added" or "sold"

int UI::getbarcode(int& qty, string action)
{
	setcolor(15) ;
	int code ;
	std::cout << "\nEnter the barcode: " ;
	std::cin >> code ;
	std::cout << "\nEnter the quantity to be " << action ;
	std::cin >> qty ; 

	return code;
}

void UI::quit(string username) //called by controller if choice= 7 
{
	heading() ;
	setcolor(12) ; //light red
	gotoxy(10,10) ;
	cout << "Logging user " << username <<  " out. Please wait while all your data is saved." ;
    gotoxy(10,11) ;
	system("PAUSE") ;
}