/*
 * set.h
 *
 *  Created on: 22 αιεπ 2016
 *      Author: Shirel_local
 */

#ifndef SET_H_
#define SET_H_

typedef enum{FALSE, TRUE} Bool;

typedef struct _Set* PSet;

/*User functions*/
typedef Bool (*COMP_FUNC)(PElem, PElem);

/*Interface functions*/
PSet SetCreate(COMP_FUNC, CLONE_FUNC, DESTROY_FUNC);
void SetDestroy (PSet);
Bool SetAdd (PSet, PElem);
PElem SetFindElement (PSet, PElem);
PElem SetGetFirst (PSet);
PElem SetGetNext (PSet);
int SetGetSize(PSet);
Bool SetRemoveElement(PSet, PElem);

#endif /* SET_H_ */
