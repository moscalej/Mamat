#include <stdio.h>
#include <stdlib.h>
typedef struct _LIST_ELEMENT {
    int i; // this is the information of the node
    struct _LIST_ELEMENT* pNext; // this will be the addres of the next node
} LIST_ELEMENT; // this is the alias to call the str
int main() {
    LIST_ELEMENT* List = NULL;
    LIST_ELEMENT* pElem;
    int i;
    /* Keep adding elements as long as the user enters
    numbers */
    while (scanf("%d", &i) > 0) {
        pElem = (LIST_ELEMENT*)malloc(sizeof(LIST_ELEMENT));
        if (NULL == pElem)
            exit(-1);
        pElem->i = i;
        pElem->pNext = List;
        List = pElem;
    }
    printf("Accepted the following numbers:\n");
    for (pElem = List; pElem; pElem = pElem->pNext)
    printf("%d\n", pElem->i);
    /* Destroy the list */
    while(List) {
        pElem = List;
        List = List->pNext;
        free(pElem);
    }
 return 0;
}
