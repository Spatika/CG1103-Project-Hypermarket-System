#include "stack.h"

template <class T3>
Stack<T3>::Stack()
{
	_size=0;
	//arr1 = new T3 [_size++];
}

template <class T3>
bool Stack<T3>::isEmpty()
{
	if(_size==0)
		return true;
	else
		return false;
}

//reduce array size
template <class T3>
bool Stack<T3>::expandarray()
{
	bool ch=false;

	// create new array that is larger by 1
	
	T3 *newarray = new T3[_size + 1]; //here T3 is 
	
	if(newarray != NULL)
		ch=true;

	// copy old array into a new array
	for(int i = 0; i<_size; i++)
	{
		newarray[i] = arr1[i];  //these are Submissions that you're copying right not Submission pointers
	}

	newarray[_size].name =  '0'; //YUP!
	newarray[_size].Qptr= NULL;

	//delete old array
	for(int i=0;i<_size;i++)
	{
		arr1[i].name= '0';
		arr1[i].Qptr = NULL;
	}
	//delete [] arr1;

	//set old array to new array
	arr1 = newarray;

	//add size
	_size ++;
	return ch;
}

//reduce array size
template <class T3>
void Stack<T3> ::contractarray()
{

	//create new array that is smaller by 1
	T3 *newarray = new T3[_size-1];

	//copy old array to new array
	for(int i = 0; i<_size-1; i++)
	{
		newarray[i] = arr1[i];
	}

	for(int i=0;i<_size;i++)
	{
		arr1[i].name= '0';
		arr1[i].Qptr = NULL;
	}
	//delete [] arr1;

	//set old array to new array
	arr1 = newarray;
	
	//decrease size
	_size--;
}

template <class T3>
int Stack<T3>::size()
{
	return _size;
}

template <class T3>
bool Stack<T3>::push( T3& newItem )
{
	bool test;
	test = expandarray();
	arr1[size()-1].name = newItem.name;
	arr1[size()-1].Qptr = newItem.Qptr;
	//_size++;
	return true;
}

template <class T3>
bool Stack<T3>::pop( T3& stackTop )
{
	if(!isEmpty())
	{
		stackTop.name = arr1[_size-1].name;
		stackTop.Qptr=arr1[_size-1].Qptr;
		arr1[_size-1].name =  '0';
		arr1[_size-1].Qptr= NULL;
		contractarray();
		return true;
	}
	else
		return false;

}

template <class T3>
bool Stack<T3>::getTop(T3& stackTop)
{
	if(!isEmpty())
	{
		stackTop.name = arr1[_size-1].name;
		stackTop.Qptr=arr1[_size-1].Qptr ;
		return true;
	}
	else
		return false;
}

template class Stack<Submission>;