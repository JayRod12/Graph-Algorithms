#ifndef GRAPH_H
#define GRAPH_H

#define MAXV 100

typedef struct {
	int y; 
	int weight;
	struct edgenode *next;
} edgenode;

typedef struct {
	edgenode *edges[MAXV + 1];
	int degree[MAXV + 1];
	int nvertices;
	int nedges;
	bool directed;
} graph;

void initialize_graph(graph *g, bool directed);
void read_graph(graph *g);
void insert_edge(graph *g, int x, int y, bool directed);
void print_graph(graph *g);

#endif