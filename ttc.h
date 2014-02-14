// ttc.h- header file for our TTC simulation
// Elizabeth Patitsas; January 22, 2013
// You will NOT need to alter this file!

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

// Passenger elements

struct passenger
{
	int waiting; // how many minutes the person has been waiting
	struct passenger *next;	
};

struct passenger* make_passenger();
void insert_passenger_after(struct passenger *node, struct passenger *new_node);
int num_passengers(struct passenger *first);
void print_passenger(struct passenger *node);
void print_passenger_list(struct passenger *first);
void remove_first_passenger(struct passenger **node);
void clear_passenger_list(struct passenger **first);
void increment_passenger_list(struct passenger *first);
double average_passenger_list(struct passenger *first);


// Train elements

struct train{
    int id; // id number of the train
    int pos; // position on track in km
    struct train *next; // a pointer to the next train
};

int contains_train_id(struct train *first, int value);
struct train* make_train(int iden, int position);
void prepend_train(struct train **first, struct train *new_node);
void print_train(struct train *node);
void print_trains(struct train *first);
int can_advance(struct train *current, int passengers_on_platform);
void advance_train(struct train *current, int passengers_on_platform);
int num_trains(struct train *first);
double avg_train_dist(struct train *first);
void remove_train_after(struct train *node);
void clear_all_trains(struct train **first);
struct train* get_last_train(struct train *first);
int train_at_position(struct train *first, int pos);


// Station stuff

struct station{
	char *name;
	int pos; // position on track. Should not change.
	struct passenger *passengers; // pointer to first element in list
	struct station *next; // next station on the track (east)
	struct station *prev; // next station on the track (west) 
};

struct station* make_station(char *name, int pos); // given to students
void print_station(struct station *current); // given to students
void print_stations(struct station *first); // given to students
int passengers_at_station(struct station *curr); // given to students

void insert_station_after(struct station *node, struct station *new_node); 
struct station* read_stations();
void add_passenger(struct station *curr_station);
void add_n_passengers(struct station *curr_station, int n);
int total_passengers(struct station *first);
double average_wait_time(struct station *first);
struct station* get_station_at_pos(int position, struct station *first);
void remove_all_stations(struct station **first);


