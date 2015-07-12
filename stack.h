#include<iostream> //Stack class is a template
#include<string>
using namespace std;
#include "QueueLL.h"

struct Submission{ 
	string name;
	QueueLL<Job*>* Qptr; //ptr. to a queue of job pointers
};


template <class T3>
//template <class T>

class Stack{
	T3 *arr1; //Submission = T3 
	
	int _size;
	bool expandarray();
	void contractarray();
public:
	Stack();
	bool isEmpty();
	int size();
	bool push( T3& newItem ); //why are these passed  by reference?
	bool pop( T3& stackTop ); 
	bool getTop( T3& stackTop);

} ;

//stack implemented using?? dynamic array
