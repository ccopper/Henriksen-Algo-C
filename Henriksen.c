
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#include "Henriksen.h"

#define nullNode(tNode) tNode->lItem = NULL; tNode->eTime = FLT_MIN;
#define copyNode(oNode,nNode) nNode->lItem = oNode->lItem; nNode->eTime = oNode->eTime;

//Defaults for the structs
struct HLN HLNDef = {NULL, NULL, FLT_MIN, NULL};
struct HTN HTNDef = {NULL, NULL, NULL, NULL, FLT_MIN};

//Internal Functions
HLN* createHLN(float eTime, void* ePayload);
HTN* createHTN(HLN* lItem, float eTime);

HTN* findMinTree(HDS* hds, float eTime);
HLN* findMinList(HDS* hds, HTN* tNode, float eTime);

void printInOrder(HTN* root);
void freeTree(HTN* root);
void expandTree(HTN* root, int firstCall);


HDS* createHenrik()
{
	//Alloc new object
	HDS* temp = malloc(sizeof(HDS));

	//Create the dummy list items
	temp->lHead = createHLN(FLT_MIN, NULL);
	temp->lTail = createHLN(FLT_MAX, NULL);
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

void insertEvent(HDS* hds, float eTime, void* payload)
{
	if(eTime == FLT_MIN || eTime == FLT_MAX )
		return;

//	printf("insertEvent(hds, %f, NULL);\n", eTime);
//	fflush(stdout);

	HLN* temp = createHLN(eTime, payload);
	//Find smallest time > eTime
	HTN* tNode = findMinTree(hds, eTime);
//	if(tNode == NULL)
//		printInOrder(hds->tRoot);
//	fflush(stdout);
	HLN* rItem = findMinList(hds, tNode, eTime);

//if(rItem == NULL)
//		printInOrder(hds->tRoot);
//	fflush(stdout);

	HLN* lItem = rItem->lPrev;
	//Insert the new item
	temp->lPrev = lItem;
	temp->lNext = rItem;

	lItem->lNext = temp;
	rItem->lPrev = temp;

}

float peek(HDS* hds)
{
	HLN* lItem = hds->lHead->lNext;
	if(lItem->eTime == FLT_MAX)
		return FLT_MIN;
	else
		return lItem->eTime;
}

void* deQueue(HDS* hds)
{

	HLN* lItem = hds->lHead->lNext;
	if(lItem->eTime == FLT_MAX)
		return NULL;

	//printf("deQueue(hds); //T=%f\n", lItem->eTime);
	//fflush(stdout);


	hds->lHead->lNext = lItem->lNext;
	lItem->lNext->lPrev = hds->lHead;

	void* temp = lItem->ePayload;
	free(lItem);
	return temp;
}

void* delete(HDS* hds, float eTime)
{
	HTN* tNode = findMinTree(hds, eTime);
	HLN* lItem = findMinList(hds, tNode, eTime);

	if(lItem->eTime != eTime || lItem->eTime == FLT_MAX || lItem->eTime == FLT_MIN)
		return NULL;

	//Check to see if this list item is in the tree
	if(tNode ->lowNode != NULL && tNode->lowNode->lItem == lItem)
	{
		//Traverse backwards until we find another node with value
		HTN* temp = tNode->lowNode->lowNode;
		while(temp == NULL || temp->eTime == FLT_MIN)
			temp = temp->lowNode;

		if(temp != NULL)
		{
			copyNode(temp, tNode->lowNode);
			nullNode(tNode);
		}

	}

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

HTN* findMinTree(HDS* hds, float eTime)
{
	HTN* tNode = hds->tRoot;
	HTN* target = NULL;
	//printf("T: %f\n", eTime);
	//printf("S: %f\n", tNode->eTime);
	//Search tree
	while(1)
	{
		if(eTime >= tNode->eTime)
		{
			if(tNode->rChild == NULL)
				break;
			tNode = tNode->rChild;
			//printf("R: %f\n", tNode->eTime);
		} else
		{
			if(target == NULL || (target->eTime > tNode->eTime && tNode->eTime > eTime))
			{
				//printf("M: %f\n", tNode->eTime);
				target = tNode;
			}
			if(tNode->lChild == NULL)
				break;

			tNode = tNode->lChild;
			//printf("L: %f\n", tNode->eTime);
		}
	}
//	printf("E: %f\n", tNode->eTime);
	//printf("B: %f\n", target->eTime);
	//printInOrder(hds->tRoot);
	return target;
}



HLN* findMinList(HDS* hds, HTN* tNode, float eTime)
{
	int nCount = 0;
	//Search starting at node provided
	HLN* max = tNode->lItem;

	//printf("S: %f\n", max->eTime);

	while(max->eTime >= eTime)
	{
		//printf("T: %f\n", max->eTime);

		//Pull if necessary
		if(nCount > DIST_MAX)
		{
			//printf("PRE: ");
			//printLTH(hds);

			//Check to see if we overflowed the tree
			//Only expand once though
			if(tNode->lowNode == NULL && nCount == 5)
			{
				//If this is the rightmost node we will have
				//to save the node
				if(tNode->eTime == FLT_MAX)
				{
					expandTree(hds->tRoot, 1);

					tNode = tNode->rChild;
				} else
				{
					expandTree(hds->tRoot, 1);
				}
				//printf("E");
			}

			//Reset the count and do another pull if necessary
			tNode = tNode->lowNode;
			//Update the pull pointer
			tNode->lItem = max;
			tNode->eTime = max->eTime;

			nCount = 0;

			//printf("PST: ");
			//printLTH(hds);
			//printf("\n");
		}
		//printf("N: %i\n", max->eTime);

		max = max->lPrev;
		nCount++;
	}

	//printf("E: %f\n", max->lNext->eTime);
	fflush(stdout);

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
		root->rChild = createHTN(NULL, FLT_MIN);
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
		root->lChild = createHTN(NULL, FLT_MIN);
		prevNode->lowNode = root->lChild;
		prevNode = root->lChild;
	} else
	{
		expandTree(root->lChild, 0);
	}

}

//Creates a new list node
HLN* createHLN(float eTime, void* ePayload)
{
	HLN* temp = malloc(sizeof(HLN));
	memcpy(temp, &HLNDef, sizeof(HLN));
	temp->eTime = eTime;
	temp->ePayload = ePayload;
	return temp;
}
//Create a new tree node
HTN* createHTN(HLN* lItem, float eTime)
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


void printInOrder(HTN* root)
{
	if(root->lChild != NULL)
		printInOrder(root->lChild);
	printf("%f, ", root->eTime);
	if(root->rChild != NULL)
		printInOrder(root->rChild);
}


