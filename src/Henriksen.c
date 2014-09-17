
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>


#include "Henriksen.h"

#define nullNode(tNode) tNode->lItem = NULL; tNode->eTime = INT_MIN;
#define copyNode(oNode,nNode) nNode->lItem = oNode->lItem; nNode->eTime = oNode->eTime;

//Defaults for the structs
struct HLN HLNDef = {NULL, NULL, INT_MIN, NULL};
struct HTN HTNDef = {NULL, NULL, NULL, NULL, INT_MIN};

//Internal Functions
HLN* createHLN(int time, void* ePayload);
HTN* createHTN(HLN* lItem, int eTime);
HLN* findMin(HDS* hds, int eTime);

void freeTree(HTN* root);
void expandTree(HTN* root, int firstCall);


HDS* createHenrik()
{
	//Alloc new object
	HDS* temp = malloc(sizeof(HDS));

	//Create the dummy list items
	temp->lHead = createHLN(INT_MIN, NULL);
	temp->lTail = createHLN(INT_MAX, NULL);
	temp->lHead->lNext = temp->lTail;
	temp->lTail->lPrev = temp->lHead;

	//Create the default tree
	temp->tRoot = createHTN(temp->lTail, 0);


	return temp;
}

void destroyHenrik(HDS* hds)
{
	freeTree(hds->tRoot);

	HLN* temp = hds->lHead;

	while(temp->lNext != NULL)
	{
		temp = temp->lNext;
		free(temp->lPrev);
	}

	free(temp);
	free(hds);
	return;
}

void insertEvent(HDS* hds, int eTime, void* payload)
{
	if(eTime == INT_MIN || eTime == INT_MAX )
		return;
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

void* deQueue(HDS* hds)
{
	HLN* lItem = hds->lHead->lNext;
	if(lItem->eTime == INT_MAX)
		return NULL;

	hds->lHead->lNext = lItem->lNext;
	lItem->lNext->lPrev = hds->lHead;

	void* temp = lItem->ePayload;
	free(lItem);
	return temp;
}

void* delete(HDS* hds, int eTime)
{
	HLN* lItem = findMin(hds, eTime);
	if(lItem->eTime != eTime || lItem->eTime == INT_MAX || lItem->eTime == INT_MIN)
		return NULL;

	lItem->lNext->lPrev = lItem->lPrev;
	lItem->lPrev->lNext = lItem->lNext;

	void* temp = lItem->ePayload;
	free(lItem);
	return temp;
}



void freeTree(HTN* root)
{
	if(root->lChild != NULL)
		freeTree(root->lChild);
	if(root->rChild != NULL)
		freeTree(root->rChild);
	free(root);
}

HLN* findMin(HDS* hds, int eTime)
{
	HTN* tNode = hds->tRoot;

	//Search tree
	while(1)
	{
		if(eTime >= tNode->eTime)
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
		if(nCount > DIST_MAX)
		{
			//Check to see if we overflowed the tree
			//Only expand once though
			if(tNode->lowNode == NULL && nCount == 5)
			{
				expandTree(hds->tRoot, 1);
			}
			//Update the pull pointer
			tNode->lowNode->lItem = max;
			//Reset the count and do another pull if necessary
			tNode = tNode->lowNode;
			nCount = 0;
		}

		max = max->lPrev;
		nCount++;
	}



	return max->lNext;
}

void expandTree(HTN* root, int isFirstCall)
{
	//Pointer to track the last node encountered
	static HTN* prevNode = NULL;
	//if its the first call
	if(isFirstCall)
		prevNode = NULL;

	//Check right child exists or create it
	if(root->rChild == NULL)
	{
		root->rChild = createHTN(NULL, INT_MIN);
		//Check to see if this is the rightmost node
		if(prevNode != NULL)
		{
			prevNode->lowNode = root->rChild;
		} else
		{
			copyNode(root, root->rChild);
			nullNode(root);
		}
		//update the previous node to the new one
		prevNode = root->rChild;
	} else
	{
		//Not a old leaf so travel down
		expandTree(root->rChild, 0);
	}
	//update the previous node's low pointer
	prevNode->lowNode = root;

	//update the low pointer and proceed
	prevNode = root;
	if(root->lChild == NULL)
	{
		root->lChild = createHTN(NULL, INT_MIN);
		prevNode->lowNode = root->lChild;
		prevNode = root->lChild;
	} else
	{
		expandTree(root->lChild, 0);
	}

}


HLN* createHLN(int time, void* ePayload)
{
	HLN* temp = malloc(sizeof(HLN));
	memcpy(temp, &HLNDef, sizeof(HLN));
	temp->eTime = time;
	temp->ePayload = ePayload;
	return temp;
}
HTN* createHTN(HLN* lItem, int eTime)
{
	HTN* temp = malloc(sizeof(HTN));
	memcpy(temp, &HTNDef, sizeof(HTN));
	temp->lItem = lItem;

	if(lItem == NULL)
	{
		temp->eTime = eTime;
	} else
	{
		temp->eTime = lItem->eTime;
	}
	return temp;
}

