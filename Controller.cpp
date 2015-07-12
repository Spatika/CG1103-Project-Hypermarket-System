#include "Controller.h"

//main function in the controller class
void controller:: initiate(string username)
{
	int ch;
	do
	{
		ch = view.mainmenu();
		switch(ch)
		{
		case 1:
			menu1();
			break;
		case 2:
			search();
			break;
		case 3:
			stats();
			break;
		case 4:

			bool test ;
			test=load() ; //to load from whatever file you enter
			if(test) //if load from batchjobs has happened successfully
				process();
			break;
		case 5:
			Ob.pageprint();
			break;
		case 6:
			loaddata();
			break;
		case 7:
			break;
		default:
			view.setcolor(12) ;
			view.gotoxy(20,18) ;
			cout<<"Error!! Enter a valid operation";
			view.gotoxy(20,19) ;
			system("PAUSE") ;
		}

		if(ch != 7)
			_getch();
	}while(ch != 7);

	if(ch == 7)
		view.quit(username) ;

}



//function to control the pathways after selecting choice 1 in main menu
bool controller::menu1()
{
	int choice;
	choice = view.choice1();

	switch(choice)
	{
	case 1: return add();
		break;
	case 2: return del();
		break;
	case 3: return resetsales();
		break;
	case 4: return makesale();
		break;
	case 5: return stockup();
		break;
	case 6: return false ;
		break;
	default:
		view.setcolor(12) ;
		view.gotoxy(20,8) ;
		cout<<"ERROR!! Enter a valid option";
		view.gotoxy(20,9) ;
		system("PAUSE") ;
		view.setcolor(15) ;
		return menu1();
	}
}

//function to control the adding of a product and checking for possible errors
bool controller:: add()
{
	string name;
	string category,manu;
	int stock, code;
	float price;
	int sold;
	int d,m,y;
	float discount;

	//accepting the type of the product to be added
	int choice = view.addmenu();

	//input the details of the product depending on the choice of the user
	if(choice == 1 || choice == 2)
		{
			view.addproduct(choice, name, code, manu, price, category, stock, sold, discount,d,m,y);
		}

	//returning to the main menu without adding a product
	 else 
		 if(choice == 3)
				return false;
		 else 
			 //if user enters an invalid operation, calling the menu again
		 {
			view.setcolor(12) ;
			view.gotoxy(20,18) ;
			cout<<"Error!! Enter a valid operation";
			view.gotoxy(20,19) ;
			system("PAUSE") ;
			view.setcolor(15) ;
			return add();
		 }
		
	//checking for the existence of another product with the same barcode
	if(Ob.search(code) == true)
	{
		view.setcolor(12) ;
		
		cout<<"\nERROR!!! Barcode specified already exists!";
		view.gotoxy(20,9) ;
		system("PAUSE") ;
		view.setcolor(15) ;
		return add();
	}

	//without any errors adding the product
	if(choice == 1)
	{
		bool op = Ob.add(name, code, manu, price, category, stock,sold); //functionality add called if no errors
		if(op == true)
		{
			view.setcolor(10) ;
			cout<<"\n\nProduct added successfully!";
			view.setcolor(15) ;
		}
		else
		{
			view.setcolor(12) ;
			cout<<"\n\nSorry! Memory full; cannot add another product! :(";
			view.setcolor(15) ;
		}
		_getch() ;
	
		return op;		
	}
	else
	
		if(choice == 2)
		{
			bool op = Ob.add(name, code, manu, price, category, stock, sold, discount, d, m, y);
			if(op == true)
			{
				view.setcolor(10) ;
				cout<<"\n\nProduct added successfully!";
				view.setcolor(15) ;

			}
			else
			{
				view.setcolor(12) ;
				cout<<"\n\nSorry! Memory full; cannot add another product! :(";
				view.setcolor(15) ;
			}
			_getch();
			return op;
		}
	
}

//function to delete a particular product and check for the possible errors
bool controller:: del()
{
	int choice, code;
	string s;
	view.setcolor(15) ;

	//call function in UI for the submenu which gives the category based on which the deletion is supposed to be performed
	choice = view.Delete();

	//choice = 5 is to return to the main menu
	if(choice == 5)
		return true;
	else
		//delete by barcode
		if(choice == 4)
		{
			code = view.getbarcode();
			if(Ob.search(code) == false)
			{
				view.setcolor(12) ;
				cout<<"\n\nERROR!!! No product with the given barcode exists";
				view.setcolor(15) ;
				_getch();
				return del();
			}
			else
			{
				//barcode exists and delete the product
				bool ch = Ob.scrap(code);
				if(ch == true)
				{
					view.setcolor(10) ;
					cout<<"\n\nProduct(s) deleted!";
					view.setcolor(15) ;
				}
				else
				{
					view.setcolor(10) ; 
					cout<<"\n\nNo product has been deleted.";
					view.setcolor(15) ;
				}
				_getch();
				return true;
			}
		}
		else
			//delete by name, category of manufacturer
			if(choice >=1 && choice <=3)
			{
				s = view.getattribute(choice);
				bool ch = Ob.scrap(s, choice);
				if(ch == true)
					cout<<"\n\nProduct(s) deleted! ";
				else
					cout<<"\n\nNo product has been deleted";
				_getch();
				return true;
			}
			else
				//when an invalid option has been choosen, then calling the del()
			{
				view.setcolor(12) ;
				cout<<"\n\t\t    Please enter a valid option!";
				view.setcolor(15) ;

				cout<<"\n\nPlease enter a valid option!";
				_getch();
				return del();
			}
}


//function to reset all the product sales to zero
bool controller::resetsales()
{
	//creating a new screen
	view.reset();
	view.setcolor(15) ;

	//resetting all the sales
	Ob.reset();

	view.setcolor(10) ;
	cout << "\n\t\t    Sales successfully reset to 0 for all products!" ;
	view.setcolor(15) ;

	return true;
}


//function to control the execution the sales of a product
bool controller::makesale()
{
	int choice = view.sell();
	view.setcolor(15) ;

	//choice corresponding to return to menu option
	if(choice == 5)
		return true;
	else
		//chose to make sale by barcode
		if(choice == 4)
		{
			int qty;
			int code = view.getbarcode(qty,"sold");

			if(Ob.search(code) == false)
			{
				view.setcolor(12) ;
				cout<<"\n\nERROR!!! No product with the given barcode exists";
				view.setcolor(15) ;
				_getch();
				return makesale();
			}

			else
			{
				if(Ob.obtstock(code) >= qty)
					return Ob.sale(code,qty);
				else
				{
					view.setcolor(12) ;
					cout<<"\n\nNot enough stock for this product";
					view.setcolor(15) ;
				}
				return false;
			}
		}
		//chose to make sale by name or category or manufacturer
		if(choice>=1 && choice <= 3)
		{
			int qty;
			string s;

			getline(cin,s);
			s = view.getattribute(choice, qty, "sold");

			return Ob.sale(s, choice, qty);
		}
		else
			//invalid operation choosen
		{
			view.setcolor(12) ;
			cout<<"\n\t\t    Please enter a valid option!";
			view.setcolor(15) ;
			 _getch();
			return makesale();
		}
}


//funtion to control the restocking of products
bool controller::stockup()
{
	int choice = view.restock();
	view.setcolor(15) ;

	//choice corresponding to return to menu option
	if(choice == 5)
		return true;
	else
		//chose to restock by barcode
		if(choice == 4)
		{
			int qty;
			int code = view.getbarcode(qty,"restocked");

			if(Ob.search(code) == false)
			{
				view.setcolor(12) ;
				cout<<"\n\nERROR!!! No product with the given barcode exists";
				view.setcolor(15) ;
				_getch();
				return stockup();
			}

			else
				return Ob.restock(code,qty);
		}
		//chose to make sale by name or category or manufacturer
		if(choice>=1 && choice <= 3)
		{
			int qty;
			string s;

			
			getline(cin,s);
			s = view.getattribute(choice, qty, "restocked");

			return Ob.restock(s, choice, qty);
		}
		else
			//invalid operation choosen
		{
			view.setcolor(12) ;
			cout<<"\n\t\t    Please enter a valid option!";
			view.setcolor(15) ;
			 _getch();
			return stockup();
		}
}



//function help user to search for particular products
bool controller::search()
{
	int choice = view.searchmenu();
	//1-name 2-category 3-manufacturer 4-barcode 5-check if product has expired
	view.setcolor(15) ;

	if(choice < 1 || choice >6)
	{
		view.setcolor(12) ;
		cout<<"\n\nERROR!! Input a valid operation"; 
		view.setcolor(15) ;
		_getch();
		return search();
	}

	else
		if(choice == 6)
			return false;
		else
			if(choice >= 1 && choice<=3)
			{
				string s;
				if(choice == 1)
				cout<<"\nEnter the name of the product(s) to be searched\t: ";
				else
					if(choice == 2)
						cout<<"\nEnter the category of the product(s) to be searched\t: ";
					else
						cout<<"\nEnter the manufacturer of the product(s) to be searched\t: ";
				getline(cin, s);
				getline(cin, s);

				//cin>>s;
				Product** P = new Product*[Ob.length()];;
				cout<<endl;
				int size = Ob.search(s,choice,P);

				if(size == 0)
				{
					view.setcolor(12) ;
					cout<<"\n\nERROR!! No such product(s) exist";
					view.setcolor(15) ;
				}
				else
					for(int i=0; i<size; i++)
					{
						cout<<"\nProduct "<<i+1<<" : "; 
						P[i]->printproduct();
						cout << endl;
					}

				delete [] P;
			}
			else
				if(choice == 4)
				{
					cout<<"Enter the barcode of the product(s) to be searched\t: ";
					int code;
					cin>>code;
					cout<<endl;
					bool ch = Ob.search(code);

					if(ch == false)
					{
						view.setcolor(12) ;
						cout<<"\n\nERROR!! No such product of this barcode exists!";
						view.setcolor(15) ;
					}
					else
					{
						Product* P;
						Ob.search(code,P);
						P->printproduct();
					}
				}
				else
					checkexpire();

	//need to allow changes here


	return true;
}


//function to control the checking of the expiry of a product
bool controller::checkexpire()
{
	view.setcolor(15) ;
	int ch,a;
	a = view.checkexpired();
	string s;
	int code;

	if(a > 0 && a<4)
	{
		view.setcolor(15) ;
		s=view.getattribute(a) ;
		
	}
	else
		if(a == 4)
		{
			view.setcolor(15) ;
			cout << "\n\nEnter the barcode: " ;
			cin>>code;
		}
		else
			if(a == 5)
				return true;
			else
			{
				view.setcolor(12) ;
				cout<<"\n\nERROR!! Please choose a correct choice.";
				view.setcolor(15) ;
				return checkexpire();
			}

	if(a == 4)
		ch = Ob.IfExpired(code);
	else
		ch = Ob.IfExpired(s,a);

	if(ch == 0)
	{
		view.setcolor(12) ;
		cout<<"\n\nERROR!! Such a product does not exist or it is not a perishable product";
		view.setcolor(15) ;
		return false;
	}
	else
		if(ch == 1)
		{
			
			return true;
		}
		else
		{
			cout<<"\n\nThe product has not expired.";
			return false;
		}
}


//function to control the generation of statistics
bool controller::stats()
{
	int choice = view.statsmenu();

	if(choice == 6)
		return true;
	else
		if(choice == 1)
		{
			int x = view.toplow(1);

			//x is greater than the number of products
			if(x > Ob.getnop())
			{
				view.setcolor(12) ;
				cout<<"\n\nERROR!! There do not exist "<<x<<" products in the inventory";
				cout << endl ;
				system("PAUSE") ;
				view.setcolor(15) ;
				
				return stats();
			}
			else
				return Ob.topsales(x);
		}

		else
			if(choice == 2)
			{
				string s;
				cout<<"\n\nEnter the category under which the best product is to be searched :";
				cin>>s;
				return Ob.ctop(s);
			}
			else 
				if(choice == 3)
					return Ob.mtop();
				else
					if(choice == 5)
					{
						bool ch = Ob.expire();
						if(ch == false)
						{
							view.setcolor(12) ;
							cout<<"\n\nThere are no products which expire in a week";
							view.setcolor(15) ;
							_getch();
						}
						return ch;
					}
					else
						if(choice == 4)
						{
							int x = view.toplow(2);

							//x is greater than the number of products
							if(x > Ob.getnop())
							{
								view.setcolor(12) ;
								cout<<"\n\nERROR!! There do not exist "<<x<<" products in the inventory. ";
								cout << endl ;
								system("PAUSE") ;
								view.setcolor(15) ;
								return stats();
							}
							else
								return Ob.botsales(x);
						}
						else
						{
							view.setcolor(12) ;
							cout<<"\n\nInvalid choice of operation";
							view.setcolor(15) ;

							_getch();
							return stats();
						}
}



//function to control the loading of data from a file
void controller::loaddata()
{
	string s;
	s = view.loaddata();
	bool ch = Ob.loaddata(s); //functionality loaddata 
	if(ch == true)
	{
		view.setcolor(10) ;
		view.gotoxy(20,12) ;
		cout<<"File successfully read from!";
		view.setcolor(15) ;
		
	}

}



bool controller::load() //load data from batchjobs.txt
{
	view.heading() ;
	view.setcolor(10) ;
	view.gotoxy(15,6) ;
	cout<<"Batch Processing";
	view.gotoxy(15,7) ;
	cout<<"Enter the name of the file from which the jobs are to be read: ";
	view.gotoxy(15,8) ;
	string s;
	cin>>s;
	ifstream fin(s);
	if(fin == NULL)
	{
		view.setcolor(12) ; //light red
		view.gotoxy(20,9) ; 
		cout<<"No such file exists!";
		view.setcolor(15) ;
		return false;
	}
	else
	{
		int num = 0, count = 0;
		string action, worker, name, cat, manu;
		int bc, stock, date;
		double price;
		char x;

		fin>>num;

		for(int i=0; i<num; i++)
		{
			fin.get(x); //for newline 
			getline(fin, worker); //getline don't need to do get(x) after...

			Submission newsub;
			newsub.name = worker;
			newsub.Qptr = new QueueLL<Job*>;

			fin>>count; //no of jobs 
			
			for(int j=0; j<count; j++)
			{
				fin.get(x); //for newline
				getline(fin, action);
				if(action == "ADD")
				{
					getline(fin, name);
					getline(fin, cat);
					fin>>bc;
					fin>>price;
					fin.get(x);
					getline(fin, manu);
					fin>>stock;

					Job* newjob = new Job(action, name, cat, bc, price, manu,stock);
					newsub.Qptr->enqueue(newjob);

				}
				else
					if(action == "DELETE")
					{
						fin>>bc;
						Job* newjob = new Job(action, bc);
						newsub.Qptr->enqueue(newjob);
					}
					else
						if(action == "RESTOCK")
						{
							fin>>bc;
							fin>>stock;
							Job* newjob = new Job(action, bc, stock);
							newsub.Qptr->enqueue(newjob);
						}
						else
							if(action == "SALE")
							{
								fin>>bc;
								fin>>stock;
								Job* newjob = new Job(action, bc, stock);
								newsub.Qptr->enqueue(newjob);
							}
							else //action is DISPOSE of expired products, i.e. stock=0 
							{
								fin>>bc;
								fin>>date;
								Job* newjob = new Job(action, bc, date);
								newsub.Qptr->enqueue(newjob);
							}
			}

			WhoseTurn.push(newsub);
		
		}
		fin.close();
		return true;
		
	}
}


void controller::process()
{	
	ofstream fout("log.txt"); //error jobs overwritten when batchjobs processed more than once...
	int counter = 0 ;
	int size1 = WhoseTurn.size(); //the Stack of Submission structs -> each has a name and a ptr to a QueueLL of Job pointers

	for(int i = 0; i<size1; i++)
	{
		Submission cur;
		cur.name =  '0';//
		cur.Qptr= NULL;//
		WhoseTurn.getTop(cur);

		int size2 = cur.Qptr->getSize();

		for(int j = 0; j < size2; j++)
		{
			bool check = true ;
			Job* cur2 = NULL;
			cur.Qptr->getFront(cur2);
		
			if(cur2->getAction() == "ADD") 
			{
				check = Ob.search(cur2->getBar()); //check if the barcode exists
				if(check == false)
				{
					Ob.add(cur2->getName(), cur2->getBar(), cur2->getMan(), cur2->getPrice(), cur2->getCat(), cur2->getStock(),0); //call add() which calls insert()
					check = true;
				}
				else
					check = false;
			}
			else
				if(cur2->getAction() == "DELETE")
				{
					check = Ob.batchscrap(cur2->getBar()); //why not check, using search and then call scrap by barcode which in turn calls remove
				}
				else
					if(cur2->getAction() == "RESTOCK")
					{
						check = Ob.search(cur2->getBar());
						if(check == true)
							check = Ob.batchrestock(cur2->getBar(), cur2->getStock()) ;
					
							
					}
					else
						if(cur2->getAction() == "SALE")
						{
							check = Ob.search(cur2->getBar());
							if(check == true)
								if(Ob.obtstock(cur2->getBar()) > cur2->getSale()) //there should be stock available for the given barcode greater than that to be sold...
									Ob.batchsale(cur2->getBar(), cur2->getStock());
								else
									check = false;
						}

						else //should reset stock to 0!! 
						{
							check = Ob.batchIfExpired(cur2->getBar(),cur2->getDate());
							if(check == true)
							{
							 //reset stock of product to zero in the list!!
								Ob.batchreset(cur2->getBar()) ;
							}
							else
								check = false ;
						}

			if(check == false)
			{
				fout<< cur2->getBar() << " " << cur2->getAction() << " " << cur.name << endl;
				counter++;
			}

			cur.Qptr->dequeue(cur2);

		}
		WhoseTurn.pop(cur); //you would've popped everything..but still not deleted the dynamic array??
	}
	
	fout.close();
	view.heading() ;
	view.gotoxy(15,6) ;
	view.setcolor(10) ;
	cout<<"Batch processing was successful. ";
	view.gotoxy(15,7) ;
	if(counter > 0)
	{
		cout << counter << " errors were detected." ; 
		view.gotoxy(15,8) ;
		cout << "Please open the file log.txt to view the errors." ;
	}

	else
	{
		cout<<"All jobs were completed successfully and no errors were detected.";
	}
	view.setcolor(15) ; //white
}
