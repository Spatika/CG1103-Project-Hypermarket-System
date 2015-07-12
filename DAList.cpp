#include "DAList.h"
#include <iostream>
using namespace std;

template <class T>
DAList<T>::DAList()
	:ListBase()
{
	//actsize=_size;
	array1 = new T[_size];
}


template <class T>
DAList<T>::~DAList()
{
	//delete [] array1;
}

//increase array size
template <class T>
bool DAList<T>::expandarray()
{
	bool ch=false;
	//actsize=_size+1000;
	// create new array that is larger by 1000
	T *newarray = new T[_size + 1000];
	if(newarray != NULL)
		ch=true;

	// copy old array into a new array
	for(int i = 0; i<_size; i++)
	{
		newarray[i] = array1[i];
	}

	newarray[_size] = NULL;

	//delete old array
	delete [] array1;

	//set old array to new array
	array1 = newarray;

	//add size
	_size += 1;
	return ch;
}

//reduce array size
template <class T>
void DAList<T> ::contractarray()
{

	//create new array that is smaller by 1
	T *newarray = new T[_size-1];

	//copy old array to new array
	for(int i = 0; i<_size-1; i++)
	{
		newarray[i] = array1[i];
	}

	delete [] array1;

	//set old array to new array
	array1 = newarray;

	//decrease size
	_size--;
}

template <class T>
bool DAList<T> ::insert(T p)
{
	bool ch;

	// increase array size
	//if(_size == actsize)
		ch = expandarray();

	//put new product pointer into last position
	array1[getLength()-1] = p;
		
	return ch;
}

template <class T>
bool DAList<T> ::remove(int index)
{
	//if invalid index return false
	if(index < 0 || index >= getLength())
		return false;
	else
	{
		//delete product at that index
		delete array1[index];
		array1[index] = NULL;

		//shift the other products
		for(int i=index; i<getLength()-1; i++)
		{
			array1[i] = array1[i+1];
		}

		//reduce array size
		contractarray();

		return true;
	}
}

template <class T>
bool DAList<T> ::retrieve(int index, T& retriever)
{
	// if invalid index return flase
	if(index < 0 || index >= getLength())
		return false;
	else
	{
		//set the pointer that is passed in to be product pointer at that index
		retriever = array1[index];

		return true;
	}
}

template class DAList<Product*>;



