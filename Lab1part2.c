// Programmer:			Zachary William Preston
// Date:			2020 September 22
// Course:			Intro to Operating Systems
// Description:			A discrete event simulator that will simulate the journey an event
//				in an operating system takes as it journeys through the priority Queue
//				to the CPU and then to an I/O device, or uses the CPU

// Preprocessor Directives
#include <stdio.h>
#include <stdlib.h>
#define TIME_START 0
#define TIME_END 100000
#define STAT_FILE "stats.txt"
#define FILE_ERROR "-->ERROR: File cannot be opened"
#define START_MESSAGE "Simulation Started....\n"
#define END_MESSAGE "Simulation Ended....\n"

// Structure of an event, the ID is to keep track of each event, the id
// of each event is unique, and is given using the counter for the for loop
//		priority-> 1, 2, or 3 where 1 is the highest priority
//		time-> the "timer" used to determine how many units of time
// 			is needed for event to run before it finishes and terminates
//		type-> determines whether event will use the CPU, will go to I/O, or
//			will use the network queue
//		Event *next-> used to implement the queue, in the form of a linked list
typedef struct Event {
	int id;
	int priority;
	int time;
	int type;
	struct Event *next;
} Event;

// Function Prototypes
void recordEvent(FILE *, Event *, int);
int getRandomTime();
int getRandomPriority();
int getRandomType();
Event *addNewEvent(int, int, int, int);
void printEventData(Event *);
void printEntireQueue(Event **);
void push(Event **, int, int, int, int);
Event *pop(Event **);

// Main method, where the invocation will take place
int main(int argc, char *argv[]) {
	// Each of the queues are precreated, and set to NULL initially
	Event *pQueue = NULL;
	Event *cpuQueue = NULL;
	Event *io = NULL;
	Event *network = NULL;
	// Count is used to keep track of all events created, is used for giving an ID to each event
	// Counters for the size of each Queue are used to keep track of how large the queues get
	int count;
	int pQueueSize = 0, cpuSize = 0, ioSize = 0, netSize = 0;
	// To prevent errors, the Priority Queue is precreated with a few events to prevent segemtation errors
	for (count = 0; count < 20; count++, pQueueSize++)
		push(&pQueue, count + 1, getRandomPriority(), getRandomTime(), getRandomType());
	// Each time an event terminates, it will be written to the STAT_FILE
	FILE *file = fopen( STAT_FILE, "w" );
	if (file == NULL) {
		printf( "%s\n", FILE_ERROR );
		exit(1);
	}
	fputs(START_MESSAGE, file);
	printf( "%s", START_MESSAGE );
	// Simulation begins here
	for (int time = TIME_START; time <= TIME_END; time++) {
		// New Event is being created at start of each unit of time
                push(&pQueue, count++, getRandomPriority(), getRandomTime(), getRandomType());
		Event *top = pop(&pQueue);
		// Event is getting taken out of priority queue, and placed into one of 3 queues,
		// depending on the type, type 1 is for CPU, type 2 is for I/O, type 3 is for Network
		// Each time it is added to one of the queues, the counter for that queue will increment
		if (top->type == 1) {
                        push(&cpuQueue, top->id, top->priority, top->time, top->type);
			cpuSize++;
		} else if (top->type == 2) {
			push(&io, top->id, top->priority, top->time, top->type);
			ioSize++;
		} else {
			push(&network, top->id, top->priority, top->time, top->type);
			netSize++;
		} free(top);
		// The first event in each queue will have it's timer decremented by one for each unit of time
		// if the time reaches 0, then the event has finished executing, and will terminate, the time will
		// be logged in the STAT_FILE
		if (cpuSize > 0) {
			cpuQueue->time--;
			if (cpuQueue->time == 0) {
				Event *temp = pop(&cpuQueue);
				printf( "Time %d || Event %d in CPU has finished executing\n", time, temp->id );
				recordEvent(file, temp, time);
				free(temp);
			}
		}
		if (ioSize > 0) {
			io->time--;
			if (io->time == 0) {
				Event *temp = pop(&io);
				printf( "Time %d || Event %d in IO has finished executing\n", time, temp->id );
				recordEvent(file, temp, time);
				free(temp);
			}
		}
		if (netSize > 0) {
			network->time--;
			if (network->time == 0) {
				Event *temp = pop(&network);
				printf( "Time %d || Event %d in Network has finished executing\n", time, temp->id );
				recordEvent(file, temp, time);
				free(temp);
			}
		}
	} fputs(END_MESSAGE, file);
	fclose(file);
	// Finally, the simulation ends
	printf( "%s", END_MESSAGE );
	return EXIT_SUCCESS;
}

// Records the event to the file at the point of termination, showing information about the event
// as well as marking down the time that the event terminated
void recordEvent(FILE *file, Event *event, int time) {
	char num[6];
	fputs("Time = ", file);
        sprintf(num, "%d", time);
	fputs(num, file);
	fputs(" || Event ", file);
	sprintf(num, "%d", event->id);
        fputs(num, file);
        fputs(" || ", file);
	if (event->type == 1)
	        fputs("CPU ", file);
	else if (event->type == 2)
		fputs("I/O ", file);
	else
		fputs("Network ", file);
        fputs("Event Priority: ", file);
        sprintf(num, "%d", event->priority);
        fputs(num, file);
        fputs("\n", file);
}

// Generates a random amount of time each time a new event is created, though this is likely
// not how it would work in real life
int getRandomTime() {
	return rand() % 10 + 10;
}

// Generates a random priority for each event that is created and pushed onto priority queue
int getRandomPriority() {
	return rand() % 3 + 1;
}

// Generates a random type for event, to determine what queue the event will enter into,
// CPU, network, or I/O
int getRandomType() {
	return rand() % 3 + 1;
}

// Creates a new event, allocates the space, and then assigns the value to each part of the structure
// then returns the event, setting the next to NULL, is changed later, when pushed onto queue
Event *addNewEvent(int id, int priority, int time, int type) {
	Event *event = (Event *) malloc (sizeof(Event));
	event->id = id;
	event->priority = priority;
	event->time = time;
	event->type = type;
	event->next = NULL;
	return event;
}

// Prints the data of a single event
void printEventData(Event *event) {
	printf( "ID = %3d\tPriority = %d\tTime = %2d\tType = %d\n", event->id, event->priority, event->time, event->type );
}

// Traverses an entire queue, and prints the data for each event in the queue
void printEntireQueue(Event **queue) {
	if ((*queue) == NULL) {
		printf( "Queue is empty\n" );
	} else {
		Event *start = (*queue);
		while (start->next != NULL) {
			printEventData(start);
			start = start->next;
		}
	}
}

// Pushes a new event onto the queue, if the head == NULL, it means the queue is empty, else traverse the linked list
// queue until the priority is correct, then insert
void push(Event **head, int id, int priority, int time, int type) {
	if ((*head) == NULL) {
		(*head) = addNewEvent(id, priority, time, type);
		(*head)->next = NULL;
	} else {
		Event *start = (*head);
		Event *temp = addNewEvent(id, priority, time, type);
		if ((*head)->priority > priority) {
			temp->next = *head;
			(*head) = temp;
		} else {
			while (start->next != NULL && start->next->priority < priority)
				start = start->next;
			temp->next = start->next;
			start->next = temp;
		}
	}
}

// Removes an event from the queue, and returns that event, used when the event pops from the queue
// and is evaluated as to what device the event will go to next
Event *pop(Event **queue) {
	Event *temp = *queue;
	(*queue) = (*queue)->next;
	temp->next = NULL;
	return temp;
}
