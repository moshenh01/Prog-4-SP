#ifndef GRAPH_
#define GRAPH_
#include <stdio.h>
#include <stdlib.h>

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int edge_node_num;//node number of the edge
    int weight;
    pnode startpoint;
    pnode endpoint;//pointer to the node at the other end of the edge
    struct edge_ *next;//linked list of edges for a node  (adjacency list) 
} edge, *pedge;//edge is the data type, pedge is the pointer to the data type 


typedef struct GRAPH_NODE_ {
    int dis;
    int vis;
    int node_num;//node number 
    pedge edges;//linked list of edges
    struct GRAPH_NODE_ *next;//linked list of nodes (adjacency list) 
} node, *pnode;//node is the data type, pnode is the pointer to the data type

//----------------------PQ-----
typedef struct node_pq {
    int data;
    int priority;
 
    struct node_pq* next;
 
} Node;
//-------------------------------


extern struct GRAPH_NODE_ *head;

//head of the linked list of nodes


void print_lowest_route();
void delete_node(int node_num);
void insert_node();
void build_node_edges();
void build_node_edgesforB(int node_num);
void build_graph(int node_amount);// build the graph from the input file
void TSP();
void rm_graph(pnode head);


#endif
