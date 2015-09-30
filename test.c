#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(void) {
	queue q;		// Discovered vertices yet to be processed
	int v;			// Current Vertex
	int x[] = {1,2,3,4,5,6,7,8};

	init_queue(&q);
	for (int i = 0; i < 8; i++) {
		enqueue(&q, x[i]);
	}

	while (!empty_queue(&q)) {
		v = dequeue(&q);
		printf("vertex.. %d\n", v);
	}

	free_queue(&q);
}