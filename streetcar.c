// ttc.c - simulates the Bloor-Danforth line of the TTC
// Elizabeth Patitsas + Bryon Leung and Rami Abu Shammeh, February 4 2012

#include "ttc.h"

#define SPADINA 36
#define YONGE 42

#define MAX_POS 82

#define MAX_LOAD 500
#define TRAIN_GAP 5

// these control the behaviour of the program and are for
// students to play with
#define DEBUGGING 0
#define SIM_TIME 60*100

void advance_time(struct station *kipling, struct train **first);
void passengers_wait(struct station *kipling); // STUDENT TODO
void add_trains(struct train **first);
int num_arriving_passengers(struct station *curr);
void enter_passengers(struct station *kipling); // STUDENT TODO
void load_trains(struct station *kipling, struct train **first); 
void advance_trains(struct station *kipling, struct train **first);
void print_track(struct station *first_station, struct train **first_train, int time, int print_track);


void advance_time(struct station *kipling, struct train **first)
{
	// Simulates one minute of the Bloor-Danforth line
	// PRE: *kipling, *first, **first all are not null, there is more than one train on the track
	// POST: the stations and trains will be altered: trains will advance, stations' passengers will increase/decrease

	assert(kipling);
	assert(first);
	assert(*first);
	assert((*first)->next);

	// increment passenger waiting times
	passengers_wait(kipling);

	// add trains if appropriate
	add_trains(first);

	// passengers arrive
	enter_passengers(kipling);

	// load the trains
	load_trains(kipling, first);

	// first advance any trains that can move; delete any that advance into position 83
	advance_trains(kipling, first);
}

void passengers_wait(struct station *kipling)
{
	//this increments each passenger's waiting time by one minute, at every station.
	//PRE: none
	//POST: none
	struct station *current;
	//Run increment_passenger_list on each station
	for (current = kipling; current != NULL; current = current->next)
	{
		if (current->passengers)
		{
			increment_passenger_list(current->passengers);
		}
	}

}

void add_trains(struct train **first)
{
	// adds trains to the track every time the westmost train 		// gets to position = TRAIN_GAP
	// PRE: *first != NULL
	// POST: first will be altered if a new train is added
	assert(*first);

	// non-stochastic approach
	// if the newest train has gotten to TRAIN_GAP, then add a new one
	if( (*first)->pos == TRAIN_GAP )
	{
		// then we add a new train at pos 0.
		int id = (*first)->id + TRAIN_GAP;
		struct train *new_train = make_train(id, 0);
		prepend_train(first, new_train);
	}
}

int num_arriving_passengers(struct station *curr)
{
	// Adds a number of new passengers
	// If downtown, adds between 1 and 300 passengers; else between 0 and 100.
	// PRE: none
	// POST: none

	int max = 100; // default (non-downtown)
	int min = 0;

	// if downtown, adjust the min/max of the random numbers
	if(curr->pos >= SPADINA && curr-> pos <= YONGE) 
	{
		max = 300;
		min = 1;
	}

	// and return a value between (max, min)
	return (rand() % max + min);
}

void enter_passengers(struct station *kipling)
{
	//for each station, curr_station, this adds num_arriving_passengers many passengers to the station.
	//PRE: none
	//POST: none
	struct station *current;
	//We add, to each station, the number of passengers the the function
	//num_arriving_passengers gives for the station
	for (current = kipling; current != NULL; current = current->next)
	{
		add_n_passengers(current, num_arriving_passengers(current));
	}
}

void load_trains(struct station *kipling, struct train **first)
{
	// Loads at most MAX_LOAD many passengers from each station that has a train at it
	// PRE: none
	// POST: stations' passengers will have decreased

	struct train *curr_train = *first;
	while(curr_train)
	{
		// is there a station at this train's position?
		struct station *curr_station = get_station_at_pos(curr_train->pos, kipling);	

		if(curr_station)
		{
			// then we need to load our train
			struct passenger **passgrs = &(curr_station->passengers);
			int num_passeng = num_passengers(*passgrs);

			if(*passgrs && num_passeng <= MAX_LOAD)
			{
				clear_passenger_list( passgrs );
			}
			else if(*passgrs)
			{
				// remove MAX_LOAD many passengers
				int i;
				for(i = 0; i < MAX_LOAD; i++)
				{
					remove_first_passenger( passgrs );
				}
			}
		}
	
		curr_train = curr_train->next;
	}
}

void advance_trains(struct station *kipling, struct train **first)
{
	// Advance every train on the track (if it can be advanced)
	// PRE: *first != NULL and there is more than one train on the track
	// POST: the trains' positions will be incremented
	assert(*first);
	assert((*first)->next);

	struct train *curr = *first;
	struct train *prev = NULL;
	while(curr)
	{
		if(curr->pos >= MAX_POS + 1)
		{
			// delete the train when it gets to position 83
			prev->next = NULL;
			free(curr);
			return;
		}
		else
		{
			// otherwise, the train is on the track and we should advance it
			int num_pass = 0;
			struct station *curr_station = get_station_at_pos(curr->pos, kipling);	
			if(curr_station)
			{
				num_pass = num_passengers(curr_station->passengers);
			}

			advance_train(curr, num_pass);

			prev = curr;
			curr = curr->next;
		}
	}
}

void print_track(struct station *first_station, struct train **first_train, int time, int print_track)
{
	// prints the TTC Bloor-Danforth Track
	// PRE: none
	// POST: none

	int i = 0;
	struct station *curr_station = first_station;
	struct train *curr_train = *first_train;
	while(i <= MAX_POS && curr_station && print_track == 1)
	{
		printf("%2d: ", i);

		// print a train
		if(curr_train && curr_train->pos == i)
		{
			printf("   [t%3d] ", curr_train->id);
			curr_train = curr_train->next;
		}
		else
		{
			printf("     ||  ");
		}

		// print a station
		if(curr_station->pos == i)
		{
			int num_waiting = passengers_at_station(curr_station);
			printf("= (n = %d, avg = %.1lf) %s", num_waiting, average_passenger_list(curr_station->passengers), curr_station->name);
			curr_station = curr_station->next;
		}

		printf("\n");
		i++;
	}
	// now print some information: average wait time of passengers, number of trains on track, average distance between trains
	printf("---------- ANALYTICS --------\n");
	printf("Simulated time elapsed (min): %d \n", time );
	printf("Total number of passengers: %d \n", total_passengers(first_station) );
	printf("Average wait time of passengers (in min): %lf \n", average_wait_time(first_station) );
	printf("Total number of trains: %d \n", num_trains(*first_train) );
	printf("Average distance between trains (in km): %lf \n", avg_train_dist(*first_train) );
}


void test_cases_for_students(struct station *kipling, struct train *first)
{
	// test cases for students
	
	// Test 1. enter passengers
	enter_passengers(kipling);
	print_track(kipling, &first, 0, 1); // if enter_passengers is working you should see something including:
	/*
		38:      ||  = (n = 227, avg = 0.0) StGeorge
		39:      ||  
		40:      ||  = (n = 241, avg = 0.0) Bay
		41:      ||  
		42:      ||  = (n = 127, avg = 0.0) Yonge
		43:      ||  
		44:      ||  = (n = 72, avg = 0.0) Sherbourne
		45:      ||  
		46:      ||  = (n = 36, avg = 0.0) CastleFrank
		47:      ||  
	*/

	// Test 2. passengers wait
	passengers_wait(kipling);	
	print_track(kipling, &first, 0, 1); // you should see all passengers have waited one minute
	enter_passengers(kipling);
	print_track(kipling, &first, 0, 1); // now you should see something like:
	/*
		38:      ||  = (n = 326, avg = 0.7) StGeorge
		39:      ||  
		40:      ||  = (n = 466, avg = 0.5) Bay
		41:      ||  
		42:      ||  = (n = 343, avg = 0.4) Yonge
		43:      ||  
		44:      ||  = (n = 142, avg = 0.5) Sherbourne
		45:      ||  
		46:      ||  = (n = 49, avg = 0.7) CastleFrank
		47:      ||  
	*/
}

int main()
{
	// Simulate the TTC!
	// To keep things consitent, we'll use a predefined seed of 1
	srand(1);

	// we'll be outputting data to a file called data.csv
	FILE *file;
	file = fopen("data.csv","w+");

	// set up our first station and first two trains 
	struct station *kipling = read_stations();
	struct train *first = make_train(5, 0);
	struct train *second = make_train(0, 5);
	first->next = second;

	if(DEBUGGING == 1)
	{
		printf("BEGINNING TEST\n");
		test_cases_for_students(kipling, first);
	}
	else
	{
		// if we're not debugging, then simulate!
		fprintf(file, "time, avg_wait, num_trains, avg_dist\n");
		int i = 0;
		for(i = 0; i < SIM_TIME; i++)
		{
			advance_time(kipling, &first);
			// print data every half hour
			if(i % 30 == 0)
			{
				fprintf(file, "%d, %lf, %d, %lf\n", i, average_wait_time(kipling), num_trains(first), avg_train_dist(first));
			}
		}

		print_track(kipling, &first, i, 1);
	}

	// cleanup
	clear_all_trains(&first);
	remove_all_stations(&kipling);
	fclose(file);
	return 0;
}
