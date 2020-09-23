#include <stdio.h>
#include <stdlib.h>
#define PQ_MAX 30
#define STAT_FILE "stats.txt"
#define TIME_START 0
#define TIME_FIN 100

// int priority = rand() % 3 + 1;
// int time = rand() % 20 + 10;

typedef struct Event {
	int id;
	int time;
	int priority;
	int type;
	struct Event *next;
} Event;

int getRandomTime();
int getRandomPriority();
int getRandomType();
void printEventData(Event *);
Event *addNewEvent(int, int, int, int);
void push(Event **, int, int, int, int);
Event *pop(Event **);
void printEntireQueue(Event **);

int main(int argc, char *argv[]) {
	int id = 1;
	Event *pQueue = addNewEvent(id, getRandomTime(), getRandomPriority(), getRandomType());
	printf( "Simulation Start...\n" );
	for (int time = TIME_START; time < TIME_FIN; time++, ++id) {
		if (queueSize <= PQ_MAX) {
			push(&pQueue, id, getRandomTime(), getRandomPriority(), getRandomType());
			queueSize++;
		}
	} printf( "Size of Queue = %d\n", queueSize );
	printEntireQueue(&pQueue);
	Event *test = pop(&pQueue);
	queueSize--;
	printf( "ENTERING CPU QUEUE --> " );
	printEventData(test);
	printf( "Size of Queue = %d\n", queueSize );
	printf( "Simulation Finish...\n" );
	return EXIT_SUCCESS;
}

int getRandomTime() {
	return rand() % 20 + 10;
}

int getRandomPriority() {
	return rand() % 3 + 1;
}

int getRandomType() {
	return rand() % 3 + 1;
}

void printEventData(Event *event) {
	printf( "ID = %3d\tPriority = %d\tTime = %2d\tType = %d\n", event->id, event->priority, event->time, event->type );
}

Event *addNewEvent(int id, int time, int priority, int type) {
	Event *event = (Event *) malloc (sizeof(Event));
	event->id = id;
	event->time = time;
	event->priority = priority;
	event->type = type;
	event->next = NULL;
	return event;
}

void push(Event **head, int id, int time, int priority, int type) {
	Event *start = (*head);
	Event *temp = addNewEvent(id, time, priority, type);
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

Event *pop(Event **start) {
	Event *temp = *start;
	(*start) = (*start)->next;
	temp->next = NULL;
	return temp;
}

void printEntireQueue(Event **queue) {
	Event *start = (*queue);
	while (start->next != NULL) {
		printEventData(start);
		start = start->next;
	}
}
