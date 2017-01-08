#include<iostream>
#include "Lists.H"

// Method for getting the list head
template <class T>
T& LinkedList<T>::getHead()
{
	if (head == NULL)
	{
		return NULL;
	}
	currLocation = head;
	return head->data;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	while (this->size > 0)
	{
		this->currLocation = this->head;
		this->removeElem();
	}
	//need to check later
}

// Method for adding a new element to the head of the list
template <class T>
Result LinkedList<T>::addHead(T newData)
{
	if (DoesDataExist(newData) == SUCCESS) return FAILURE;// Data already exist in our list!!
	if (head == NULL) // If our list is empty
	{
		head = new listElem<T>(newData);

		if (head == NULL)
		{
			delete head;
			return FAILURE;
		}

		head->next = NULL;
		size++;
		return SUCCESS;
	}
	else // Our list is NOT empty so we add the new element to the HEAD of the list
	{

		listElem<T>* temp = new listElem<T>(newData);
		if (temp == NULL)
		{
			return FAILURE;
		}

		temp->next = head;
		head->next = temp;
		size++;
		return SUCCESS;
	}
}

// Method for removing an element from the list
template <class T>
Result LinkedList<T>::removeElem()
{
	
	if (currLocation == NULL) return FAILURE;
	if (head == currLocation)
	{
		listElem<T>* temp = currLocation;
		head = head->next;
		delete temp;
		currLocation = NULL;
		size--;
		return SUCCESS;
	}
	listElem<T>* temp1;
	listElem<T>* temp2;

	temp1 = head;
	while (1)
	{
		temp2 = temp1->next;
		if (temp2 == currLocation)
		{
			temp1->next = temp2->next;
			temp2->next = NULL;
			delete temp2;
			currLocation = NULL;
			size--;
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

// A function that checks if we are trying to add data that already exists.
template <class T>
Result LinkedList<T>::DoesDataExist(T newData)
{
	if (newData == NULL) return FAILURE;
	listElem<T>* temp = head;
	if (temp == NULL) return FAILURE;
	while (temp->next != NULL)
	{
		if (newData == temp->data) return SUCCESS;
		else
		{
			temp->next = temp->next->next;
		}
	}
	return FAILURE;
}

// Method for moving our list iterator to the next element
template <class T>
Result LinkedList<T>::getNext()
{
	if (currLocation == NULL) return FAILURE;
	if (currLocation->next == NULL) return FAILURE;
	currLocation = currLocation->next;
	return SUCCESS;
}

// Method for getting the size of our linked list
template <class T>
int LinkedList<T>::getSize()
{
	return this->size;
}

// Method for getting the data that is found in the linked list.
template <class T>
T& LinkedList<T>::getData()
{
	return currLocation->data;
}
