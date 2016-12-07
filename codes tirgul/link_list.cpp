#include <stdio.h>
#include <stdlib.h>

typedef struct _LIST_ELEMENT {
    int info_node; // this is the information of the node
    struct _LIST_ELEMENT* Next_node_address; // this will be the addres of the next node
} LIST_ELEMENT; // this is the alias to call the struct

int main() {
    LIST_ELEMENT* List = NULL; //we create list element ponter that points to nothing
    LIST_ELEMENT* pElem;		// we create a pointer to the first elemente of our list
    int info_node_input;		// this will be the info from the user

    /* Keep adding elements as long as the user enters
    numbers */

    while (scanf("%d", &info_node_input) > 0) {
        pElem = (LIST_ELEMENT*)malloc(sizeof(LIST_ELEMENT));
		if (NULL == pElem) {
			exit(-1);		// more space need it
		}
        pElem->info_node = info_node_input;
        pElem->Next_node_address = List;
        List = pElem; //list will get the ponter value of the last node
    }
    printf("Accepted the following numbers:\n");
    for (pElem = List; pElem; pElem = pElem-> Next_node_address )
    printf("%d\n", pElem->info_node);
    /* Destroy the list */
    while(List) {
        pElem = List;
        List = List->Next_node_address;
        free(pElem);
    }
 return 0;
}
