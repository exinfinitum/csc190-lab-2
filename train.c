// passenger.c -- implements a linked list of TTC subway trains
// YOURNAMEHERE, DATE

#include "ttc.h"
#include<stdio.h>
#include<stdlib.h>

struct train* make_train(int iden, int position)
{
//Creates a train structure, and returns a pointer to the struct
//PRE: none
//POST: returns a pointer to the train
	struct train *car = malloc(sizeof (struct train));
	car->next = NULL;
	car->id = iden;
	car->pos = position;
	return car;
}

int contains_train_id(struct train *first, int value)
{
//Checks to see if train linked list whose first element is pointed to by first contains a node with an id equal to value.
//Returns 1 if yes, 0 otherwise. If first is NULL, returns 0.
//PRE: first is a pointer to the first element in train linked list
//POST: returns 0 or 1
	int have_id = 0;
	struct train *curr;
	for(curr = first; curr != NULL; curr = curr->next)
	{
		if (curr->id == value)
		{
			have_id = 1;
		}

	}

	return have_id;
}

int train_at_position(struct train *first, int pos)
{
	// Returns 1 iff there exists a train at position pos (given to students)
	// PRE: none
	// POST: none
	struct train *curr = first;
	int contains_pos = 0;
	while(curr)
	{
		if(curr->pos == pos)
		{
			return 1;
		}

		curr = curr->next;
	}

	return contains_pos;
}

void prepend_train(struct train **first, struct train *new_node)
{
//Attaches a train in front of the first train in a linked list of train nodes
//PRE: first is a pointer to first element in train linked list
//POST: none
	int stop = 0;
	struct train *curr;
	for(curr = *first; curr->next != NULL; curr = curr->next)
	{
		if (curr->pos <= new_node->pos)
		{
			stop = 1;
		}

	}	

	assert(*first != NULL);
	assert(new_node != NULL);
	assert(stop != 1);
	new_node->next = *first;
	*first = new_node;
	//printf("First: %d, new: %d", (*first)->id, new_node->id);
	//assert (contains_train_id(*first, new_node->id) != 1);

	
}

void print_train(struct train *node)
{
	// This method is provided to students.
	// Prints a single train, and what it points to (if it points to another train)
	// PRE: node != NULL
	// POST: none
	assert(node);
	printf("Train %d at %d", node->id, node->pos);
	if(node->next)
	{
		printf("; next is %d at %d", node->next->id, node->next->pos);
	}

	printf("\n");
}

void print_trains(struct train *first)
{
//Prints all trains in the linked list whose first element is pointed to by first
//PRE: none
//POST: none
	printf("---------- The trains ---------- \n");
	struct train *curr;
	for(curr = first; curr != NULL; curr = curr->next)
	{
		print_train(curr);
	}	
}

int can_advance(struct train *current, int passengers_on_platform)
{
//Indicates if a train can be advanced safely. If so, returns 1, else returns 0.
//PRE: passengers_on_platform >= 0, and current != NULL
//POST: 1 or 0 is returned
	assert(current != NULL);
	assert(passengers_on_platform >= 0);
	int trains_clear = 0;
	if ((current->next))
	{
		//if(((current->next)->pos) > ((current->pos) ))// - 1))
		if(((current->next)->pos) > ((current->pos) + 1))
		{
			trains_clear = 1;
		}
	}
	//Below lines commented out during debugging	
	else if (current->next == NULL)
	{
		trains_clear = 1;
	}
	if(trains_clear && (passengers_on_platform == 0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void advance_train(struct train *current, int passengers_on_platform)
{
//Advances a train iff it can be advanced safely.
//PRE: passengers_on_platform >= 0, and current != NULL
//POST: none
	if ((can_advance(current, passengers_on_platform)) && (current != NULL))
	{
		current->pos++;
	}
}

int num_trains(struct train *first)
{
//Returns the number of trains in the linked list whose first element is pointed to by first
//PRE: none
//POST: none
	int count = 0;
	struct train *curr;
	for(curr = first; curr != NULL; curr = curr->next)
	{
		count++;
	}

	return count;
}

double avg_train_dist(struct train *first)
{
//Returns the average distance between the train cars
//PRE: none
//POST: none
	double total_dist = 0;
	double count = 0;
	if (first == NULL)
	{	
		return 0;
	}

	struct train *curr;
	for(curr = first; ((curr != NULL) && (curr->next != NULL)); curr = curr->next)
	{
		total_dist += (((curr->next)->pos - (curr->pos)) - 1);
		count++;
	}

	//total_dist -= num_trains(first);
	return total_dist / count;
}


void remove_train_after(struct train *node)
{
//Removes the train that comes after the element pointed to by node from the linked list
//PRE: node != NULL
//POST: none
	assert (node != NULL);
	struct train *after = node->next;
	node->next = after->next;
	free(after);
}

void clear_all_trains(struct train **first)
{
//Removes all trains from a linked list, where first is a pointer to a pointer pointing to the first element of the linked list
//PRE: none
//POST: none
	struct train *curr;
	struct train *deleteme;
	for(curr = *first; curr != NULL;)
	{
		deleteme = curr;
		curr = curr->next;
		free(deleteme);
	}	

	*first = NULL;
}
