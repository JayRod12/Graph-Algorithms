#ifndef QUEUE_H
#define QUEUE_H


// Queue of vertices, i.e. integers
typedef struct {
	int v; 				// Vertex number
	struct box *next;
} box;

typedef struct {
	box *first;
	box *last;
} queue;

void init_queue(queue *q);
int empty_queue(queue *q);
int dequeue(queue *q);
void enqueue(queue *q, int v);
void free_queue(queue *q);
void print_queue(queue *q);

#endif
