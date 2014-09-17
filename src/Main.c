#include <stdio.h>
#include <stdlib.h>

#include "Henriksen.h"

void printList(HDS* hds);
void printInOrder(HTN* root);

int main(void)
{
	HDS* hds = createHenrik();

	printInOrder(hds->tRoot);

	expandTree(hds->tRoot, 1);

	printInOrder(hds->tRoot);






	destroyHenrik(hds);

	return 0;
}


void printInOrder(HTN* root)
{
	if(root->lChild != NULL)
		printInOrder(root->lChild);
	printf("%i\n", root->eTime);
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
