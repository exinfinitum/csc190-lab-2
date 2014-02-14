// station.c -- simulates a doubly-linked list of TTC stations
// Bryon Leung and Rami Abu Shammeh, February 4 2013
#include "ttc.h"

struct station* make_station(char *name, int pos)
{
	// Creates a new station node in our doubly-linked list, setting its name and position to name and pos.
	// The new node is unlinked (prev and next are both NULL).
	// PRE: none
	// POST: none

	struct station *new_node = (struct station*) malloc(sizeof(struct station));
	new_node->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
	strcpy(new_node->name, name);

	new_node->pos = pos;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->passengers = NULL;

	return new_node;
}

int passengers_at_station(struct station *curr_station)
{
	// Number of passengers waiting at a given station, curr_station. If station == NULL, returns 0.
	// PRE: none
	// POST: none

	if(curr_station && curr_station->passengers)
	{
		return num_passengers(curr_station->passengers);
	}

	return 0;
}

void print_station(struct station *current)
{
	// Prints a single station. If current == NULL, prints "No station. \n".
	// PRE: none.
	// POST: none
	if(!current)
	{
		printf("No station. \n");
	}
	else
	{
		if(current->prev)
		{
			printf("%13s -> ", current->prev->name);
		}
		else
		{
			printf("                 ");
		}

		printf("%s (%d)", current->name, num_passengers(current->passengers) );
		if(current->next)
		{
			printf("-> %-13s \n", current->next->name);
		}
		else
		{
			printf("\n");
		}
	}
}

void print_stations(struct station *first)
{
	// Prints all stations in a linked list
	// PRE: none
	// POST: none

	printf("\nThe stations: \n");
	struct station *curr = first;
	while(curr)
	{
		print_station(curr);
		curr = curr->next;
	}
}


// The functions beneath this line are for students to implement.

void insert_station_after(struct station *node, struct station *new_node)
{
	// Inserts a station pointed at by new_node after the station pointed at by node.
	// PRE: node != NULL && new_node != NULL.
	// POST: none
	
	//DOES NOT CREATE ANY STATIONS!
	//Link the new node
	new_node->prev = node;
	//Link the node after new node (if there is one)
	if (node->next)
	{
		new_node->next = node->next;
		node->next->prev = new_node;
	}

	node->next = new_node;
}

struct station* read_stations()
{
	// Creates a linked list of stations as defined in bloor_line.txt and returns a pointer to first station in that list.
	// PRE: bloor_line.txt is in the same directory as this file and contains stations in the format: Name (pos), where position is
	// an integer, and stations are separated by newlines.
	// POST: a pointer to the first element of a doubly-linked list is returned

	//Open file and define read in variables.
	FILE *fr;
	fr = fopen("bloor_line.txt", "r");
	char name[20];
	int posn;
	//Define three station pointers we will use to work with the station creation
	struct station *new_station;
	struct station *first_station;
	struct station *old_station = NULL;

	//For every line in file:
	while (fscanf(fr, "%s %d", name, &posn) != EOF)
	{
		//Create a new station
		new_station = make_station(name, posn);
		
		//If we have a station before, we insert after
		if (old_station)
		{
			insert_station_after(old_station, new_station);
		}
		//Else we assign this as the first station
		else
		{
			first_station = new_station;
		}

		//The station we just made will be the 'old' station for the next one we'll make
		old_station = new_station;
	}
	//Close the file and return a pointer to the first station
	fclose(fr);
	return first_station;
}

void add_passenger(struct station *curr_station)
{
	// Adds a passenger to a station.
	// PRE: curr_station != NULL.
	// POST: none

	struct passenger *curr_passenger = curr_station->passengers;		
	curr_station->passengers = make_passenger();
	if (curr_passenger)
	{
		curr_station->passengers->next = curr_passenger;
	}
}

void add_n_passengers(struct station *curr_station, int n)
{
	// Adds n passengers to a station, by running a loop on add_passenger.
	// PRE: curr_station != NULL and n >= 0
	// POST: none

	int x;	
	for (x = 0; x < n; x++)
	{
		add_passenger(curr_station);
	}
}

int total_passengers(struct station *first)
{
	// Returns the total number of passengers in all stations in the linked list whose first element is pointed at by first.
	// PRE: none
	// POST: none

	int counter = 0;
	struct station *curr_stn;
	struct passenger *curr_psngr;
	//For every station, go through the list of passengers, and loop through that list, incrementing counter by one for each passenger.
	for (curr_stn = first; curr_stn != NULL; curr_stn = curr_stn->next)
	{

		for(curr_psngr = curr_stn->passengers; curr_psngr != NULL; curr_psngr = curr_psngr->next)
		{
			counter++;
		}
	}
	return counter;
}

double average_wait_time(struct station *first)
{
	// Returns the average wait time of all passengers in all stations in the linked list whose first element is pointed at by first.
	// PRE: none
	// POST: returns an integer

	double total_wait_time = 0;
	//First we get the number of passengers in all stations
	int num_psngrs = total_passengers(first);

	struct station *curr_stn;
	struct passenger *curr_psngr;

	for (curr_stn = first; curr_stn != NULL; curr_stn = curr_stn->next)
	{
		//loops through each station and each passenger within each station and increments total_wait_time
		//with the waiting time of each passenger struct.
		for(curr_psngr = curr_stn->passengers; curr_psngr != NULL; curr_psngr = curr_psngr->next)
		{
			total_wait_time += curr_psngr->waiting;
		}
	}

	//Divide total wait time by number of passengers
	return total_wait_time/num_psngrs;
}

struct station* get_station_at_pos(int position, struct station *first)
{
	// Returns station at the position indicated by position in the linked list whose first element is pointed to by first.
	// If no such station exists, returns NULL.
	// PRE: none
	// POST: returns a pointer

	struct station *curr_stn;
	//Go through all stations starting with *first until we get the station with the requested position. Then we return that value (and terminate the function).
	//If none exist, we exit the loop and return NULL
	for (curr_stn = first; curr_stn != NULL; curr_stn = curr_stn->next)
	{
		if(position == curr_stn->pos)
		{
			return curr_stn;
		}
	}

	return NULL;
}

void remove_all_stations(struct station **first)
{
	// Removes all stations and associated passenger lists in the linked list of stations whose pointer is pointed at by first.
	// Also sets the first pointer to NULL.
	// PRE: none
	// POST: all stations in linked list are freed

	//For all stations: free the passengers and name, then free the station.
	struct station *current;
	struct station *old;
	struct passenger **pass_list;
	for (current = *first; current != NULL;)
	{
		//Clear psngr list
		pass_list = &(current->passengers);
		clear_passenger_list(pass_list);
		//Free name
		free(current->name);

		//Advance the station manually here BEFORE FREEING STATION, to avoid a null pointer error.
		old = current;
		current = current->next;
		free(old);
	}
	*first = NULL;
}
