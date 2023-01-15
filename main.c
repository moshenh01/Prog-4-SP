#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char ch;

    while (scanf(" %c", &ch) != EOF )
    { 
       // printf("%c\n", ch);
       if (ch == 'Q'){
              break;
       }
        
        snd1:
        if (ch == 'A')
        {
            int node_amount;
            scanf("%d", &node_amount);
            build_graph(node_amount);
            while (scanf(" %c", &ch) == 1 && ch == 'n')
            {
                build_node_edges();
                ch = '\0';
            }
            goto snd1;
        }
        else if (ch == 'B')
        {
            insert_node();
            
        }

        else if (ch == 'D')
        {
            int node_num;
            scanf("%d", &node_num);
            delete_node(node_num);
    
        }
        else if (ch == 'S')
        {
            print_lowest_route(); // print the lowest route from a node one other node (diakstra).
        }
        else if (ch == 'T')
        {
            // printf("TSP\n");
            TSP(); // print the lowest route from a node one other node (diakstra).

        }

        else
        {
            printf("Invalid input\n");
        }

    }

    rm_graph(head);
    
            
    return 0;
}