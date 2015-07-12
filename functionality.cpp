#include "functionality.h"
#include "windows.h" 

template <typename T>
void functionality<T>::setcolor(unsigned int color) 
{                                    
    if (color >15 || color <=0)
    {
        cout <<"Error" <<endl;
        
    }
    else
    {    
        HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hcon,color);
		
    }
} 
template <typename T>
int functionality<T>::length()
{
	return ob.getLength();
}

template <typename T>
functionality<T> ::~functionality()
{
	writedata();
}

 template <typename T> 
bool functionality<T> :: add(string name, int code, string manu, double price, string category, int stock, int sold)
{
	//create new product pointer
	Product* P = new Product(name, code, manu, price, category, stock, sold);

	//insert into list ob - is object of type dynamic array
	return ob.insert(P) ;
}

template <typename T> 
bool functionality<T> :: add(string name, int code, string manu, double price, string category, int stock, int sold, double x, int d, int m, int y)
{
	//create new product pointer that points to perishable object
	Product* P = new Perishables(name, code, manu, price, category, stock, sold, x, d, m, y);

	// insert into list
	return ob.insert(P);
}


template <typename T> 
bool functionality<T> :: scrap(int code)
{
	Product* P;

	//find index of product with that barcode in the list
	int index = search(code, P);
	
	//no such product exists
	if(index == -1)
	{
		setcolor(12) ;
		cout<<"\nNo such product with the specified barcode exists";
		setcolor(15) ;
		return false;
	}
	else
	{
		//display details of product
		cout<<"\n\nDetails of the product you have choosen to delete\t:";
		P->printproduct(); cout<<endl;

		//check if user really wants to delete it
		cout<<"\n\nDo you want to proceed to delete this product(y\\n)\t:\t";
		char ch;
		cin>>ch;
		if(ch == 'y' || ch == 'Y') 
		{
			//remove the product
			ob.remove(index);
			return true;
		}
		return false;
	}
}

template <typename T> 
bool functionality<T> ::scrap(string s, int ch)
{
	// create new array OF PRODUCT POINTERS the same size as your dynamic array of product pointers
	Product** P = new Product*[ob.getLength()];

	//search for all products with the name(1) or manufacturer(3) or category(2)
	int num = search(s, ch, P); //passed by reference
	
	if(num == 0)
	{
		setcolor(12) ;
		cout<<"\nNo product with the given specifications exists";
		setcolor(15) ;
		return false;
	}
	else
	{
		//display to user all the details of the products
		cout<<"\n"<<num<<" occurrences of related products have been found";
		for(int i=0; i<num; i++)
		{
			if(num > 1)
				cout<<"\n\nDetails of the product "<<i+1<<" you have choosen to delete\t:";
			else
				cout<<"\n\nDetails of the product you have choosen to delete\t:";
			P[i]->printproduct(); cout<<endl;
		}
		// if there are more than one products 
		if(num>1)
		{
			// let user choose if he wants to delete one or delete all
			cout<<"\n\n1.Delete all\n2.Delete one of the products shown\nEnter your choice of operation\t:\t";
			int choice;
			cin>>choice;
			//if want to delete all
			if(choice == 1)
			{
				//make sure 
				cout<<"\n\nAre you sure you want to delete all(y\\n)\t:\t";
				char ch;
				cin>>ch;
				if(ch == 'y' || ch == 'Y') 
				{
					//loop to delete all products
					for(int i=0 ; i<num; i++)
					{
						Product *P1;
						int index = search(P[i]->getBarcode(), P1); //2nd kind of search to search for index passed
						ob.remove(index);
					}
					return true;
				}

				if(ch == 'n' && num > 1)
					cout<<"\nYou are advised to refine your search by using the barcode or another form of search";
				return false;
			}
			//if delete only one
			else
			{
				//ask user to input number of product shown on which the operation is to performed
				cout<<"\n\nEnter the product number to be deleted\t:\t";
				cin >> choice;
				choice -= 1;
				Product *P1;

				//find index and then delete
				int index = search(P[choice]->getBarcode(), P1);
				ob.remove(index);
				return true;
			}
		}
		// if there is only one product
		else
		{
			// confirm with user
			cout<<"\n\nAre you sure you want to delete the product(y\\n)\t:\t";
			char ch;
			cin>>ch;

			//delete
			if(ch == 'y' || ch == 'Y') 
			{
				Product *P1;
				int index = search(P[0]->getBarcode(), P1);
				ob.remove(index);
				return true;				
			}
		}
		
	}

	delete []P;
}


template <typename T> 
void functionality<T> ::reset()
{
	int max = ob.getLength();
	Product* P = NULL;
	bool ch;

	//retrieve products one by one and reset
	for(int i=0; i<max; i++)
	{
		ch = ob.retrieve(i, P);
		if(ch == true)
			P->Reset();
	}
}


template <typename T> 
bool functionality<T> :: restock(int code, int qty)
{
	Product* P;
	//find index of the product in list
	int index = search(code, P);
	
	//invalid index, no such product
	if(index == -1)
	{
		setcolor(12) ;
		cout<<"\nNo such product with the specified barcode exists";
		setcolor(15) ;
		return false;
	}
	else
	{
		//display details
		cout<<"\n\nDetails of the product you have choosen to restock\t:";
		P->printproduct(); cout<<endl;

		//confirm with user
		cout<<"\n\nDo you want to proceed to restock the product(y\\n)\t:\t";
		char ch;
		cin>>ch;

		//restock product
		if(ch == 'y' || ch == 'Y') 
		{
			P->restock(qty);
			return true;
		}
		return false;
	}
}


template <typename T> 
bool functionality<T> ::restock(string s, int ch, int qty)
{
	//create new array
	Product** P = new Product*[ob.getLength()];

	//search for all products with the name or manufacturer or category
	int num = search(s, ch, P);
	
	//when there isnt any product with the specified details
	if(num == 0)
	{
		setcolor(12) ;
		cout<<"\nNo such product with the specified barcode exists";
		setcolor(15) ;
		return false;
	}
	else
	{
		cout<<"\n"<<num<<" occurrences of related products have been found";
		for(int i=0; i<num; i++)
		{
			if(num>1)
				cout<<"\n\nDetails of the product "<<i+1<<" you have choosen to restock\t:";
			else
				cout<<"\n\nDetails of the product you have choosen to restock\t:";
			P[i]->printproduct(); cout<<endl;

		}

		//when there are nore than one products with the same specification
		if(num>1)
		{
			cout<<"\n\n1.Restock all\n2.Restock one by one\nEnter your choice of operation\t:\t";
			int choice;
			cin>>choice;
			if(choice == 1)
			{
				//confirming with the user
				cout<<"\n\nAre you sure you want to restock all(y\\n)\t:\t";
				char ch;
				cin>>ch;
				if(ch == 'y' || ch == 'Y') 
				{
					for(int i=0; i<num; i++)
						P[i]->restock(qty);
					return true;
				}

				if(ch == 'n' && num>1)
					cout<<"\nYou are advised to refine your search by using the barcode or another form of search";
				return false;
			}	
			else if(choice == 2)
			{
				//asking the user for the product on which the operation is to performed
				cout<<"\n\nEnter the product number to be restocked\t:\t";
				cin>>choice;
				choice -= 1;
				P[choice]->restock(qty);
				return true;
			}
		}
		else
		{
			//confirming with the user
			cout<<"\n\nAre you sure you want to restock the product(y\\n)\t:\t";
			char ch;
			cin>>ch;
			if(ch == 'y' || ch == 'Y') 
			{
				P[0]->restock(qty);
				return true;				
			}
		}
		
	}
	delete []P;
}


//function to print the entire list of products
template <typename T> 
void functionality<T> ::print()
{
	int max = ob.getLength();
	Product* P = NULL;
	bool ch;

	for(int i=0; i<max; i++)
	{
		ch = ob.retrieve(i, P);
		if(ch == true)
		{
			P->printproduct(); cout<<endl;
		}
	}
}



//print in pages
template <typename T> 
void functionality<T> ::pageprint()
{
	 
	int max = ob.getLength();
	if(max == 0)
	{
		setcolor(12) ;
		cout << "\n\nNo products currently in inventory!" ;
		setcolor(15) ;
		return ;
	}
	Product* P = NULL;
	bool ch;
	int count=0;
	char command;
	for(int i=0; i<max; i++)
	{
		ch = ob.retrieve(i, P);
		if(ch == true)
		{
			P->printproduct();
			cout<<endl;
			count++;
			if(i+1==max)
				count=10;
			if(count ==10)
			{
				count=0;
				if(i+1==max)
				{
					cout<<"\nPlease press enter to end"<<endl;
					cout<<"Please press backspace to go to prev page"<<endl;
					cout<<"Please press escape+enter to quit displaying"<<endl;
				}
				else
				{
					if(i+1==10)
					{
						cout<<"\nPlease press enter to go to next page"<<endl;
						cout<<"Please press escape+enter to quit displaying"<<endl;
					}
					else
					{
						cout<<"\nPlease press enter to go to next page"<<endl;
						cout<<"Please press backspace to go to prev page"<<endl;
						cout<<"Please press escape+enter to quit displaying"<<endl;
					}
				}

				command=getch();
				//please like put the command !=13 into error handling portion
				if(command == 8)
				{
					if(max%10==0)
						i-=20;
					else
					{
						i-=((max%10)+10);
					}
				}
				else
				{
					if(command==27)
						break;
					else
						if(command !=13)
						{
							cout<<"Please press enter/backspace/escape !!"<<endl;
							i-=10;
						}
				}

				system("cls");
			}
		}
	}
}


//function to execute the sale of a product with the specified barcode
template <typename T> 
bool functionality<T> ::sale(int code, int qty)
{
	Product* P;
	int index = search(code, P);
	
	//when no such product exists
	if(index == -1)
	{
		setcolor(12) ;
		cout<<"\nNo such product with the specified barcode exists";
		setcolor(15) ;
		return false;
	}
	else
	{
		cout<<"\n\nDetails of the product you have choosen to make a sale\t:";
		P->printproduct(); cout<<endl;

		//confirming with the user about the operation
		cout<<"\n\nDo you want to proceed with the sale of the product(y\\n)\t:\t";
		char ch;
		cin>>ch;
		if(ch == 'y' || ch == 'Y') 
		{
			P->addSold(qty);
			return true;
		}
		return false;
	}
}


//function to perform the corresponding sale operations
template <typename T> 
bool functionality<T> ::sale(string s, int x, int qty)
{
	Product** P = new Product*[ob.getLength()];
	int num = search(s, x, P);
	
	if(num == 0)
	{
		setcolor(12) ;
		cout<<"\nNo such product with the specified details exist";
		setcolor(15) ;
		delete []P;
		return false;
	}
	else
	{
		cout<<"\n"<<num<<" occurrences of related products have been found";
		for(int i=0; i<num; i++)
		{
			if(num>1)
				cout<<"\n\nDetails of the product "<<i+1<<" you have choosen to sell\t:";
			else
				cout<<"\n\nDetails of the product you have choosen to sell\t:";
			P[i]->printproduct(); cout<<endl;

		}

		//when there are nore than one products with the same specification
		if(num>1)
		{
			cout<<"\n\n1.Sell all\n2.Sell one by one\nEnter your choice of operation\t:\t";
			int choice;
			cin>>choice;
			if(choice == 1)
			{
				//confirming with the user
				cout<<"\n\nAre you sure you want to sell the same quantity of all(y\\n)\t:\t";
				char ch;
				cin>>ch;
				if(ch == 'y' || ch == 'Y') 
				{
					for(int i=0; i<num; i++)
					{
						if(P[i]->getStock() >= qty)
							P[i]->addSold(qty);
					}

					delete []P;
					return true;
				}

				if(ch == 'n' && num>1)
					cout<<"\nYou are advised to refine your search by using the barcode or another form of search";

				delete []P;
				return false;
			}	
			else if(choice == 2)
			{
				//asking the user for the product on which the operation is to performed
				cout<<"\n\nEnter the product number to be sold\t:\t";
				cin>>choice;
				choice -= 1;
				if(P[choice]->getStock() >= qty)
				{
					P[choice]->addSold(qty);
					delete []P;
					return true;
				}
				else
				{
					cout<<"\n\nNot enough stock to sell this product";
					delete []P;
					return false;
				}
				
			}
		}
		else
		{
			//confirming with the user
			cout<<"\n\nAre you sure you want to sell the product(y\\n)\t:\t";
			char ch;
			cin>>ch;
			if(ch == 'y' || ch == 'Y') 
			{
				if(P[0]->getStock() >= qty)
				{
					P[0]->addSold(qty);
					delete []P;
					return true;
				}
				else
				{
					cout<<"\n\nNot enough stock to sell this product";
					delete []P;
					return false;
				}
			}
		}
		
	}
	
}


//function to load the data from a file 
template <typename T> 
bool functionality<T> ::loaddata(string s)
{
	ifstream fin(s);
	if(fin == NULL)
	{
		setcolor(12) ;
		cout<<"\n\t\t    No such file exists!!";
		setcolor(15) ;
		return false;
	}
	else
	{
		int num = 0, i = 0;
		char ch;
		string name, category, manu;
		int code, stock, sold;
		double price;
		float discount;
		int d, m, y;
		char x;

		fin>>num;

		//reading all the data required for the num products in the file
		for(i=0; i<num; i++)
		{
			fin>>ch;
			fin.get(x);
			getline(fin, name);
			getline(fin, category);
			fin>>code; fin.get(x);
			fin>>price; fin.get(x);
			getline(fin, manu);
			fin>>stock; fin.get(x);
			fin>>sold; fin.get(x);

			if(ch == 'y')
			{
				fin>>d; //this is integer being converted as it's loaded to struct Date
				y = d%10000;
				d /= 10000;
				m = d%100;
				d = d/100;
				fin>>discount;

				//ensuring only unique coded products are added
				if(search(code) == false)
					add(name, code, manu, price, category, stock, sold, discount, d, m, y);
			}
			else
				//ensuring only unique coded products are added
				if(search(code) == false)
					add(name, code, manu, price, category, stock, sold);
		}

		
		return true;
		fin.close();
	}
}


//function to display the best selling product in a particular category
template <typename T> 
bool functionality<T> ::ctop(string s)
{
	Product** P = new Product*[ob.getLength()];

	//searching for all the products of the category
	int num = search(s,2,P);

	if(num == 0)
	{
		setcolor(12) ;
		cout<<"\n\nThere does not exist any product belonging to this category";
		setcolor(15) ;
		return false;
	}
	else
	{
		double revenue = 0;
		int index = -1, i;

		for(i=0; i<num; i++)
		{
			if(P[i]->getPrice() * P[i]->getSold() > revenue)
				{
					revenue = P[i]->getPrice() * P[i]->getSold();
					index = i;
				}
		}

		if(index == -1)
		{
			cout<<"\n\nThere haven't been any sales to find the top product in this category";
			return false;
		}

		Product* P1 = P[index];
		cout<<"\n\nDetails of the top selling product in the category "<<s<<" is \t:";
		P1->printproduct(); cout<<endl;
		return true;
	}

	delete []P;
}


//generate top x selling products
template <typename T> 
bool functionality<T> ::topsales(int x)
{
	setcolor(15) ;
	//returns an error when there are lesser products than the number of top products asked by the user
	if(x > ob.getLength())
		return false;

	ofstream fout("TopSeller.txt");

	Product* *newarray = new Product*[ob.getLength()];
	Product* p;
	int counter = 0;

	//put all products into new array
	for(int i=0; i<ob.getLength(); i++)
	{
		ob.retrieve(i, p);
		newarray[i] = p;
	}

	int index, previndex = -1;

	cout << "\nTop " << x << " selling products: " << endl;
	cout << endl;

	//run loop x times
	for(int i=0; i<x; i++)
	{
		double max = 0;

		//find index of max revenue product
		while(1)
		{
			for(int j=0; j<ob.getLength(); j++)
			{
				if(newarray[j] != NULL && newarray[j]->getSold()*newarray[j]->getPrice() >= max && newarray[j]->getSold()*newarray[j]->getPrice() != 0)
				{
					max = newarray[j]->getSold()*newarray[j]->getPrice();
					index = j;
				}
			} 

			//if index is same as previous run index, for loop did not change anything
			if(index == previndex)
				break;

			//if different then there is a product with same revenue as previous
			previndex = index;

			counter=i+1;

			// print out details
			cout << "Number " << i+1 << " selling product:" << endl;
			cout << "Total revenue: $" << max << endl;
			cout << "Product Name: " << newarray[index]->getName() << endl;
			cout << "Barcode Number: " << newarray[index]->getBarcode() << endl;
			cout << "Category: " << newarray[index]->getCategory() << endl;
			cout << "Manufacturer: " << newarray[index]->getManu() << endl;
			cout << endl;

			fout << "Number " << i+1 << " selling product:" << endl;
			fout << "Total revenue: $" << max << endl;
			fout << "Product Name: " << newarray[index]->getName() << endl;
			fout << "Barcode Number: " << newarray[index]->getBarcode() << endl<<endl;
			fout << endl;

			//set the index of the product to be NULL since it has been printed already
			newarray[index] = NULL;
		}
	}

	cout << "Press enter to return to main menu." << endl;

	if(counter < x)
	{
		setcolor(12) ;
		cout << "Only Top "<< counter << " product(s) are available as the other products have not been sold. " << endl;
		setcolor(15) ;
	}
	delete [] newarray;

	fout.close();

	return true;
}


template <typename T> 
bool functionality<T> ::botsales(int x)
{
	setcolor(15) ;
	//returns an error when there are lesser products than the number of top products asked by the user
	if(x > ob.getLength())
		return false;

	ofstream fout("BottomSeller.txt");

	Product* *newarray = new Product*[ob.getLength()];
	Product* p;
	int counter = 0;

	//put all products into new array
	for(int i=0; i<ob.getLength(); i++)
	{
		ob.retrieve(i, p);
		newarray[i] = p;
	}

	int index, previndex = -1;

	cout << "\nBottom " << x << " selling products: " << endl;
	cout << endl;

	//run loop x times
	for(int i=0; i<x; i++)
	{
		double min = newarray[0]->getPrice()*newarray[0]->getSold();

		//find index of max revenue product
		while(1)
		{
			for(int j=0; j<ob.getLength(); j++)
			{
				if(newarray[j] != NULL && newarray[j]->getSold()*newarray[j]->getPrice() <= min)
				{
					min = newarray[j]->getSold()*newarray[j]->getPrice();
					index = j;
				}
			} 

			//if index is same as previous run index, for loop did not change anything
			if(index == previndex)
				break;

			//if different then there is a product with same revenue as previous
			previndex = index;

			counter=i+1;

			// print out details
			cout << "Number " << i+1 << " lowest selling product:" << endl;
			cout << "Total revenue: $" << min << endl;
			cout << "Product Name: " << newarray[index]->getName() << endl;
			cout << "Barcode Number: " << newarray[index]->getBarcode() << endl;
			cout << "Category: " << newarray[index]->getCategory() << endl;
			cout << "Manufacturer: " << newarray[index]->getManu() << endl;
			cout << endl;

			fout << "Number " << i+1 << " lowest selling product:" << endl;
			fout << "Total revenue: $" << min << endl;
			fout << "Product Name: " << newarray[index]->getName() << endl;
			fout << "Barcode Number: " << newarray[index]->getBarcode() << endl<<endl;

			//set the index of the product to be NULL since it has been printed already
			newarray[index] = NULL;
		}
	}

	cout << "Press enter to return to main menu." << endl;

	if(counter < x)
	{
		setcolor(12) ;
		cout << "Only Bottom "<< counter << " product(s) are available as the other products have not been sold. " << endl;
	    setcolor(15) ;
	}
	delete [] newarray;

	fout.close();
	return true;
}

//function to generate the top selling manufacturer
template <typename T> 
bool functionality<T> ::mtop()
{
	setcolor(15) ;
	if(ob.getLength() == 0)
	{
		cout<<"\nThere are no products in the inventory system";
		return false;
	}

	int n = 0, num = ob.getLength();

	//creating a dynamic array where the names of manufacturers and their revenues are stored
	manu* S = new manu[num];

	for( int i=0; i<num; i++)
	{
		Product* P;
		ob.retrieve(i,P);

		int j = 0, flag = 0;
		while(j<n)
		{
			if(S[j].name == P->getManu())
			{
				flag = 1;
				S[j].rev += P->getPrice() * P->getSold();
			}

			j++;
		}

		//in case the name of the manufacturer has not been previously added to the list of names
		if(flag == 0 && n!=0)
		{
			S[n].name = P->getManu();
			S[n].rev = P->getSold() * P->getPrice();
			n++;
		}

		//for the first manufacturer
		if(n == 0)
		{
			S[0].name = P->getManu();
			S[0].rev = P->getSold() * P->getPrice();
			n = 1;
		}

	}

	int index = 0;
	for(int i=0; i<n; i++)
	{
		if(S[i].rev > S[index].rev)
			index = i;
	}

	//in case none of the manufacturers have made any sale yet
	if(S[index].rev == 0) 
	{
		delete []S;
		return false;
	}

	cout<<"\n\nThe top manufacturer is \t:\t"<<S[index].name;
	cout<<"\n\nThe revenue collected by the top manufacturer is : "<<S[index].rev;

	//deleting the dynamic array created
	delete []S;
	return true;
}


//function to generate a list of products expiring within the week
template <typename T>
bool functionality<T> ::expire()
{
	setcolor(15) ;
	bool ch = false;

	if(ob.getLength() == 0)
		return false;
	ofstream fout("expire.txt");
	time_t t = time(0); // get time now
	time_t _week =t+604800; //1 week time from now
	struct tm *now =localtime(&t);

	fout<<"Products expiring within a week from "<<now->tm_mday<<"/"<<now->tm_mon+1<<"/"<<now->tm_year+1900;
	now=localtime(&_week);
	fout<<" to "<< now->tm_mday<<"/"<<now->tm_mon+1<<"/"<<now->tm_year+1900<<endl<<endl;
	for( int i=0; i<ob.getLength(); i++)
	{
		Product* P;
		ob.retrieve(i,P);
		Date d;
		if(P->producttype()=='y')
		{
			d=P->getDate();
			struct tm *timeinfo=localtime(&t);
			time_t rawtime;
			timeinfo->tm_year=d.year-1900;
			timeinfo->tm_mon=d.month-1;
			timeinfo->tm_mday=d.day;
			rawtime=mktime(timeinfo);//expiry date of product
			if(rawtime >=t && rawtime<= _week)
			{
				ch = true;

				cout << "Product Name: " << P->getName() << endl;
				cout << "Barcode Number: " << P->getBarcode() << endl;
				cout << "Category: " << P->getCategory() << endl;
				cout << "Manufacturer: " << P->getManu() << endl;
				cout << "Expiry date: "<<d.day<<"/"<<d.month<<"/"<<d.year<<endl;
				if(((rawtime-t)/(24*60*60))==0)
					cout<<"Product is expiring Today!!!"<<endl;
				else
					cout<<"Product is expiring in "<<(rawtime-t)/(24*60*60)<< "day(s)"<<endl;
				cout << endl;
				
				fout << "Product Name: " << P->getName() << endl;
				fout << "Barcode Number: " << P->getBarcode() << endl;
				fout << "Category: " << P->getCategory() << endl;
				fout << "Manufacturer: " << P->getManu() << endl;
				fout << "Expiry date: "<<d.day<<"/"<<d.month<<"/"<<d.year<<endl<<endl;
			}
		}

	}
	fout.close();
	return ch;
}




//function to write the database onto a file
template <typename T> 
bool functionality<T> ::writedata()
{
	ofstream fout("File.txt");

	//first line indicating the number of products
	int n = ob.getLength();
	fout<<n<<endl;

	//writing all the products one by one
	for(int i=0; i<n; i++)
	{
		Product* P;
		ob.retrieve(i, P);

		fout<<P->producttype()<<endl<<P->getName()<<endl<<P->getCategory()<<endl<<P->getBarcode();
		fout<<endl<<P->getPrice()<<endl<<P->getManu()<<endl<<P->getStock()<<endl<<P->getSold()<<endl;

		if(P->producttype() == 'y')
		{
			Date D = P->getDate();
		
			if(D.day <10)
				fout<<'0'<<D.day;
			else
				fout<<D.day;

			if(D.month < 10)
				fout<<'0'<<D.month;
			else
				fout<<D.month;
			fout<<D.year<<endl<<P->getDiscount()<<endl;
		}
	}

	fout.close();
	ifstream fin("File.txt");
	if(fin == NULL)
		return false;
	fin.close();
	return true;
}



template <typename T>
int functionality<T>::IfExpired(int a) 
{
	setcolor(15) ;
	Product *p;
	//search for the product
	int i = search(a,p);

	//product does not exist
	if(i<0)
		return 0;
	else

	if(p->producttype() == 'n')
		return 0;
	else
	{
		//find the expiry date of product
		Date d;
		d=p->getDate();

		time_t t = time(0); // get time now
		struct tm *timeinfo=localtime(&t);
		time_t rawtime;
		timeinfo->tm_year=d.year-1900;
		timeinfo->tm_mon=d.month-1;
		timeinfo->tm_mday=d.day;
		rawtime=mktime(timeinfo);//expiry date of product

		//if product has expired
		if(rawtime<=t)
		{
			cout<<"\nThe product has expired. Do you want to delete this product(y//n)\t:\t";
			char ch;
			cin>>ch;
			if(ch == 'y' || ch=='Y')
				scrap(p->getBarcode());
			return 1;
		}
		//if product has not expired
		else
			return 2;
	}
}

template <typename T>
int functionality<T>::IfExpired(string s, int x) 
{
	setcolor(15) ;

	Product** P = new Product*[ob.getLength()];
	Product* P1;
	Date d;

	// search for number of products with same input
	int num = search(s, x, P);

	if(num == 0)
	{
		return 0;
	}
	else
	{
		//display all the details of products
		cout<<"\n"<<num<<" occurrences of related products have been found";
		for(int i=0; i<num; i++)
		{
			if(num>1)
				cout<<"\n\nDetails of Product No. "<<i+1<<"\t:";
			else
				cout<<"\n\nDetails of the product you have choosen to check\t:";
			P[i]->printproduct(); cout<<endl;

		}

		//if only one product then get the date
		if(num == 1)
		{
			d = P[num-1]->getDate();
			P1=P[0];
				
		}
		else
		{
			//more than 1 products then ask user for his choice of product
			cout<<"Enter your choice of product that you want to check\t:\t";
			int choice;
			cin>>choice;
		
			choice -= 1;

			P1=P[choice];
			d = P[choice]->getDate();
		}
	}

	delete []P;

	time_t t = time(0); // get time now
	struct tm* timeinfo=localtime(&t);
	time_t rawtime;
	timeinfo->tm_year=d.year-1900;
	timeinfo->tm_mon=d.month-1;
	timeinfo->tm_mday=d.day;
	rawtime=mktime(timeinfo);//expiry date of product

	if(rawtime<=t)
	{
		cout<<"\nExpired! Do you want to delete this product(y//n)\t:\t";
		char ch;
		cin>>ch;
		if(ch == 'y' || ch=='Y')
			scrap(P1->getBarcode());
		return 1;
	}
	else
		return 2;
	
}


//function to search for the existance of a product with a given barcode
template <typename T>
bool functionality<T>:: search(int barcode)
{
	setcolor(15) ; //to white

	Product* P1;
	int i=0, max = ob.getLength(); //gets the length of the dynamic array of products

	//check whole list
	for(i=0; i<max; i++)
	{
		//retrieve each product
		ob.retrieve(i, P1); //retrieve by index into P1 pointer which is passed by reference

		//if barcode matches the return index
		if(barcode == P1->getBarcode())
		{
			return true;
		}
	}

	//no barcode match
	return false;
}


//function to search the database for products with the same barcode
template <typename T>
int functionality<T> ::search(int barcode, Product*& P1) //passed by reference HERE to remember changes made to P1 in retrieve
{
	setcolor(15) ;

	int i=0, max = ob.getLength();

	//check whole list
	for(i=0; i<max; i++)
	{
		//retrieve each product
		ob.retrieve(i, P1);

		//if barcode matches return the index
		if(barcode == P1->getBarcode())
		{
			return i;
		}
	}
	//no barcode match
	return -1;
}



//function to check the database for products with the same specifications
template <typename T>
int functionality<T> ::search(string s, int ch, Product** P1) //pointer to a pointer 
{
	setcolor(15) ;

	int counter=0, i=0, max=ob.getLength();

	//check whole list
	for(i=0; i<max; i++)
	{
		// search by name
		if(ch == 1)
		{
			//retrieve each product
			ob.retrieve(i, P1[counter]);

			//if name matches increase counter
			if(P1[counter]->getName() == s)
			{
				counter++;
			}
		}
		else
			//search by category
			if(ch == 2)
			{
				//retrieve each product
				ob.retrieve(i, P1[counter]);

				// if category matches increase counter
				if(P1[counter]->getCategory() == s)
				{
					counter++;
				}
			}
			else
				//search by manufacturer
				if(ch == 3)
				{
					//retrieve each product
					ob.retrieve(i, P1[counter]);

					//if manufacturer matches increase counter
					if(P1[counter]->getManu() == s)
					{
						counter++;
					}
				}
	}

	return counter;
}


//get the stock of the product
template <typename T>
int functionality<T>:: obtstock(int code)
{
	setcolor(15) ;

	Product* P;
	search(code, P);

	return P->getStock();
}

//to get the number of products in the store
template <typename T>
int functionality<T>::getnop()
{
	return ob.getLength();
}


//deletion of objects for batchprocessing
template <typename T>
bool functionality<T>::batchscrap(int code)
{
	setcolor(15) ;

	Product* P;

	//find index of product with that barcode in the list
	int index = search(code, P);
	
	//no such product exists
	if(index == -1)
		return false;
	else
	{
		ob.remove(index);
		return true;
	}
}


template <typename T> 
bool functionality<T> :: batchrestock(int code, int qty)
{
	setcolor(15) ;

	Product* P;
	//find index of the product in list
	int index = search(code, P);
	
	//invalid index, no such product
	if(index == -1)
		return false;
	else
	{
		P->restock(qty);
		return true;
	}
}


template <typename T> 
bool functionality<T> ::batchsale(int code, int qty)
{
	setcolor(15) ;

	Product* P;
	int index = search(code, P);
	
	//when no such product exists
	if(index == -1)
		return false;
	else
	{
		P->addSold(qty);
		return true;
	}
}

template <typename t>

bool functionality<t>::batchreset(int code)
{
	Product * P ;
	int index = search(code, P) ;

	if(index == -1) 
		return false ;
	else
	{
		P->setstock(0) ;
	}
}






template <typename T>
bool functionality<T>::batchIfExpired(int bc,int date)
{
	Product *p;
	int year,month,day;
	//search for the product
	int i = search(bc,p);
	if(p->producttype())
	//date user entered
	year= date%10000;
	date=date/10000;
	month=date%100;
	date=date/100;
	day=date;
	//product does not exist
	if(i<0)
		return false;
	else
	if(p->producttype() == 'n')
		return 0;
	else
	{
		//find the expiry date of product
		Date d;
		d=p->getDate();

		//assuming the product has not expired
		bool ch = false; 

		if(d.year < year)
			ch = true;
		else
			if(d.year == year && d.month < month)
				ch = true;
			else
				if(d.year == year && d.month == month && d.day < day)
					ch = true;

		return ch;
	}
}

template class functionality<DAList<Product*>>;