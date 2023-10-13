#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "t1.h"

#define SIZE 15

typedef struct node{
    int vertex;
    struct node* next;
} node;

node* create_node(char vertex){
    node* newNode = malloc(sizeof(node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

Graph* create_graph(int num_nodes){
    Graph* newGraph = malloc(sizeof(Graph));
    newGraph->numVertices = num_nodes;

    newGraph->adjlist = malloc(num_nodes * sizeof(node*));
    newGraph->visited = malloc(num_nodes * sizeof(int));

    for(int i = 0; i < num_nodes; i++){
        newGraph->adjlist[i] = NULL;
        newGraph->visited[i] = 0;
    }
    return newGraph;
}

void add_edge(Graph *g, int from, int to){
    struct node* newNode = create_node(to);
    newNode->next = g->adjlist[from];
    g->adjlist[from] = newNode;
}

////////////////////////////////////////////QUEUE

typedef struct queue{
    int vertex[15];
    int head;
    int tail;
}queue;

queue* create_queue(){
    queue* q = malloc(sizeof(queue));
    q->head = -1;
    q->tail = -1;
    return q;
}

void enqueue(queue* q, int val){
    if(q->tail == 14){ //Q_SIZE - 1, aka queue full
        //printf("Error, trying to enqueue when the queue full\n");
    }else{
        if(q->head == -1){
            q->head++;
        }
        q->tail++;
        q->vertex[q->tail] = val;
    }
}

bool is_empty(queue* q){
    if (q->tail == -1)
        return 1;
    else
        return 0;
}

int dequeue(queue* q){
    int val;
    if(is_empty(q)){
        //printf("Error, trying to dequeue when the queue is empty\n");
        val = -1;
    }else{
        val = q->vertex[q->head];
        q->head++;
        if (q->head > q->tail) {
            //printf("Resetting queue ");
            q->head = q->tail = -1;
        }
    }
    return val;
}

////////////////////////////////////////////GRAPH TRAVERSAL

void bfs(Graph* g, int origin){
    struct queue* q = create_queue();

    g->visited[origin] = 0;
    enqueue(q, origin);
    
    printf("\nBFS ");
    while (!is_empty(q)) {
        int currentVertex = dequeue(q);
        printf(" %c ", currentVertex + 'A');

        struct node* temp = g->adjlist[currentVertex];

        while (temp) {
        int adjVertex = temp->vertex;

        if (g->visited[adjVertex] == 1) {
            g->visited[adjVertex] = 0;
            enqueue(q, adjVertex);
        }
        temp = temp->next;
        }
    }
    free(q);
}

bool first_time = 1;

void dfs(Graph* g, int origin){
    struct node* adjList = g->adjlist[origin];
    struct node* temp = adjList;

    if(first_time){
        printf("DFS:");
        first_time = 0;
    }

    g->visited[origin] = 1;
    printf(" %c ", origin + 'A');

    while (temp != NULL) {
        int connectedVertex = temp->vertex;

        if (g->visited[connectedVertex] == 0) {
            dfs(g, connectedVertex);
        }
        temp = temp->next;
    }
}

void delete_node(node* n){
    if(n == NULL){ return; }
    delete_node(n->next);
    free(n);
}

void delete_graph(Graph* g){
    for(int i = 0; i < g->numVertices; i++){
        delete_node(g->adjlist[i]);
    }
    free(g->adjlist);
    free(g->visited);
    free(g);
}
