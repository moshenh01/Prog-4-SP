#include <stdio.h>
#include <stdlib.h>
#include "graph.h"


struct GRAPH_NODE_ *head = NULL;
// head of the list of nodes in the graph.
void build_empty_node(int node_num);
void insert_node();
void rm_graph(pnode head);
void delete_edges(pedge first_edge);
void delete_node(int node_num);
void delete_edge_endpoint(pnode head, int node_num);

void build_graph(int node_amount){
  if (head != NULL)//
  {
    rm_graph(head);
    head = NULL;
  }
 
  for (int i = 0; i < node_amount; i++)
  {
    build_empty_node(i);
   // printf("node %d is created\n",i);
  }
  
  
}

void build_empty_node(int node_num){
    pnode new_node = (struct GRAPH_NODE_*)
    malloc(sizeof(struct GRAPH_NODE_));
    new_node->next = NULL;
    new_node->node_num = node_num;
    new_node->edges = NULL;
    if(head == NULL){
        head = new_node;
    }
    else{
        pnode temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

void insert_node(){
    int node_num;
    scanf("%d", &node_num);
    if (head == NULL)
    {
       // printf("graph is empty\n");
        build_empty_node(node_num);
        build_node_edgesforB(node_num);
        return;
    }
    pnode temp = head;
    while(temp->next != NULL && temp->node_num != node_num){
        temp = temp->next;
    }
    if (temp->node_num == node_num)
    {
        //printf("node %d already exists\n",node_num);
        //delete_node(node_num);
        //build_empty_node(node_num);
        delete_edges(temp->edges);
        temp->edges = NULL; 
        build_node_edgesforB(node_num);
        return;
    }
    if (temp->next == NULL)
    {
        //printf("node %d not exists\n",node_num);
        build_empty_node(node_num);
        build_node_edgesforB(node_num);
        return;
    }
    
    
    build_empty_node(node_num);
}

void rm_graph(pnode head){
    pnode temp = head;
    while(temp != NULL){
        pnode temp2 = temp->next;
        delete_edges(temp->edges);
        free(temp);
        temp = temp2;
    }
    head = NULL;
}
void delete_node(int node_num){
    pnode temp = head;
    pnode temp2 = head;
    if (temp->node_num == node_num)
    {
        head = temp->next;
        delete_edge_endpoint(head, node_num);
        delete_edges(temp->edges);
        free(temp);
       // printf("1node %d was deleted\n",node_num);
        return;
    }
    while(temp->next != NULL && temp->node_num != node_num){
        temp2 = temp;
        temp = temp->next;
    }
    if (temp->node_num == node_num)
    {
        temp2->next = temp->next;
        delete_edge_endpoint(head, node_num);
        delete_edges(temp->edges);
        free(temp);
        //printf("2node %d was deleted\n",node_num);
        return;
    }
   
}
void delete_edges(pedge first_edge){
    pedge temp = first_edge;
    while(temp != NULL){
        pedge temp2 = temp->next;
       // printf("edge %d was deleted\n",temp->weight);
        free(temp);
        temp = temp2;
    }
    first_edge = NULL;
}
void delete_edge_endpoint(pnode head, int node_num){//delete the edges that have the node_num as endpoint
    pnode temp = head;
    while(temp != NULL){
        pedge temp2 = temp->edges;
        pedge f_edge = temp->edges;
        while (temp2 != NULL)
        {   
            
            pedge temp3 = temp2->next;
            //if the edge is the first edge of the node
            if (temp2->endpoint->node_num == node_num && f_edge == temp2)
            {
                temp->edges = temp2->next;
                free(temp2);
            }
            //if the edge is not the first edge of the node
            else if (temp2->endpoint->node_num == node_num)
            {   
                f_edge->next = NULL;
                free(temp2);

            }
            temp2 = temp3;
            
        }
        temp = temp->next;
    }
        
}