#include "QueueLL.h"
#include <iostream>
#include <string>
using namespace std;

template <class T2>

QueueLL<T2>::QueueLL()
{
	size = 0;
	tail = NULL;
}

template <class T2>

bool QueueLL<T2>::isEmpty()
{
	if(size == 0)
		return true;
	else
		return false;
}

template <class T2>

int QueueLL<T2>::getSize()
{
	return size;
}

template <class T2>

QueueLL<T2>::~QueueLL()
{
	T2 hold;
	while(!isEmpty())
	{
		dequeue(hold);
	}
}

template <class T2>

bool QueueLL<T2>::enqueue( T2 newItem )
{
	QNode* NewNode; 
	NewNode = new QNode;
	NewNode->item = newItem;
	

	if(isEmpty())
	{
		NewNode->next = NewNode;
		tail = NewNode;
	}
	else
	{
		NewNode->next = tail->next;
		tail->next = NewNode;
		tail = NewNode;
		
	}
	size++;
	return true;
}

template <class T2>

bool QueueLL<T2>::dequeue(T2& queueFront)
{
	if(isEmpty())
		return false;
	else
		if(size == 1)
		{
			//size--;
			queueFront = tail->item;
			delete tail;
			tail = NULL;
		}
		else
		{
			//size--;
			QNode* front; 
			front = tail->next;
			tail->next = front->next;
			queueFront = front->item;
			delete front;
			front = NULL;
		}
	size--;
	return true;
}

template <class T2>

bool QueueLL<T2>::getFront(T2& queueFront)
{

	if(isEmpty())
		return false;
	else
	{
		queueFront = tail->next->item;
		return true;
	}
}

template class QueueLL<Job*>;