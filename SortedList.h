#ifndef SORTLIST_H
#define SORTLIST_H

#include "Perishables.h"
#include "ListBase.h"

template <typename T1>
class SortedList : public ListBase
{
	//structure of the node used in the list
	struct node
	{
		T1 P;
		node* next;
	};
	node* head, *tail;
	
public:
	SortedList() ;
	~SortedList() ;

	bool insert(T1 P1);
    bool remove(int index);
    bool retrieve(int index, T1& P1);
	

} ;

#endif