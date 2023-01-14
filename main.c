#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    char ch;
snd2:
    scanf(" %c", &ch);
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
    if (ch == 'B')
    {
        insert_node();
        goto snd2;
    }

    if (ch == 'D')
    {
        int node_num;
        scanf("%d", &node_num);
        delete_node(node_num);
        goto snd2;
    }
    if (ch == 'S')
    {
        print_lowest_route(); // print the lowest route from a node one other node (diakstra).
        goto snd2;
    }
    if (ch == 'T')
    {
        //printf("TSP\n");
        TSP(); // print the lowest route from a node one other node (diakstra).
        
        goto snd2;
    }
    if (ch == 'Q')
    {
        rm_graph(head);
        printf("Quit\n");
        return 0;
    }

    else
    {
        printf("Invalid input");
    }
    return 0;
}