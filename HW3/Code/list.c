#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
//#define MAX_SIZE (256)

// This will be the structure of our iterator
typedef struct node_iter
{
	//node field
	struct node_iter* nextNode;

	//information field
	PElem address;
}*Pnode_iter, node_iter;

// This is our linked list that holds the relevant information
typedef struct List_
{
	//node field
	Pnode_iter iterator;
	
	//information field
	Pnode_iter head_element; 
	CLONE_FUNC copy_list_elem;
	DESTROY_FUNC free_list_elem;

}List_, *PList;

PList ListCreate(CLONE_FUNC copy_list_elem, DESTROY_FUNC free_list_elem)
{
	if ((copy_list_elem == NULL) || (free_list_elem == NULL))
	{
		return NULL;
	}
	PList node = (PList)malloc(sizeof(List_));
	if (node == NULL)
	{
		return NULL;
	}
	node->copy_list_elem = copy_list_elem;
	node->free_list_elem = free_list_elem;
	node->head_element = NULL;
	node->iterator = NULL;

	return node;
}

// A function that adds new nodes to our linked list.
Result ListAdd(PList list_elem, PElem linked_elements)
{
	if ((list_elem == NULL) || (linked_elements == NULL))
	{
		return FAIL;
	}
	Pnode_iter node = (Pnode_iter)malloc(sizeof(node_iter));
	//PElem element = (PElem)malloc(sizeof(linked_elements));
	if (node == NULL)
	{
		free(node);
		return FAIL;
	}
	
	//node = list_elem->iterator;
	node->address = list_elem->copy_list_elem(linked_elements);
	node->nextNode = list_elem->head_element;
	list_elem->head_element = node;

	return SUCCESS;

}

// A function that moves our iterator to the front of the linked list
// and returns a pointer to the node that the iterator is pointing to.
PElem ListGetFirst(PList list_elem)
{
	if (list_elem == NULL) return NULL;
	if (list_elem->head_element == NULL)
	{
		list_elem->iterator = NULL;
		return NULL;
	}
	list_elem->iterator = list_elem->head_element;
	return list_elem->iterator->address;
}

// Moves the iterator to the next node in our linked list and returns a pointer
// to the node that the iterator is now pointing to.
PElem ListGetNext(PList list_elem)
{
	if (list_elem == NULL) return NULL;
	if (list_elem->head_element == NULL) return NULL;
	if (list_elem->iterator == NULL) return NULL;
	if (list_elem->iterator->nextNode == NULL) return NULL; // No next node to point to!

	list_elem->iterator = list_elem->iterator->nextNode;

	return list_elem->iterator->address;
}

// A function that returns the size of our list.
int ListGetSize(PList list_elem)
{
	if (list_elem == NULL) return -1;
	Pnode_iter temp;
	temp = list_elem->head_element;
	int counter = 0;
	while (1)
	{
		if (temp != NULL)
		{
			counter++;
			temp = temp->nextNode;
			continue;
		}
		else break;
	}
	return counter;
}
/*
Result ListRemove(PList list_elem)// Head_Element should always be the input here 
								  // so we start from beginning of the list! (I think)
{
	Pnode_iter temp_Iterator1;
	Pnode_iter temp_Iterator2;
	if (list_elem == NULL) return FAIL;
	if (list_elem->iterator == NULL)
	{
		return FAIL;
	}
	// Checking if there is only one node in the list and it doesn't have a correct address.
	if (list_elem->iterator->nextNode == NULL && list_elem->iterator->address == NULL)
	{
		return FAIL;
	}

	if (list_elem->iterator->address != NULL)
	{
		list_elem->iterator->address = NULL;
		return SUCCESS;
	}
	// We will use two pointers (one right before the other) so that when the first
	// pointer hits the iterator address, we have the location of the node before 
	// it, to attach to the next node in the iterator.
	temp_Iterator1 = list_elem->iterator;
	temp_Iterator2 = list_elem->iterator->nextNode;
	while (1)
	{
		if (temp_Iterator2->address != NULL) // Meaning the iterator is pointing here.
		{
			if (temp_Iterator2->nextNode == NULL) // This means the iterator is at the end 
			{									  // of the list, so we just point the one
				temp_Iterator1->nextNode = NULL;  // before it to NULL!
				//free(temp_Iterator2->address);
				temp_Iterator2->address = NULL;
				return SUCCESS;
			}
			else
			{
				temp_Iterator1->nextNode = temp_Iterator2->nextNode;
				//free(temp_Iterator2->address);
				temp_Iterator2->address = NULL;
				return SUCCESS;
			}
		}
		else
		{
			// The iterator wasn't found so we move to the next iterator node
			// to see if has an address.
			temp_Iterator2->nextNode = temp_Iterator2->nextNode->nextNode;
			temp_Iterator1->nextNode = temp_Iterator1->nextNode->nextNode;
			continue;
		}
	}
}*/

Result ListRemove(PList list_elem)
{	
	if (list_elem == NULL) return FAIL;
	if (list_elem->head_element == NULL) return FAIL;
	if (list_elem->iterator == NULL) return FAIL;
	if (list_elem->iterator->address == NULL) return FAIL;
	if (list_elem->head_element->nextNode == NULL)// Checking if there is only one node in the list.
	{
		if (list_elem->head_element->address != list_elem->iterator->address) return FAIL;
		else
		{
			list_elem->head_element->address = NULL;
			list_elem->iterator->address = NULL;
			return SUCCESS;
		}
	}
	Pnode_iter temp1 = list_elem->head_element; // Is now head element
	while (1)
	{
		if (temp1 == NULL || temp1->address == NULL) return FAIL;
		if (temp1->address == list_elem->iterator->address)
		{
			if (temp1->nextNode == NULL)
			{
				temp1->address = NULL;
				list_elem->iterator->address = NULL;
				list_elem->head_element = temp1;
				return SUCCESS;
			}
			else
			{
				temp1->address = NULL;
				temp1 = temp1->nextNode;
				list_elem->iterator->address = NULL;
				list_elem->head_element = temp1;
				return SUCCESS;
			}
		}
		temp1 = temp1->nextNode;
	}
}

void ListDestroy(PList list_elem)
{
	if (list_elem == NULL) return;

	PList temp = list_elem;
	while (temp->head_element != NULL)
	{
		temp->head_element = temp->head_element->nextNode;
		list_elem->free_list_elem(list_elem->head_element);
		list_elem->head_element = temp->head_element;
	}
	free(list_elem->iterator);
	free(list_elem);
}
