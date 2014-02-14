/*
#@*@&* ECF KILLED MY USB!


*/

#include "ttc.h"
#include<stdio.h>
#include<stdlib.h>

struct passenger* make_passenger()
{
//Creates a passenger structure, and returns a pointer to the struct
//PRE: none
//POST: returns a pointer to the passenger
	struct passenger *dude = malloc(sizeof (struct passenger));
	dude->waiting = 0;
	dude->next = NULL;
	return dude;
	
}

void insert_passenger_after(struct passenger *node, struct passenger *new_node)
{
//Inserts a passenger in the linked list after the passenger pointed to by node
//PRE: node != NULL and new_node != NULL
//POST: none
	assert ((node != NULL) && (new_node != NULL));
	node->next = new_node;
}


void print_passenger(struct passenger *node)
{
//Prints a passenger's waiting time. If node == NULL, prints NULL.
//PRE: none
//POST: none
	if (node != NULL)
	{
		printf("%d",node->waiting);
	}

	else
	{
		printf("NULL");
	}
}

void print_passenger_list(struct passenger *first)
{
//Prints the waiting times for all passengers in the linked list.
//PRE: none
//POST: none
	struct passenger *curr;
	printf("Waiting times: \n");
	for(curr = first; curr != NULL; curr = curr->next)
	{
		printf("%d\n", curr->waiting);
	}
}

void remove_first_passenger(struct passenger **first)
{

	//The node MUST be the first node, else null pointer exception!
	assert (*first != NULL);
	//store target node so we can delete it
	struct passenger *terminate = *first;
	
	*first = (*first)->next;
	free(terminate);
	
}

void clear_passenger_list(struct passenger **first)
{
	struct passenger *curr;
	struct passenger *deleteme;
	for(curr = *first; curr != NULL;)
	{
		deleteme = curr;
		curr = curr->next;
		free(deleteme);
	}

	*first = NULL;
}

void increment_passenger_list(struct passenger *first)
{
	struct passenger *curr;
	assert (first != NULL);
	for(curr = first; curr != NULL; curr = curr->next)
	{
		(curr->waiting)++;
	}
}

double average_passenger_list(struct passenger *first)
{
	struct passenger *curr;
	double sum = 0;
	double counter = 0;
	if (first != NULL)
	{	
		for(curr = first; curr != NULL; curr = curr->next)
		{
			sum += curr->waiting;
			counter++;
		}

		sum = sum / counter;
		return sum;
	}

	else
	{
		return -1;
	}
}

int num_passengers(struct passenger *first)
{
	struct passenger *curr;
	int counter = 0;
	if (first != NULL)
	{	
		for(curr = first; curr != NULL; curr = curr->next)
		{
			counter++;
		}

		return counter;
	}

	else
	{
		return -0;
	}
}
