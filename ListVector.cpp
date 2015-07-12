#include "ListVector.h"
#include "Product.h" 
#include<string>

using namespace std ;

template <class T>
bool ListVector<T>::insert(T P)
{ 
	if(List.size() >= List.max_size()) //current size greater than maximum allowed size
		return false ;
	
	List.push_back(P) ;
	_size++;
	return true ; 
}

template <class T>
bool ListVector<T>::remove(int index) //index starts from 0
{

	if(index < 0 || index >= _size) //invalid index
		return false ;

	List.erase(List.begin()+index) ;  //List.begin() random access iterator at beginning of vector; List.erase() automatically shifts other nodes after deletion
	_size-- ;
	
	return true ;

}

template <class T>
bool ListVector<T>::retrieve(int index, T& P)
{
	if(index < 0 || index >= _size)
	{
		P = NULL ; 
		return false ;
	}

	P = List[index] ;
	return true ;
}

template class ListVector<Product*>;