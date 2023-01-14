#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


/*
create the eades for the node that we are scanning.
*/
void addedge(pnode ourNode, int Vertex, int edgeToVertex);
void build_node_edgesforB(int node_num);
void build_node_edges(){
    int node_num;
    scanf("%d", &node_num);
    pnode temp = head;
    while(temp->node_num != node_num){
        temp = temp->next;
    }
    int x1,y1;
    if(scanf("%d %d", &x1, &y1) != 2){
        return;
    }
    addedge(temp,x1,y1);
    printf("edge %d %d is created\n",x1,y1);
    int x2,y2;
    if(scanf("%d %d", &x2, &y2) != 2){
        return;
    }
    addedge(temp,x2,y2);
    //printf("edge %d %d is created\n",x2,y2);

}
void build_node_edgesforB(int node_num){
    pnode temp = head;
    while(temp->node_num != node_num){
        temp = temp->next;
    }
    int x1,y1;
    if(scanf("%d %d", &x1, &y1) != 2){
        return;
    }
    addedge(temp,x1,y1);
    //printf("edge %d %d is created\n",x1,y1);
    int x2,y2;
    if(scanf("%d %d", &x2, &y2) != 2){
        return;
    }
    addedge(temp,x2,y2);
    //printf("edge %d %d is created\n",x2,y2);


}
void addedge(pnode ourNode, int edgeToVertex, int weight){
     pnode temp = head;
    while(temp->node_num != edgeToVertex){
        temp = temp->next;
    }
    pedge new_edge = (struct edge_*)
    malloc(sizeof( struct edge_));
    new_edge->next = NULL;
    new_edge->startpoint= ourNode;
    new_edge->endpoint= temp;
    new_edge->weight = weight;
    new_edge->edge_node_num = ourNode->node_num;

   // printf("ourNode->node_num = %d\n",ourNode->node_num);
    if(ourNode->edges == NULL){
        ourNode->edges = new_edge;
    //printf("1**");
    }
    else{
        pedge temp2 = ourNode->edges;
        while(temp2->next != NULL){
            temp2 = temp2->next;
        }
        temp2->next = new_edge;
        //printf("2**");
    }
}