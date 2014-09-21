#include <stdio.h>
#include <stdlib.h>

#include "Henriksen.h"

void printList(HDS* hds);
void printInOrder(HTN* root);


int main(void)
{
	//char *data = "Hello Event Driven World\n";

	HDS* hds = createHenrik();
	printf("Created a new HDS at 0x%X\n", (unsigned int)hds);

	insertEvent(hds, 5, NULL);
	printf("There is now an event at time %i\n", peek(hds));

	char* temp = deQueue(hds);
	printf("DeQueuing event. Payload was: %s\n", temp);


	insertEvent(hds, 5, NULL);
	insertEvent(hds, 5, NULL);
	insertEvent(hds, 5, NULL);
	insertEvent(hds, 5, NULL);
	insertEvent(hds, 5, NULL);
	insertEvent(hds, 4, NULL);

	/*
	printf("First batch\n");
	int x;
	for(x = 2; x <= 100; x += 2 )
	{
		insertEvent(hds, x, (void *)x);
	}
	printf("Second Batch\n");
	for(x = 1; x <= 100; x += 2 )
	{
		insertEvent(hds, x, (void *)x);
	}
	printf("Delete Batch\n");
	for(x = 1; x <= 100; x += 3 )
	{
		delete(hds, x);
	}
	*/

	destroyHenrik(hds);

	return 0;
}


void printInOrder(HTN* root)
{
	if(root->lChild != NULL)
		printInOrder(root->lChild);
	printf("%i, ", root->eTime);
	if(root->rChild != NULL)
		printInOrder(root->rChild);
}


//Print the list of items in descending order
void printList(HDS* hds)
{
	HLN* temp = hds->lTail;

	while(temp != NULL)
	{
		printf("%i, ", temp->eTime);
		temp = temp->lPrev;
	}
	printf("\n");
	return;
}
