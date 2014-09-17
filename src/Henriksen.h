#ifndef HENRIKSEN_H
#define HENRIKSEN_H

#define DIST_MAX 4

typedef struct HLN HLN;
typedef struct HTN HTN;
//Linked List Node
struct HLN
{
	HLN* lNext;
	HLN* lPrev;
	int eTime;
	void* ePayload;
};
//Tree Node
struct HTN
{
	HTN* lChild;
	HTN* rChild;
	HTN* lowNode;
	HLN* lItem;
};

//RootNode / LL head
typedef struct
{
	HLN* lHead;
	HLN* lTail;
	HTN* tRoot;
} HDS;

//Create a new Henriksen with the given payload size
HDS* createHenrik();
//Destroy the list and dealloc memory
void destroyHenrik(HDS* hds);
//Inserts a new event into the tree
void insertEvent(HDS* hds, int eTime, void* payload);



#endif
