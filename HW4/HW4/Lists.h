#ifndef _LISTS_H_
#define _LISTS_H_

#include <iostream>
#include <string>
#include "defs.H"
using namespace std;
// This is a template for our Lists. A modifiable list will be provided for each 
// necessary type (Message List, Follower List, Friend list....etc).
// Included are the required functions that can be executed on the lists.
template <class T> 
class LinkedList
{
private:
	listElem<T>* head_;
	listElem<T>* currLocation_;
	int size_;
	//Result DoesDataExist(T newData);

public:
	// Constructor
	LinkedList()
	{
		head_ = NULL;
		currLocation_ = NULL;
		size_ = 0;
		
	}
	// Destructor
	virtual ~LinkedList();


	
	Result addHead(T newHead);
	Result removeElem();
	Result getNext();
	T* getHead();
	T* getData();
	int getSize();

	
	//bool operator==(const T &a) {};
};

//* Destructor
template<class T>
LinkedList<T>::~LinkedList()
{
	
	clog << "we start the : ~LinkedList() with tiems :" << this->getSize()<< endl;
	while (NULL != this->head_)
	{
		this->currLocation_ = head_;
		this->head_ = this->head_->next;
		//clog << this->getSize()<<")" << "this element(list) will be destroy: " << &(this->currLocation_->data) << endl;
		delete this->currLocation_->data;
		delete this->currLocation_;
	
	}
	

	
}


//*******************************************************************
//* getHead()
//* Method for adding a moving the iterator to the head of the list.
//* no parameters
//* Returns a pointer
//*******************************************************************
template <class T>
T* LinkedList<T>::getHead()
{
	if (head_ == NULL)
	{
		return NULL;
	}
	
	currLocation_ = head_;
	return head_->data;
}

//*******************************************************************
//* addHead()
//*  Method for adding a new element to the head of the list.
//* T newData
//* {SUCCESS,FAILURE}
//*******************************************************************
template <class T>
Result LinkedList<T>::addHead(T newData)
{
	//if (DoesDataExist(newData) == SUCCESS) return FAILURE;// Data already exist in our list!!
	
	if (head_ == NULL) // If our list is empty
	{
		listElem<T>* temp = new listElem<T>;
		head_ = temp;
		
		T * new_datada = new T;
		*new_datada = newData;
		if (head_ == NULL)
		{
			delete head_;
			return FAILURE;
		}
		head_->data = new_datada;
		head_->next = NULL;
		size_++;
		return SUCCESS;
	}
	else // Our list is NOT empty so we add the new element to the HEAD of the list
	{

		listElem<T>* temp = new listElem<T>;
		//temp = head_;
		T * new_datada = new T;
		*new_datada = newData;

		if (temp == NULL)
		{
			return FAILURE;
		}
		//temp = head_;
		temp->data = head_->data;
		temp->next = head_->next;
		head_->data = new_datada;
		head_->next = temp;
		
		size_++;
		return SUCCESS;
	}
}

//*******************************************************************
//* removeElem()
//* Method for removing an element from the list
//* no parameters
//* {SUCCESS,FAILURE}
//*******************************************************************
template <class T>
Result LinkedList<T>::removeElem()
{

	if (currLocation_ == NULL) return FAILURE;
	if (head_ == currLocation_)
	{
		listElem<T>* temp = currLocation_;
		head_ = head_->next;
		delete temp->data;
		delete temp;
		temp = NULL;
		currLocation_ = NULL;
		size_--;
		return SUCCESS;
	}
	listElem<T>* temp1;
	listElem<T>* temp2;

	temp1 = head_;
	while (1)
	{
		temp2 = temp1->next;
		if (temp2 == currLocation_)
		{
			temp1->next = temp2->next;
			temp2->next = NULL;
			delete temp2;
			currLocation_ = NULL;
			temp2 = NULL;
			size_--;
			return SUCCESS;
		}
		if (temp2 == NULL)
		{
			break;
		}
		temp1 = temp2;
	}
	return FAILURE;
}

//*******************************************************************
//* DoesDataExist()
//* A function that checks if we are trying to add data that already exists.
//* newData
//* {SUCCESS,FAILURE}
//*******************************************************************
/*template <class T>
Result LinkedList<T>::DoesDataExist(T newData)
{
	//if (newData == NULL) return FAILURE;
	listElem<T>* temp = head_;
	if (temp == NULL) return FAILURE;
	while (temp->next != NULL)
	{
		if (temp->data == newData) return SUCCESS;
		else
		{
			temp = temp->next;
		}
	}
	return FAILURE;
}*/

//*******************************************************************
//* getNext()
//* Method for moving our list iterator to the next element
//* no parameters
//* {SUCCESS,FAILURE}
//*******************************************************************
template <class T>
Result LinkedList<T>::getNext()
{
	if (currLocation_ == NULL) return FAILURE;
	if (currLocation_->next == NULL) return FAILURE;
	currLocation_ = currLocation_->next;
	return SUCCESS;
}

//*******************************************************************
//* getSize()
//* Method for getting the size of our linked list
//* no parameters
//* returns int
//*******************************************************************
template <class T>
int LinkedList<T>::getSize()
{
	return this->size_;
}

//*******************************************************************
//* getData()
//* Method for getting the data that is found in the linked list.
//* no parameters
//* returns a pointer to the data
//*******************************************************************
template <class T>
T* LinkedList<T>::getData()
{
	return currLocation_->data;
}

#endif
