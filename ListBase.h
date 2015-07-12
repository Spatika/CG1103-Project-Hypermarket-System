#ifndef LISTBASE_H
#define LISTBASE_H

#include<iostream>
#include "Perishables.h"
using namespace std;
class ListBase 
{

protected:
    int _size;
        
public:
    ListBase() { _size = 0; }
    virtual ~ListBase() {}

    bool isEmpty()  { return (_size == 0) ;}
    int getLength() { return _size; }
	/*
    virtual bool insert(Product*);
    virtual bool remove(int index);
    virtual bool retrieve(int index, Product*&P);
      */
}; 

#endif