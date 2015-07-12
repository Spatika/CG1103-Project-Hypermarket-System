#ifndef QUEUELL_H
#define QUEUELL_H
#include "Job.h"
//QueueLL is a template class -> but we use it to have a Queue of Job objects (Job is a class having 
template <class T2>

class QueueLL 
{
private:
	int size;

	struct QNode{
		T2 item; //Job* in this case
		QNode* next;
	};

	QNode* tail;
		
public:

	QueueLL();
	~QueueLL();

	bool isEmpty();
	int getSize();
	bool enqueue( T2 newItem );

    bool dequeue( T2& queueFront ); 

    bool getFront( T2& queueFront );

};

#endif 


//Queue is implemented using a linked list 