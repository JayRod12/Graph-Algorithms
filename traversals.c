#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"
#include "graph_structs.h"

bool discovered[MAXV + 1];
bool processed[MAXV + 1];
int parent[MAXV + 1];
int nedges; // OPt
int ttime;						// Exclusive for depth first search
int entry_time[MAXV + 1];		// Exclusive for depth first search
int exit_time[MAXV + 1];		// Exclusive for depth first search
bool finished;					// Exclusive for depth first search

void breadth_first_search(graph *g, int start);
void depth_first_search(graph *g, int start);
void initialize_search();
void process_vertex_late(int v);
void process_vertex_early(int v);
void process_edge(int x, int y);
void process_edge_for_finding_cycles(int x, int y);		// Exclusive for depth first search
void find_path(int start, int end);
void print_properties(graph *g);

int main(void) {
	graph *g = malloc(sizeof(graph));	
	read_graph(g);				// Undirected graph
	print_graph(g);	
	printf("Start vertex? ... ");
	int start;
	scanf("%d",&start);

	initialize_search(g);
	// breadth_first_search(g,start);
	//depth_first_search(g,start);


	printf("Depth or breadth first search? ['depth'/'breadth'] ... ");
	char search_type[10];
	scanf("%s", search_type);

	if (!strcmp(search_type, "depth")) {
		printf("Depth first search! \n");
		depth_first_search(g,start);
	} else if (!strcmp(search_type, "breadth")) {
		printf("Breadth first search! \n");
		breadth_first_search(g,start);
	} else {
		return -1;
	}

	print_properties(g);

	free(g);

	printf("Number of edges: %d\n", nedges);

	while (true) {
		printf("\nFind a path from: [x] to [y] ... ");
		printf("\nNote: shortest path only works if [x] is the same vertex as the starting vertex in the bfs\n");
		int x, y;
		scanf("%d %d",&x,&y);
		find_path(x,y);
	}
}

void initialize_search(graph *g) {
	for (int i = 1; i <= g->nvertices; i++) {
		discovered[i] = processed[i] = false;
		parent[i] = entry_time[i] = exit_time[i] = -1;
		ttime = 0;
	}
	finished = false;
}


/*********************************************************************
		BREADTH FIRST SEARCH - RELATED ALGORITHMS

		USE:
			- SHORTEST PATH ALGORITHMS (GUARANTEED BY DOING A BFS AND THEN FINDING PATH, NOT FOR WEIGHTED GRAPHS)
			- FINDING CONNECTED COMPONENTS IN A GRAPH (UNIMPLEMENTED HERE)
			- TWO COLOURING GRAPHS (UNIMPLEMENTED HERE)
*/

void breadth_first_search(graph *g, int start) {
	queue q;		// Discovered vertices yet to be processed
	edgenode *p;	// Temporary edgenode
	int v;			// Current Vertex
	int y; 			// Successor Vertex


	init_queue(&q);
	enqueue(&q, start);
	discovered[start] = true;


	while (!empty_queue(&q)) {
		v = dequeue(&q);
		process_vertex_early(v);
		processed[v] = true;
		p = g->edges[v];
		while (p != NULL) {
				y = p->y;
				if (!processed[y] || g->directed) {
					// If there is an edge (v -> y) in the graph where y has visited 
					// all its outgoing edges but the graph is directed then we must process that edge
					// although we dont process the y vertex.
					process_edge(v,y);
				}
				if (!discovered[y]) {
					discovered[y] = true;
					parent[y] = v;
					enqueue(&q,y);
				}

				p = (edgenode *) p->next;
		}
		process_vertex_late(v);
	}

	free_queue(&q);
}




/*
		END OF BFS
***************************************************************/



/****************************************************************
		VERTEX AND EDGE PROCESSING FUNCTIONS
*/
void process_vertex_late(int v) {

}

void process_vertex_early(int v) {
	printf("processed vertex %d\n", v);
}	

void process_edge(int x, int y) {
	/* Normal bfs or dfs */
	printf("processed edge (%d,%d)\n", x, y);
	nedges++;
	/*********************/

	/* Cycle detection in dfs*

	if (discovered[y] && (parent[x] !=  y)) {
		printf("Cycle from %d to %d:",y,x);
		find_path(y,x);
		printf("\n\n");
		finished = true;
	}

	/*********************/
}

void process_edge_for_finding_cycles(int x, int y) {
	if (discovered[y] && (parent[x] !=  y)) {
		printf("Cycle from %d to %d:",y,x);
		find_path(y,x);
		printf("\n\n");
		finished = true;
	}
}



/*
		END OF VERTEX AND EDGE PROCESSING FUNCTIONS
*****************************************************************/




void print_properties(graph *g) {

	printf("\nParent:\t");
	for (int i = 1; i <= g->nvertices; i++)
		printf("%d\t", parent[i]);
	printf("\n");

	printf("\nVertex:\t");
	for (int i = 1; i <= g->nvertices; i++)
		printf("%d\t", i);
	printf("\n");


	printf("\nEntry:\t");
	for (int i = 1; i <= g->nvertices; i++)
		printf("%d\t", entry_time[i]);
	printf("\n");

	printf("\nExit:\t");
	for (int i = 1; i <= g->nvertices; i++)
		printf("%d\t", exit_time[i]);
	printf("\n");


}

/*
		FINDING PATHS (GENERAL GRAPHS)

		REQUIRES THE PARENT ARRAY TO BE FILLED (BY DOING A DFS OR BFS)
*/

void find_path(int start, int end) {
	if ((start == end) || (end == -1))
		printf("Path: %d", start);
	else {
		find_path(start, parent[end]);
		printf(" %d",end);
	}
}

/*****************************************************************
			DEPTH FIRST SEARCH - RELATED ALGORITHMS
*/

void depth_first_search(graph *g, int v) {
	edgenode *p;	// Temporary edgenode
	int y; 			// Successor Vertex

	if (finished) return; 	// Allow for early termination

	discovered[v] = true;
	ttime ++;
	entry_time[v] = ttime;

	process_vertex_early(v);


	p = g->edges[v];
	while (p != NULL) {
		y = p->y;
		
		if (!discovered[y]) {
			parent[y] = v;
			process_edge(v,y);			
			depth_first_search(g,y);
		} else if ((!processed[y] && (parent[v] != y)) || g->directed) {
			process_edge(v,y);			
		}
		if (finished) return;
		p = (edgenode *) p->next;
	}

	process_vertex_late(v);
	
	ttime ++;
	exit_time[v] = ttime;
	
	processed[v] = true;
}







/*
		END OF DFS
***************************************************************/
