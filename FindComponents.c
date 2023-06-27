/*
===================================
Name: Anurag Prashant Umale       =   
Student Id: 1887255               =
E-mail: aumale@ucsc.edu           =
File: FindComponents.c            =
Class: CSE 101 Spring 2023        =
===================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

int main(int argc, char *argv[]) // taking arguments from the command line
{
    if (argc != 3) // checming if the arguments recieved are equal to 3 or not
    {
        fprintf(stderr,"Usage: %s <input file> <output file>\n", argv[0]); // Error mesage 
        exit(EXIT_FAILURE); // exiting in failure
    }
    FILE *in = fopen(argv[1], "r"); // opening the file for reading
    FILE *out = fopen(argv[2], "w"); // opening the file for writing
    if (in == NULL) // chcking if the pointer is equal to NULL
    {
        fprintf(stderr,"Unable to open file %s for reading\n", argv[1]); // Error mesage 
        exit(EXIT_FAILURE); // exiting in failure
    }
    if (out == NULL) // checking if the pointer is equal to NULL
    {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]); // Error mesage 
        exit(EXIT_FAILURE); // exiting in failure
    }

    int num1 = 0; // number 1 is set to 0
    int num2 = 0; // number 2 is set to 0
    int count = 0; // setting the count to 0

    fscanf(in, "%d\n", &count); // scanning the first value from the text file
    Graph new_graph = newGraph(count); // creating the new Graph
    fscanf(in, "%d %d\n", &num1, &num2); // scanning the seconf line

    while (num1 != 0 && num2 != 0) // checking if the number1 and number2 is not equal to 0
    {
        addArc(new_graph, num1, num2); // adding the arc to the graph using the number
        fscanf(in, "%d %d\n", &num1, &num2); // scanning for the two the numbers
    }
    fprintf(out, "Adjacency list representation of G:\n"); // printing the message
    printGraph(out, new_graph); // printing out the graph
    fprintf(out, "\n"); // printing new line

    List graph_list = newList(); // creating the list
    for (int i = 1; i <= getOrder(new_graph); i++) // stating the for loop from 1 to order of the Graph
    {
        append(graph_list, i); // appending the i in the list
    }
    DFS(new_graph, graph_list); // calling the DFS function
    Graph transpose_graph = transpose(new_graph); // calling the transpose function
    DFS(transpose_graph, graph_list); // calling the DFS function
    fprintf(out, "\n"); // printing new line

    count = 0; // count is set to 0
    moveBack(graph_list); // moving back in list
    while (index(graph_list) != -1) // while the index of the list is not equal to -1
    {
        if (getParent(transpose_graph, get(graph_list)) == NIL) // if parent of the element is NIL
        {
            count++; // count is incremented
        }
        movePrev(graph_list); // moving previous in list
    }
    fprintf(out, "G contains %d strongly connected components:\n", count); // printing the message
    for (int i = 1; i <= count; i++) // for loop from 1 to the coung 
    {
        int nilNum = 0; // setting the nil num count to 0
        bool found = false; // setting the flag to false
        fprintf(out, "Component %d:", i); // printing out the message 
        moveBack(graph_list); // moving back in the list
        while (nilNum != i && !found) // while the Nil numb count is not equal to i and not flag
        {
            if (getParent(transpose_graph, get(graph_list)) == NIL) // checking ig the parent of the list value is NIL
            {
                nilNum++; // nil Num count is increment
                if (nilNum == i) // if Nil Num count is equal to i
                {
                    fprintf(out, " %d", get(graph_list)); // printing the message
                    moveNext(graph_list); // moving front in the graph
                    found = true; // flag is set to true
                    while (index(graph_list) != -1 && getParent(transpose_graph, get(graph_list)) != NIL) // while the index of the list is not equal to -1 and the parent is not equal to NIL
                    {
                        fprintf(out, " %d", get(graph_list)); // printing out the element
                        moveNext(graph_list); // moving next in list
                    }
                }
            }
            if (!found) // if not flag
            {
                movePrev(graph_list); // moving previous in list
            }
        }
        if (i != count) // if i is not equal to count
        {
            fprintf(out, "\n"); // printing the new line
        }
    }
    fclose(in); // closing the file
    fclose(out); // closing the file
    freeGraph(&new_graph); // freeing the graph
    freeGraph(&transpose_graph); // freeing the graph
    freeList(&graph_list); // freeing the list
    return EXIT_SUCCESS; // returning the SUCCESS
}