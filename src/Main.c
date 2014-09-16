#include <stdio.h>
#include <stdlib.h>

#include "Henriksen.h"

void printList(HDS* hds);
void printInOrder(HTN* root);

int main(void)
{
	HDS* hds = createHenrik(0);

	printInOrder(hds->tRoot);

	insertEvent(hds, 20, NULL);
	insertEvent(hds, 10, NULL);
	insertEvent(hds, 5, NULL);
	insertEvent(hds, 4, NULL);
	insertEvent(hds, 3, NULL);
	insertEvent(hds, 2, NULL);

	printInOrder(hds->tRoot);

	//insertEvent(hds, 15, NULL);


	printList(hds);

	return 0;
}


void printInOrder(HTN* root)
{
	if(root->lChild != NULL)
		printInOrder(root->lChild);
	printf("%i\n", root->lItem->eTime);
	if(root->rChild != NULL)
		printInOrder(root->rChild);
}

//Print the list of items in descending order
void printList(HDS* hds)
{
	HLN* temp = hds->lTail;

	while(temp != NULL)
	{
		printf("%i\n", temp->eTime);
		temp = temp->lPrev;
	}
	return;
}
