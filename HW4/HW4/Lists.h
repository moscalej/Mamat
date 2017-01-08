#ifndef _LISTS_H_
#define _LISTS_H_

#include "defs.H"


// This is a template for our Lists. A modifiable list will be provided for each 
// necessary type (Message List, Follower List, Friend list....etc).
// Included are the required functions that can be executed on the lists.
template <class T> class LinkedList 
{
private:
	listElem<T>* head;
	listElem<T>* currLocation;
	int size;
	Result DoesDataExist(T newData);
	
public:
	// Constructor
	LinkedList()
	{
		head = NULL;
		currLocation = NULL;
		size = 0;
	}
	// Destructor
	~LinkedList();


	Result addHead(T newHead);
	Result removeElem();
	Result getNext();
	T& getHead();
	T& getData();
	int getSize();
};
// Add underscore to private*****************************************
#endif
