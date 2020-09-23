#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	int priority;
	struct Node *next;
} Node;

Node *newNode(int, int);
int peek(Node **);
void pop(Node **);
void push(Node **, int, int);

int main(int argc, char *argv[]) {
	Node *pq;
	printf( "Head = %d\n", peek(&pq));
}

Node *newNode(int d, int p) {
	Node *temp = (Node*) malloc (sizeof(Node));
	temp->data = d;
	temp->priority = p;
	temp->next = NULL;
	return temp;
}

int peek(Node **head) {
	if ((*head) == NULL)
		return -10;
	else
		return (*head)->data;
}

void pop(Node **head) {
	Node *temp = *head;
	(*head) = (*head)->next;
	free(temp);
}

void push(Node **head, int d, int p) {
	if ((*head) == NULL) {
		
	}
	Node *start = (*head);
	Node *temp = newNode(d, p);
	if ((*head)->priority > p) {
		temp->next = *head;
		(*head) = temp;
	} else {
		while (start->next != NULL && start->next->priority < p) {
			start = start->next;
		} temp->next = start->next;
		start->next = temp;
	}
}
