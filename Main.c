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
	printf("There is now an event at time %f\n", peek(hds));

	char* temp = deQueue(hds);
	printf("DeQueuing event. Payload was: %s\n", temp);


	printf("First batch\n");
	int x;
	for(x = 100; x > 80; x -= 1 )
	{
		insertEvent(hds, x, (void *)x);
	}

	printInOrder(hds->tRoot);
	printf("\n");
	float y;
	for(y = 95; y > 92; y -= 0.3 )
	{
		insertEvent(hds, y, (void *)x);
	}
	printInOrder(hds->tRoot);
	//printList(hds);
	insertEvent(hds, 93.5, NULL);
	//printList(hds);

	//findMinTreeR(hds->tRoot, 94.5);

	/*
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




//Print the list of items in descending order
void printList(HDS* hds)
{
	HLN* temp = hds->lTail;

	while(temp != NULL)
	{
		printf("%f, ", temp->eTime);
		temp = temp->lPrev;
	}
	printf("\n");
	return;
}
