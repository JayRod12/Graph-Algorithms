#include <stdlib.h>
#include <stdio.h>
#include "queue.h"




void init_queue(queue *q) {
	q->first = q->last = NULL;
}

int empty_queue(queue *q) {
	return q->first == NULL;
}


int dequeue(queue *q) {
	if (empty_queue(q)) {
		return -1;
	}
	box *tmp = q->first;				// Temp box pointer
	int v = tmp->v;						// Store vertex

	if (q->first != q->last) { 		
		// There is >= 2 elements
		q->first = (box *) tmp->next;	// Update first box to new head of queue
		free(tmp);						// Free the old box
	} else {
		// There is 1 element only
		q->first = q->last = NULL;
		free(tmp);
	}
	return v;
}

void enqueue(queue *q, int v) {
	box *b = malloc(sizeof(box));
	b->v = v;
	b->next = NULL;

	if (empty_queue(q)) {
		q->first = b;
		q->last = b;
	} else {
		q->last->next = (struct box *) b;
		q->last = b;	
	}
}

void print_queue(queue *q) {
	printf("Queue: ");
	box *b = q->first;

	while (b != NULL) {
		printf("%d ",b->v);
		b = b->next;
	}
	printf("\n");
}

void free_queue(queue *q) {
	while (!empty_queue(q)) {
		dequeue(q);
	}
}
