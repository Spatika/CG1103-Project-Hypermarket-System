#include "ListBase.h"
#include "Product.h"
#include "Perishables.h"
template <class T>

class DAList: public ListBase
{
private:
	//int actsize;
	T* array1;
	
	//Methods to change array size
	bool expandarray();
	void contractarray();

public:

	DAList();

	~DAList();
	
	// Method to insert a new product into list
	bool insert(T p);

	//Method to remove a product from list
    bool remove(int index);

	//Method to retrieve product from list
    bool retrieve(int index, T& retriever);

};