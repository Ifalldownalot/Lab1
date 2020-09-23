// Programmer: 			Zachary William Preston
// Date:			2020 September 15
// Course:			Intro to Operating Systems
// Description:			This is a discrete event simulator that is meant
//				to simulate the interaction between events on an OS
//				and a CPU and the transition from CPU usage to various
//				I/O devices over a period of time

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define START_TIME 0
#define END_TIME 100
#define STR_SIZE 6
#define STAT_FILE "stats.txt"
#define FILE_ERROR "--> ERROR: File couldn't be opened\n"
#define START_MESSAGE "Simulation Started...\n"
#define END_MESSAGE "Simulation Ended...\n"

typedef struct Event {
	int time;
	int priority;
	int id;
} Event;

void recordCurrentTime(FILE *, char *, int);
void recordNewEvent(FILE *, Event, char *);
Event createNewEvent(int);

int main(int argc, char *argv[]) {
	Event test = createNewEvent(1);
	while (test.time >= 0) {
		printf( "Time remaining = %d\n", test.time );
		test.time--;
	}
	/*
	FILE *file = fopen(STAT_FILE, "w" );
	if (file == NULL) {
		printf( "%s", FILE_ERROR);
		exit(1);
	} else {
		int globalTime = START_TIME;
		char num[STR_SIZE];
		fputs(START_MESSAGE, file);
		Event testEvent;
		testEvent.time = 10;
		testEvent.priority = 5;
		testEvent.id = 1;


		while (globalTime <= END_TIME) { // <--- Simulation begins here
			recordCurrentTime(file, num, globalTime);
			recordNewEvent(file, testEvent, num);
			globalTime++;
		} fputs(END_MESSAGE, file); // <--- Simulation ends here
		fclose(file);
	}*/
	return EXIT_SUCCESS;
}

void recordCurrentTime(FILE *file, char *num, int time) {
	sprintf(num, "%d", time);
	fputs("Current Time: ", file);
	fputs(num, file);
	fputs("\n", file);
}

void recordNewEvent(FILE *file, Event event, char *num) {
	fputs("\tNew Event Created: PID Number ", file);
	sprintf(num, "%d", event.id);
	fputs(num, file);
	fputs("\n", file);
	fputs("\t\tTime to termination: ", file);
	sprintf(num, "%d", event.time);
	fputs(num, file);
	fputs("\n", file);
	fputs("\t\tEvent Priority: ", file);
	sprintf(num, "%d", event.priority);
	fputs(num, file);
	fputs("\n", file);
}

Event createNewEvent(int count) {
	Event newEvent;
	newEvent.time = 10;
	newEvent.priority = 5;
	newEvent.id = count;
	return newEvent;
}
