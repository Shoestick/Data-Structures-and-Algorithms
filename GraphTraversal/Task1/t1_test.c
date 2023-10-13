#include "t1.h"
#include <stdio.h>
#include <stdlib.h>

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

char int2char(int k){
    return k + 'A';
}

/*void printGraph(struct Graph* graph) {
  for (int v = 0; v < graph->numVertices; v++) {
    struct node* temp = graph->adjlist[v];
    printf("\n Adjacency list of vertex %c\n ", v + 'A');

    printf("%c", int2char(temp->vertex));
    temp = temp->next;

    while (temp) {
      printf(" -> %c", int2char(temp->vertex));
      temp = temp->next;
    }
    printf("\n");
  }
}*/

int main(){
    int num_nodes = 6;
    Graph *graph = create_graph(num_nodes);
   
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));

    dfs(graph, char2val('A'));
    bfs(graph, char2val('A'));

    //printf("%i", char2val('F'));
    delete_graph(graph);
    //printGraph(graph);
}