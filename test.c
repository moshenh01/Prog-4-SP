#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    int priority;
 
    struct node* next;
 
} Node;
Node* newNode(int d, int p)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->priority = p;
    temp->next = NULL;
 
    return temp;
}
int peek(Node** head) { return (*head)->data; }
 
// Removes the element with the
// highest priority form the list
void dequeue(Node** head)
{
    Node* temp = *head;
    (*head) = (*head)->next;
    free(temp);
}
void enqueue(Node** head, int d, int p)
{
    Node* start = (*head);
 
    // Create new Node
    Node* temp = newNode(d, p);
 
    // Special Case: The head of list has
    // bigger priority than new node
    if ((*head)->priority > p) {
 
        // Insert New Node before head
        temp->next = *head;
        (*head) = temp;
    }
    else {
 
        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL
               && start->next->priority < p) {
            start = start->next;
        }
 
        // Either at the ends of the list
        // or at required position
        temp->next = start->next;
        start->next = temp;
    }
}
    // Function to check is list is empty
    int isEmpty(Node** head) { return (*head) == NULL; }

int main()
{
 
    // Create a Priority Queue
    // 7->4->5->6
    Node* pq = newNode(4, 1);
    enqueue(&pq, 5, 2);
    enqueue(&pq, 6, 3);
    enqueue(&pq, 7, 0);
 
    while (!isEmpty(&pq)) {
        printf("%d", peek(&pq));
        dequeue(&pq);
    }
    return 0;
}