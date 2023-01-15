#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#define MIN(a,b) a<b?a:b

int print_lowest_routee(struct GRAPH_NODE_ *head, int x, int y);
void print_lowest_route();
void dijkstra(struct GRAPH_NODE_ *head, int source);
void relax(struct edge_ *p_edge, Node **pq);
int node_exists(int node_num);
void tsp2(struct GRAPH_NODE_ *head, int numberOfNodes);
void TSP();
int highest_node_num();
void print_matrix(int matrix[][highest_node_num()], int numberOfNodes, int hnn);
void clear_distance(struct GRAPH_NODE_ *head);
int index_of(int arr[], int size, int num);
void shift_elements(int arr[], int size);
void copy_array(int arr[], int cpyarr[], int size);
int arr_has_left(int arr[], int size);
void arr_delete(int arr[], int size, int num);
int sun_of_nodes(struct GRAPH_NODE_ *head);
void TSP_helper_cmd(pnode head, int *arr,int num, int curr,int *pmin);



// struct n_node* n_head = NULL; // head of the list of nodes in the graph after dij.

//-------------------- min priority queue--------------------

Node *newNode(int d, int p)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}
int peek(Node **head) { return (*head)->data; }
// Removes the element with the
// highest priority form the list
void dequeue(Node **head)
{
    Node *temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
void enqueue(Node **head, int d, int p)
{
    Node *start = (*head);

    // Create new Node
    Node *temp = newNode(d, p);

    // Special Case: The head of list has
    // bigger priority than new node
    if ((*head)->priority > p)
    {

        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else
    {

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL && start->next->priority < p)
        {
            start = start->next;
        }

        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
void order(Node **pq)
{
    Node *temp = *pq;
    Node *temp2 = *pq;
    while (temp != NULL)
    {
        temp2 = temp->next;
        while (temp2 != NULL)
        {
            if (temp->priority > temp2->priority)
            {
                int temp_data = temp->data;
                int temp_priority = temp->priority;
                temp->data = temp2->data;
                temp->priority = temp2->priority;
                temp2->data = temp_data;
                temp2->priority = temp_priority;
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
}
int isEmpty(Node **head) { return (*head) == NULL; }

//--------------------priority queue--------------------

void print_lowest_route()
{
    int x, y;
    if(scanf("%d %d", &x, &y) == EOF)
    {
        printf("-1");
        return;
    }
    if (node_exists(x) == 0 || node_exists(y) == 0)
    {
        printf("-1");
        return;
    }
    else
    {
       int print = print_lowest_routee(head, x, y);
       if (print == SHRT_MAX)
       {
           printf("-1");
           return;
       }
       printf("Dijsktra shortest path: %d \n", print);

    }
}
int print_lowest_routee(pnode chead, int x, int y)
{
    dijkstra(head, x);
    pnode temp = head;
    while (temp->node_num != y)
    {
        temp = temp->next;
    }
    if (temp->dis == SHRT_MAX)
    {
        return temp->dis;
    }
    
    return temp->dis;
};
void dijkstra(pnode head, int source)
{

    pnode temp = head;
    while (temp != NULL) // initialize all nodes distance to infinity and visited to 0.
    {
        temp->dis = SHRT_MAX;
        temp->vis = 0;
        temp = temp->next;
    }
    temp = head;

    while (temp->node_num != source) // find the source node ,set his distans to 0.
    {
        temp = temp->next;
    }
    temp->dis = 0;
    temp = head->next;
    Node *pq = newNode(head->node_num, head->dis);
    while (temp != NULL) // set all nodes to the queue.
    {
        enqueue(&pq, temp->node_num, temp->dis);
        temp = temp->next;
    }
    while (!isEmpty(&pq))
    {
        int u = peek(&pq);
        // printf("u: %d\n", u);
        pnode temp1 = head;
        // printf("source node: %d\n",pr[u].node_num);
        while (temp1->node_num != u) // find the node with the lowest distance(priority).
        {
            temp1 = temp1->next;
        }
        dequeue(&pq);
        temp1->vis = 1; // set the node to visited to 1 its mean that we already visit
        // printf("node: %d, dis: %d\n", temp1->node_num, temp1->dis);
        pedge p_edge = temp1->edges;
        if (p_edge == NULL)
        {
            // printf("no edges\n");
            // exit(0);
        }

        // printf("egde status: %d\n", p_edge->weight);

        //-----------------------------------------------------------

        while (p_edge != NULL) // check all the edges of the node.
        {
            // relax
            relax(p_edge, &pq);
            p_edge = p_edge->next;
            //printf(" gg\n");
        }
        
        
    }
    // temp = head;
    // while (temp != NULL)
    // {
    //     //printf("%d ", temp->dis);
    //     temp = temp->next;
    // }
    // printf("\n");
}
void relax(pedge p_edge, Node **pq)

{

    // printf("startpoint: %d, endpoint: %d, weight: %d\n", p_edge->startpoint->node_num, p_edge->endpoint->node_num, p_edge->weight);
    if (p_edge->endpoint->dis > p_edge->startpoint->dis + p_edge->weight)
    {
        // printf("node- %d to node- %d , original dis: %d, new dis: %d\n",p_edge->startpoint->node_num,p_edge->endpoint->node_num, p_edge->endpoint->dis, p_edge->startpoint->dis + p_edge->weight);
        p_edge->endpoint->dis = p_edge->startpoint->dis + p_edge->weight; // update the distance of the node.

        // chande in the queue
        Node *temp = *pq;
        while (temp != NULL)
        {
            if (temp->data == p_edge->endpoint->node_num)
            {
                //printf("change in the q\n");
                temp->priority = p_edge->endpoint->dis;
                order(pq);
                break;
            }
            temp = temp->next;
        }
        
    }
}

int node_exists(int node_num)
{
    pnode temp = head;
    while (temp != NULL)
    {
        if (temp->node_num == node_num)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void swap_place(int *arr, int num1, int num2)
{
    int temp = arr[num1];
    arr[num1]=arr[num2];
    arr[num2]=temp;
}
void TSP()
{
    int amount_of_nodes;
    scanf("%d", &amount_of_nodes);
    //printf("num: %d\n", num);
    int *arr = (int*)(malloc(sizeof(int)*amount_of_nodes));
    int min = SHRT_MAX;
    int * pshort=&min;
    for(int i =0 ; i<amount_of_nodes; i++)
    {   
        scanf("%d", &arr[i]);//get the nodes into array.
    }
    for(int i=0;i<amount_of_nodes;i++)
    {
        swap_place(arr,0,i);
        TSP_helper_cmd(head,arr,amount_of_nodes,0,pshort);
        swap_place(arr,i,0);
    }
    free(arr);
    if (*pshort == SHRT_MAX)
    {
        printf("TSP shortest path:-1 \n");
        return;
    }
    
    printf("TSP shortest path: %d \n", *pshort);
    
}
void TSP_helper_cmd(pnode head, int *arr,int num, int curr,int *pmin)
{
    if(num==2)
    {
        int finshdist = print_lowest_routee(head,arr[0],arr[1]);
        if(finshdist != SHRT_MAX)
        {
            if((curr + finshdist)<*pmin)
            {
                *pmin = (curr+finshdist);
            }
        }
        return;
    }
    for(int i=1;i<num;i++)
    {
        swap_place(arr,1,i);
        int dist = print_lowest_routee(head,arr[0],arr[1]);
        if(dist== SHRT_MAX)
        {
            return;
        }
        TSP_helper_cmd(head,arr+1,num-1,curr+dist,pmin);
        swap_place(arr,i,1);
    }
}

int highest_node_num()
{
    struct GRAPH_NODE_ *temp = head;
    int max = 0;
    while (temp != NULL)
    {
        if (temp->node_num > max)
        {
            max = temp->node_num;
        }
        temp = temp->next;
    }
    return max+1;
}
void print_matrix(int matrix[][highest_node_num()], int numberOfNodes, int hnn)
{
    
    printf("\n");
    for (int i = 0; i < numberOfNodes; i++)
    {
        for (int  j = 0; j < hnn; j++)
        {
            if(matrix[i][j] == SHRT_MAX)
            {
                printf("%d ", matrix[i][j]);
            }
            else
            printf("%d     ", matrix[i][j]);
        }
        printf("\n\n");
    }
}
void clear_distance(struct GRAPH_NODE_ *head)
{
    struct GRAPH_NODE_ *temp = head;
    while (temp != NULL)
    {
        temp->dis = SHRT_MAX;
        temp = temp->next;
    }
}
int index_of(int arr[], int size, int num)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            return i;
        }
    }
    return -1;
}
void shift_elements(int arr[], int size)
{
    int temp =arr[size -1];
    for(int i = size-1; i>0 ;i--)
    {
        arr[i] = arr[i-1];
    }
    arr[0] = temp;
}
void copy_array(int arr[], int cpyarr[], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        cpyarr[i] = arr[i];
    }
    
}
int arr_has_left(int arr[], int size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] != SHRT_MAX)
        {
            return arr[i];
        }
    }
    return SHRT_MAX;
}
void arr_delete(int arr[], int size, int num)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            arr[i] = SHRT_MAX;
        }
    }
}
int sun_of_nodes(struct GRAPH_NODE_ *head)
{
    struct GRAPH_NODE_ *temp = head;
    int sum = 0;
    while (temp != NULL)
    {
        sum++;
        temp = temp->next;
    }
    return sum;
}
void Traveling_salesman_problem(struct GRAPH_NODE_ *head ,int matrix[][sun_of_nodes(head)], int place)
{
    int son = highest_node_num();
    int new_mat[son][son];
    for (size_t i = 0; i < son; i++)
    {
        for (size_t j = 0; j < son; j++)
        {
            new_mat[i][j] = SHRT_MAX;
        }
    }
    
    struct GRAPH_NODE_ *temp = head;
    while (temp != NULL)
    {
        for (size_t i = 0; i < son; i++)
        {
           
                printf("matrix[%d][%ld] = %d\n",place,i,matrix[place][i]);
            
              
            
            new_mat[temp->node_num][i] = matrix[place][i];
        }
        temp = temp->next;
    }

    print_matrix(new_mat, son, son); 

    
}
