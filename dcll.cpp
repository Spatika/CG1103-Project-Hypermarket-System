#include "dcll.h"

template <class T>
dcll<T>::dcll()
{
	tail= NULL;
}


template <class T>
dcll<T>::~dcll()
{

}


template<class T>
bool dcll<T>::insert(T p)
{
	listnode *a= new listnode; //create a new listnode
	a->p=p; //store p into the new listnode
	if(a == NULL) //if p is NULL then return false 
		return false; 
	if(_size==0) //if it is an empty list
	{
		a->next=a; //set a next to itself
		a->prev=a; //set a prev to itself
		tail=a; //set tail to point to a
		_size++; //increment size
	}
	else //we are adding the new items to the back of the list
		if(_size==1) //if the list already has an item
		{
			tail->next =a; //set tail next to be a
			a->prev =tail; //a prev will be tail
			a->next =tail; //a next will be tail
			tail->prev =a; //tail prev will point to a 
			_size++; //increment size
			tail=a; //set tail to be a 
		}
		else //if the list has more than 1 item
		{
			listnode *head; //create a new listnode pointer called head
			head= tail->next; //head will point to the first element
			tail->next =a;  //set tail next to be a
			a->prev=tail;  //a prev will be tail
			a->next =head; //a next will be head
			head->prev = a;  //head prev will be a
			tail=a;  //set tail to a
			_size++; //increment size
		}
		return true; //return true if added successfully
}

template <class T>
bool dcll<T> :: remove(int index)
{
	listnode *cur=tail->next; //set new listnode pointer cur to be at first element of list
	if(index<0 && index>_size && _size <=0) //if index passed in is lesser than zero or greater than size or size =0
		return false;
	else
	{
		for(int i=0;i<index;i++) //traversing through the list till the index
		{
			cur=cur->next;
		}
		if(_size==1) //if the list has only 1 item 
		{
			delete cur->p; //delete the content and the cur pointer
			delete cur;
			tail=NULL; //set tail to NULL
			_size--; //reduce the size by 1
			return true; // return true if removing is done successfully
		}
		else
		{
			cur->prev->next = cur->next; //the prev item of the the item to be deleted will be pointing to the next element of the cur item
			cur->next->prev=cur->prev; // the next item of cur 's prev pointer will point to cur->prev
			_size--; //reduce the size by 1
			if(cur==tail) //if deleting the last element of the list then set tail to be the prev item of cur
				tail=cur->prev;
			delete cur->p; 
			delete cur;
			return true;
		}
	}
}

template <class T>
bool dcll<T>::retrieve(int index,T& p) // retrieve from this index and store in p
{
	listnode *cur=tail->next; //cur will be set to the first element in the list
	if(index<0 && index> _size)
		return false;
	else
	{
		if(index ==0)//if retrieving first element
		{
			p=cur->p;
		}
		for(int i=0;i<index;i++) //traverse to the index wanted
			cur=cur->next;
		p=cur->p; //set p to be cur->p
		return true;
	}
}

template class dcll<Product*>; //template instantitaion
