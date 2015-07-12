#include "SortedList.h"

//constructor
template <typename T1>
SortedList<T1> :: SortedList()
{
	head = tail = NULL;
}

//destructor
template <typename T1>
SortedList<T1> ::~SortedList()
{
}


//function to insert the products inserted into the list sorted by category
template <typename T1>
bool SortedList<T1> ::insert(T1 P1)
{
	node* temp= new node;
	//in case there is no space on the heap memory
	if(temp == NULL)
		return false;
	
	//adding the product
	temp->P = P1;
	temp->next = NULL;
	_size++;
	if(head == NULL)
	{
		head = tail = temp;
	}
	else
	{
		string s = P1->getCategory();
		node* temp1 = head;
		int flag = 0;
		
		if(_size == 1)
		{
			if(head->P->getCategory() > s)
			{
				temp-> next = head;
				head = temp;
				return true;
			}

			else
			{
				head->next = temp;
				temp->next = NULL;
				tail = temp;
				return true;
			}
		}

		if(head->P->getCategory() > s)
		{
			temp->next = head;
			head = temp;
			return true;
		}

		//inserting the element in its position as per category
		for(temp1=head; temp1!= tail; temp1=temp1->next)
		{
			if(temp1->P->getCategory() <= s && temp1->next->P->getCategory() >= s)
			{
				flag = 1;
				temp->next = temp1->next;
				temp1->next = temp;
				return true;
			}
		}

		if (flag == 0)
		{
		tail->next = temp;
		tail = temp;
		}
	}
	return true;
}


//function to delete a product from the list where the index of the product is given
template <typename T1>
bool SortedList<T1> :: remove(int index)
{
	node* temp;
	int i=0;
	if(index >= _size)
		return false;

	if(index == 0)
	{
		if(head == tail)
		{
			delete head;
			head = tail = NULL;
			_size--;
		}
		else
		{
			temp = head;
			head = temp->next;
			delete temp;
			_size--;
		}
		return true;
	}

	//traversing to the index specified before deleting the product
	for(i=0, temp=head; temp!= tail || i<index; temp=temp->next,i++)
		if(i == index-1)
		{
			node* temp1 = temp->next;
			temp->next = temp1->next;
			delete temp1;
			_size--;
			return true;
		}
	return false;
}

//function to obtain the product at a particular index
template <typename T1>
bool SortedList<T1> ::retrieve(int index, T1& P1)
{
	node* temp;
	int i=0;
	if(index >= _size)
		return false;

	for(i=0, temp=head; temp!= NULL || i<=index; temp=temp->next,i++)
		if(i == index)
		{
			P1 = temp->P;
			return true;
		}

	return false;
}



template class SortedList<Product*>;