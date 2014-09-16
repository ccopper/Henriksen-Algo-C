
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include "Henriksen.h"

//Defaults for the structs
struct HLN HLNDef = {NULL, NULL, INT_MIN, NULL};
struct HTN HTNDef = {NULL, NULL, NULL};

//Internal Functions
HLN* createHLN(int time, void* ePayload);
HTN* createHTN(HLN* lItem);
HLN* findMin(HDS* hds, int eTime);


HDS* createHenrik(int pSize)
{
	//Alloc new object
	HDS* temp = malloc(sizeof(HDS));
	temp->pSize = pSize;

	//Create the dummy list items
	temp->lHead = createHLN(INT_MIN, NULL);
	temp->lTail = createHLN(INT_MAX, NULL);
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
void destroyHenrik(HDS* hds) { return; }

void insertEvent(HDS* hds, int eTime, void* payload)
{
	HLN* temp = createHLN(eTime, payload);
	//Find smallest time > eTime
	HLN* rItem = findMin(hds, eTime);
	HLN* lItem = rItem->lPrev;
	//Insert the new item
	temp->lPrev = lItem;
	temp->lNext = rItem;

	lItem->lNext = temp;
	rItem->lPrev = temp;

}

HLN* findMin(HDS* hds, int eTime)
{
	HTN* tNode = hds->tRoot;

	//Search tree
	while(1)
	{
		if(eTime >= tNode->lItem->eTime)
		{
			tNode = tNode->rChild;
		} else
		{
			if(tNode->lChild == NULL)
				break;
			tNode = tNode->lChild;
		}
	}
	int nCount = 0;
	//Search starting at node provided
	HLN* max = tNode->lItem;
	while(max->eTime >= eTime)
	{
		//Pull if necessary
		if(nCount > 4)
		{
			tNode->lowNode->lItem = max;
		}

		max = max->lPrev;
		nCount++;
	}

	return max->lNext;
}



/*-------------------------------------------------------*/
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

