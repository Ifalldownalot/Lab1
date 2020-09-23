Programmer		Zachary William Preston
Date:			2020 September 22
Course:			Intro to Operating Systems
Description:		A discrete event simulator that will simulate the journey an even
			in an operating system takes as it moves thorugh the priority queue
			to the CPU and then to an I/O device, or uses the CPU

For this project, I had to recreate it several times over the weeks, as I was having many problems with segmentation fault errors
so there are several iterations of this lab that I created that I will also include to see where the thing started from

Firstly, I created a structure that implements several parts of the improvised "event".
	int id;          There is a coutner in the main function that is used to assign an ID to each event to keep track
	int priority;    Each event is randomly assigned a number that acts as it's priority, priority 1 is most important
	int time;        Each event is randomly assigned a time, that is used as a timer for how long it needs to run before it finishes executing
	int type;	 The type is also randomly assigned, is meant to represent what the event will do once the CPU gets it
			 1 -> it will stay in the CPU and it's timer will decrement until 0 and it will terminate
			 2 -> it will go to I/O queue where the same thing will happen in a different queue
			 3 -> it will go to the network queue where the same thing will happen in a different queue
	Event *next;	 used for the implementation of a linked list for the queue, this points to the next event
			 in the queue

	
Main Function:
	In the main function, the queues are precreated and set to NULL as there are no events created yet
	For the sake of the simulation, I populated the priority queue with a few events prior to the start because I was experiencing a segmentation fault error
	A file is also opened, named STAT_FILE that is used to log each time an event timer runs out
		The event timer running out shows that it has "finished" and can terminate
	When the for loop begins, this is where the simulation starts, with a variable called time taht is used as the units of time
	during the simulation. At the start of each iteration of the for loop, is the beginning of a new "unit of time" at which several things can happen
		A new event is created, and pushed on the priority Queue
			Its data is for the most part randomly generated, the time, the type and the priority, and it is given an ID number from the counter variable
		The event at the beginning of the priority Queue is popped form the front and its type is analyzed
			If the type is 1, then the event is placed into the CPU queue
			If the type is 2, then the event is placed into the I/O queue
			If the type is 3, then the event is placed into the network queue
		The first event in each queue will have its time decremented by one for each iteration of time
			If the time for the event reaches zero, then the event has finished running
			it is popped from the queue, and then the time and the event information is logged in the open STAT_FILE, then the event terminates
			This is also printed to screen for the sake of troubleshooting and debugging
		This is done for the first event of each queue, and done over and over again until the simulation ends at TIME_END
	When simulation is finished, it is written to the file as well

Several function were written for utilites
	push -  used for pushing a new event onto a queue, used for all of the queues not just for the priority queue
		does not return any values, but creates a new event for the queue that is being pushed
	pop -   used to get the first event off the front of the queue, this is used for priority queue to analyze and decide
		what device the event will go to next, or when the timer hits 0, and the event terminates
	printEventData - used to print the data of a particular event, this is used mainly to debug, to make sure
		that the event was properly storing the values randomly generated when the event was created
	printEntireQueue - used to traverse the entire queue, and print the data for each event until the end of the queue
		is reached, used for debugging as well to make sure queue is not empty, or pointing towards NULL
	getRandomData - randomly generated integers used for assignign to new events created
