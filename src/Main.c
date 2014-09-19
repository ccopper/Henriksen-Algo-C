#include <stdio.h>
#include <stdlib.h>

#include "Henriksen.h"

void printList(HDS* hds);
void printInOrder(HTN* root);


int main(void)
{
	//char *data = "Hello Event Driven World\n";

	HDS* hds = createHenrik();
	//printf("Created a new HDS at 0x%X\n", (unsigned int)hds);

	/*insertEvent(hds, 5, NULL);
	printf("There is now an event at time %i\n", peek(hds));

	char* temp = deQueue(hds);
	printf("DeQueuing event. Payload was: %s", temp);
	*/


	int x;
	for(x = 100; x > 0; x -= 2 )
	{
		insertEvent(hds, x, (void *)x);
	}




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
