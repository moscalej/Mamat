#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
//#define MAX_SIZE (256)

// This will be the structure of our iterator
typedef struct node_iter
{
	//node field
	struct node_iter * nextNode;
	//Pnode_iter headNode;
	//information field
	PElem address;
}*Pnode_iter, node_iter;

// This is our linked list that holds the relevant information
typedef struct List_ 
{
	//node field
	int vertex_num;
	Pnode_iter iterator;
	//information field
	Pnode_iter head_element;
	CLONE_FUNC copy_list_elem;
	DESTROY_FUNC free_list_elem;

}List_,*PList;

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
	if (node == NULL)
	{
		free(node);
		return FAIL;
	}
	node->address = list_elem->copy_list_elem(linked_elements);
	node->nextNode = list_elem->head_element;
	list_elem->head_element = node->address;

	return SUCCESS;

}

// A function that returns moves our iterator to the front of the linked list
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
	if (list_elem->iterator->nextNode == NULL) return NULL;
	
	list_elem->iterator = list_elem->iterator->nextNode;
	
	return list_elem->iterator->address;
}

// A function that returns the size of our list.
int ListGetSize(PList list_elem)
{
	if (list_elem == NULL) return NULL;
	Pnode_iter temp;
	temp = list_elem->head_element;
	int counter = 0;
	while (1)
	{
		if (temp == NULL)
		{	
			return counter;
		}
		temp = temp->nextNode;
		counter++;
	}
	
}
//PList ListDestroy(){}