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
	float eTime;
	void* ePayload;
};
//Tree Node
struct HTN
{
	HTN* lChild;
	HTN* rChild;
	HTN* lowNode;
	HLN* lItem;
	float eTime;
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
void insertEvent(HDS* hds, float eTime, void* payload);

float peek(HDS* hds);

void* deQueue(HDS* hds);
void* delete(HDS* hds, float eTime);


#endif
