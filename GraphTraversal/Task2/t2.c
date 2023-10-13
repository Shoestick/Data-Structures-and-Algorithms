#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "t2.h"

Graph* create_graph(int num_nodes){ // creates a graph with num_nodes nodes, assuming nodes are stored in alphabetical order (A, B, C..)
    struct Graph* g = malloc(sizeof(Graph));
    g->num_nodes = num_nodes;

    //g->matrix = malloc(num_nodes * sizeof(int));
    g->visited = malloc(num_nodes * sizeof(int));

    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){
            g->matrix[i][j] = 0;
        }
        g->visited = 0;
    }
    return g;
}

void add_edge(Graph *g, int from, int to, int weight){ // adds an undirected weighted edge between from and to
    g->matrix[from][to] = weight;
    g->matrix[to][from] = weight;
}

bool all_vertices_visited(Graph *g){
    for(int i = 0; i < g->num_nodes; i++){
        if(g->visited[i] = 0){
            return false;
        }
    }
    return true;
}

void dijkstra(Graph* g, int origin){ // implements the dijkstra algorithm and prints the order in which the nodes are made permament, and the length of the shortest path between the origin node and all the other nodes
    /*int distance[g->num_nodes], prev[g->num_nodes];
    int next_node;
    for(int i = 0; i < g->num_nodes; i++){
        distance[i] = INFINITY;
        prev[i] = 0;
    }
    distance[origin] = 0;
    g->visited[origin] = 1;

    printf("%c ", origin + 'A');

    int current_vertex = INFINITY;
    while(!all_vertices_visited(g)){
        for(int i = 0; i < g->num_nodes; i++){
            if(g->visited[i] = 0 && distance[i] < current_vertex){
                current_vertex = distance[i];
                next_node = i;
            }
        }

        printf("%c ", next_node + 'A');
        g->visited[next_node] = 1;
        for(int i = 0; i < g->num_nodes; i++){
            if(g->visited[i] = 0){
                if(current_vertex + g->matrix[next_node][i] < distance[i]){
                    distance[i] = current_vertex + g->matrix[next_node][i];
                    prev[i] = next_node;
                }
            }
        }
        
        
        //The length of the shortest path between A and A is 0
    }
    for(int i = 0; i < g->num_nodes; i++){
        printf("The length of the shortest path between %c and %c is %i", origin + 'A', i + 'A', distance[i]);
    }*/
}

void delete_graph(Graph* g){
    free(g->visited);
    free(g);
}
