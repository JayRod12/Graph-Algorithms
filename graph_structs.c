#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph_structs.h"



// int main(void) {
// 	graph *g = malloc(sizeof(graph));	
// 	read_graph(g, false);				// Undirected graph
// 	print_graph(g);						// Print the graph
// }

void initialize_graph(graph *g, bool directed) {

	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;

	for (int i = 1; i <= MAXV; i++) {
		g->degree[i] = 0;
		g->edges[i] = NULL;
	}
}

void read_graph(graph *g) {
	int m,				// number of edges
		x, y;			// vertices in edges (x, y)
	bool directed;		// Directed or undirected graph

	// FILE *f = fopen("example_graphs_labyrinth.txt","r");
	FILE *f = fopen("example_graphs_labyrinth.txt","r");
	char dir;
	printf("Directed? [y/n] ... ");
	scanf("%c",&dir);

	if (dir == 'y') {
		directed = true;
	} else {
		directed = false;
	}



	initialize_graph(g,directed);
	//printf("Input: [vertices] [edges] ... ");
	fscanf(f,"%d %d", &(g->nvertices), &m);
	
	//printf("Input all edges now as: [x] [y]\n");
	for (int i = 1; i <= m; i++) {
		fscanf(f,"%d %d", &x, &y);
		insert_edge(g,x,y,directed);
	}
}

void insert_edge(graph *g, int x, int y, bool directed) {

	edgenode *p;
	p = malloc(sizeof(edgenode));


	p->weight = 0;
	p->y = y;
	p->next = (struct edgenode *) g->edges[x];
	
	g->edges[x] = p;
	g->degree[x] ++;

	if (directed == false) {
		insert_edge(g, y, x, true);
	} else {
		g->nedges ++;
	}
}

void print_graph(graph *g) {
	edgenode *p;

	for (int i = 1; i <= g->nvertices; i++) {
		printf("%d: ", i);
		p = g->edges[i];
		while (p != NULL) {
			printf(" %d", p->y);
			p = (edgenode *) p->next;
		}
		printf("\n");
	}
}













