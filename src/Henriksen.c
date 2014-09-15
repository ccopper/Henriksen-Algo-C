
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include "Henriksen.h"

//Defaults for the structs
struct HLN HLNDef = {NULL, NULL, INT_MIN, NULL};
struct HTN HTNDef = {NULL, NULL, NULL};

//Internal Functions
HLN* createHLN(int time);
HTN* createHTN(HLN* lItem);

HDS* createHenrik(int pSize)
{
	//Alloc new object
	HDS* temp = malloc(sizeof(HDS));
	temp->pSize = pSize;

	//Create the dummy list items
	temp->lHead = createHLN(INT_MIN);
	temp->lTail = createHLN(INT_MAX);
	temp->lHead->lNext = temp->lTail;
	temp->lTail->lPrev = temp->lHead;

	//Create the default tree
	temp->tRoot = createHTN(temp->lHead);
	temp->tRoot->lChild = createHTN(temp->lHead);
	temp->tRoot->rChild = createHTN(temp->lTail);

	temp->tRoot->rChild->lowNode = temp->tRoot;
	temp->tRoot->lowNode = temp->tRoot->lChild;

	return temp;
}




HLN* createHLN(int time, void* ePayload)
{
	HLN* temp = malloc(sizeof(HLN));
	memcpy(temp, &HLNDef, sizeof(HLN));
	temp->eTime = time;
	temp->ePayload = ePayload;
	return temp;
}
HTN* createHTN(HLN* lItem)
{
	HTN* temp = malloc(sizeof(HTN));
	memcpy(temp, &HTNDef, sizeof(HTN));
	temp->lItem = lItem;
	return temp;
}

