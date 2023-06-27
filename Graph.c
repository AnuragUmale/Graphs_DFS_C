/*
=================================================
Name: Anurag Prashant Umale                     =   
Student Id: 1887255                             =
E-mail: aumale@ucsc.edu                         =
File: Graph.c (Implementation of Graph ADT)     =
Class: CSE 101 Spring 2023                      =
=================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"


typedef struct GraphObj
{
    List *neighbour; // Adjacency list
    int *color; // Color array
    int *parent; // parent array
    int *discover_time; // discover time array
    int *finish_time; // finish time array
    int order; // order of graph
    int size; // size of the graph
    int DFS; // DFS search value
} GraphObj;

Graph newGraph(int n)
{
    Graph new_graph = (Graph)malloc(sizeof(GraphObj)); // Dynamically allocating memory
    if (new_graph) // if pointer is not equal to NULL
    {
        new_graph->size = 0; // size is set to 0
        new_graph->order = n; // order is set to n
        new_graph->DFS = NIL; // DFS value is set to NIL
        new_graph->neighbour = (List *)calloc(n + 1, sizeof(List)); // Dynamically allocating memory
        if (!new_graph->neighbour) // checking if pointer is equal to NULL
        {
            free(new_graph); // freeing the pointer
            new_graph = NULL; // setting the pointer to NULL
            fprintf(stderr, "1.Graph Error.\n2.Graph newGraph(int n).\n3.Error allocating memory dynamically.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        new_graph->color = (int *)calloc(n + 1, sizeof(int)); // Dynamically allocating memory
        if (!new_graph->color) // checking if pointer is equal to NULL
        {
            free(new_graph->neighbour); // freeing the pointer
            free(new_graph); // freeing the pointer
            new_graph = NULL; // setting the pointer to NULL
            fprintf(stderr, "1.Graph Error.\n2.Graph newGraph(int n).\n3.Error allocating memory dynamically.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        new_graph->parent = (int *)calloc(n + 1, sizeof(int)); // Dynamically allocating memory
        if (!new_graph->parent) // checking if pointer is equal to NULL
        {
            free(new_graph->color); // freeing the pointer
            free(new_graph->neighbour); // freeing the pointer
            free(new_graph); // freeing the pointer
            new_graph = NULL; // setting the pointer to NULL
            fprintf(stderr, "1.Graph Error.\n2.Graph newGraph(int n).\n3.Error allocating memory dynamically.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        new_graph->discover_time = (int *)calloc(n + 1, sizeof(int)); // Dynamically allocating memory
        if (!new_graph->discover_time) // checking if pointer is equal to NULL
        {
            free(new_graph->parent); // freeing the pointer
            free(new_graph->color); // freeing the pointer
            free(new_graph->neighbour); // freeing the pointer
            free(new_graph); // freeing the pointer
            new_graph = NULL; // setting the pointer to NULL
            fprintf(stderr, "1.Graph Error.\n2.Graph newGraph(int n).\n3.Error allocating memory dynamically.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        new_graph->finish_time = (int *)calloc(n + 1, sizeof(int)); // Dynamically allocating memory    
        if (!new_graph->finish_time) // checking if pointer is equal to NULL
        {
            free(new_graph->discover_time); // freeing the pointer
            free(new_graph->parent); // freeing the pointer
            free(new_graph->color); // freeing the pointer
            free(new_graph->neighbour); // freeing the pointer
            free(new_graph); // freeing the pointer
            new_graph = NULL; // setting the pointer to NULL
            fprintf(stderr, "1.Graph Error.\n2.Graph newGraph(int n).\n3.Error allocating memory dynamically.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        for (int i = 0; i <= n; i++) // starting the loop from 0 to n 
        {
            new_graph->neighbour[i] = newList(); // assigning new list at each index
            new_graph->color[i] = WHITE; // assigning white at each colour index
            new_graph->parent[i] = NIL; // assigning NIL at each parent index
            new_graph->discover_time[i] = UNDEF; // assigning UNDEF value at each discover time index
            new_graph->finish_time[i] = UNDEF; // assigning UNDEF value at each finsih time index
        }
        return new_graph; // returning the graph pointer
    }
    else // else
    {
        fprintf(stderr, "1.Graph Error.\n2.Graph newGraph(int n).\n3.Error allocating memory dynamically.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

void freeGraph(Graph *pG)
{
    if (pG != NULL && (*pG) != NULL) // checking if pointer and pointer to pointer are not equal to NULL
    {
        for (int i = 0; i <= (*pG)->order; i++) // starting the loop from 0 to order of graph
        {
            freeList(&(*pG)->neighbour[i]); // freeing the list at each index
        }
        free((*pG)->parent); // freeing the pointer
        free((*pG)->color); // freeing the pointer
        free((*pG)->discover_time); // freeing the pointer
        free((*pG)->finish_time); // freeing the pointer
        free((*pG)->neighbour); // freeing the pointer
        (*pG)->parent = NULL; // setting the pointer to NULL
        (*pG)->color = NULL; // setting the pointer to NULL
        (*pG)->discover_time = NULL; // setting the pointer to NULL
        (*pG)->finish_time = NULL; // setting the pointer to NULL
        (*pG)->neighbour = NULL; // setting the pointer to NULL
        free(*pG); // freeing the pointer
        (*pG) = NULL; // setting the pointer to NULL
    }
}

int getOrder(Graph G)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        return G->order; // returning the order of the graph
    }
    else // else
    {
        fprintf(stderr, "1.Graph Error.\n2.Error: getOrder(Graph G).\n3.Calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

int getSize(Graph G)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        return G->size; // returning the size of the Graph
    }
    else
    {
        fprintf(stderr, "1.Graph Error.\n2.Error: getSize(Graph G).\n3.Calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

int getParent(Graph G, int u)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        if (u < 1 || u > getOrder(G)) // checking if u is in the bounds
        {
            fprintf(stderr, "1.Graph Error.\n2.Error: int getParent(Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        if (G->DFS == NIL) // checking if the DFS is called 
        {
            return NIL; // returning the NIL value
        }
        return G->parent[u]; // returning the parent value at index u.
    }
    else
    {
        fprintf(stderr, "1.Graph Error.\n2.Error: int getParent(Graph G, int u).\n3.Calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}
int getDiscover(Graph G, int u)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        if (u < 1 || u > getOrder(G)) // checking if u is in the bounds
        {
            fprintf(stderr, "1.Graph Error.\n2.Error: int getDiscover(Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        if (G->DFS == NIL)  // checking if the DFS is called 
        {
            return UNDEF; // Returning the UNDEF value
        }
        return G->discover_time[u]; // reuturning the discover_time at index u
    }
    else
    {
        fprintf(stderr, "1.Graph Error.\n2.Error: int getDiscover(Graph G, int u).\n3.Calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}
int getFinish(Graph G, int u)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        if (u < 1 || u > getOrder(G)) // checking if u is in the bounds
        {
            fprintf(stderr, "1.Graph Error.\n2.Error: int getFinish(Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        if (G->DFS == NIL)  // checking if the DFS is called 
        {
            return UNDEF; // returning the UNDEF value
        }
        return G->finish_time[u]; // return the finish time at index u
    }
    else
    {
        fprintf(stderr, "1.Graph Error.\n2.Error: int getFinish(Graph G, int u).\n3.Calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

void addEdge(Graph G, int u, int v)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        if (u < 1 || v < 1) // checking if u and v are in the bounds
        {
            fprintf(stderr,"1.Graph Error.\n2.Error: void getPath(List L, Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }

        if (u > getOrder(G) || v > getOrder(G)) // checking if u and v are in the bounds
        {
            fprintf(stderr,"1.Graph Error.\n2.Error: void getPath(List L, Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }

        if (length(G->neighbour[v]) == 0) // checking length of the list is equal to 0
        {
            append(G->neighbour[v], u); // appending u value in the list at index v 
            G->size++; // increasing the size of the graph
        }
        else // else
        {
            moveFront(G->neighbour[v]); // moving front the element of the list at index v

            for (int i = 0; i <= length(G->neighbour[v]); i++) // starting the for loop from 0 to length of the list at index v
            {
                if (get(G->neighbour[v]) > u) // chceking if the list value at index v is grater than v
                {
                    insertBefore(G->neighbour[v], u); // inserting before element at index v 
                    G->size++; // incrementing the size of graph
                    break; // breaking the loop
                }
                if(get(G->neighbour[v]) == u){ // checking if value at index v is  equal to u
                    break; // breaking the loop
                }
                else // else
                {
                    moveNext(G->neighbour[v]); // moving nexing the list at index v
                    if (index(G->neighbour[v]) == -1) // chceking if index of list at index v equal to -1
                    {
                        append(G->neighbour[v], u); // appending the value at v 
                        G->size++; // incrementing the size
                        break; // breaking from the loop
                    }
                }
            }
        }

        if (length(G->neighbour[u]) == 0) // checking length of the list is equal to 0
        {
            append(G->neighbour[u], v); // appending v value in the list at index u 
        }
        else // else
        {
            moveFront(G->neighbour[u]); // moving front the element of the list at index u
            for (int i = 0; i <= length(G->neighbour[u]); i++) // starting the loop from 0 to the length of the list 
            {
                if (get(G->neighbour[u]) > v) // checking if the value of the list is greater than v
                {
                    insertBefore(G->neighbour[u], v); // inseting the element before

                    break; // breaking through the loop
                }
                if(get(G->neighbour[u]) == v){ // checking if the list element and the value v is equal 
                    break; // breaking out og the loop
                }
                else // else
                {
                    moveNext(G->neighbour[u]); // moving front in the list
                    if (index(G->neighbour[u]) == -1) // checking if the index is not equal to -1
                    {
                        append(G->neighbour[u], v); // appending to the list

                        break; // breaking out the loops
                    }
                }
            }
        }
    }
    else{
        fprintf(stderr,"1.Graph Error.\n2.Error: void addEdge(Graph G, int u, int v).\n3.Calling function on NULL pointer.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}
void addArc(Graph G, int u, int v)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        if (u < 1 || v < 1) // checking if u and v are in the bounds
        {
            fprintf(stderr,"1.Graph Error.\n2.Error: void getPath(List L, Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }

        if (u > getOrder(G) || v > getOrder(G)) // checking if u and v in the bounds
        {
            fprintf(stderr,"1.Graph Error.\n2.Error: void getPath(List L, Graph G, int u).\n3.The value is out of bounds.\n"); // Error Message
            exit(EXIT_FAILURE); // Exiting in failure
        }
        if (length(G->neighbour[u]) == 0) // checking length of the list is equal to 0
        {
            append(G->neighbour[u], v); // appending u value in the list at index v 

            G->size++; // increasing the size of the graph
        }
        else
        {
            moveFront(G->neighbour[u]); // moving front the element of the list at index u
            for (int i = 0; i <= length(G->neighbour[u]); i++)
            {
                if (get(G->neighbour[u]) > v) // checking ig the element at index u of the array is greater than v
                {
                    insertBefore(G->neighbour[u], v); // inserting before the element

                    G->size++; // increasing the size of the graph

                    break; // breaking out of the loop
                }
                if(get(G->neighbour[u]) == v){ // checking if the element in hte index u is equal to v
                    break; // breaking out of the loop
                }

                else // else
                {
                    moveNext(G->neighbour[u]); // moving next in the list
                    if (index(G->neighbour[u]) == -1) // checking if the index is equal to -1
                    {
                        append(G->neighbour[u], v); // appending the value v in list at index u

                        G->size++; // increasing the size of the graph

                        break; // breaking out of the loop
                    }
                }
            }
        }
    }
    else{
        fprintf(stderr,"1.Graph Error.\n2.void addArc(Graph G, int u, int v).\n3.Calling Function on NULL pointer."); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

int Visit(Graph G, List S, int u, int init_time)
{
    int t = init_time; // declearing temporary time variable
    t += 1; // incrementing by 1
    G->discover_time[u] = t; // discover time is set to temp_time variable
    G->color[u] = GRAY; // settign the color equal to gray
    List neighbour = G->neighbour[u]; // Getting the list of the neighbour at the index u
    if (length(neighbour) > 0) // checking if the length is greater than 0
    {
        moveFront(neighbour); // moving front the variable
        while (index(neighbour) >= 0) // checking index is greater than 0
        {
            int x = get(neighbour); // getting the element from the list
            if (G->color[x] == WHITE) // checking if the color at the index is equal to WHITE
            {
                G->parent[x] = u; // setting the parent value to u at index u
                t = Visit(G, S, x, t); // recursive call of the function
            }
            moveNext(neighbour); // moving next in the list
        }
    }

    G->color[u] = BLACK; // setting the color at the index u BLACK
    t++; // incrementing t
    G->finish_time[u] = t; // finish time is set to temp_time at index t
    prepend(S, u); // prepending list S with u
    return t; // returning the time
}

void DFS(Graph G, List S)
{
    if(G) // checking  if pointer is not equal to NULL
    {
        if (length(S) != getOrder(G)) // checking if the length and order of graph are not equal
        {
            fprintf(stderr,"1.Graph Error.\n2.void DFS(Graph G, List S).\n3.Error the length of the List is not equal to the List.\n"); // Error Message
            exit(-1);
        }
        int init_time = 0; // setting the initial time to 0

        for (int i = 0; i <= getOrder(G); i++)
        {
            G->color[i] = WHITE; // setting the color to WHITE for order of the Graph
        }
        List newS = newList(); // creating new list

        while (length(S) > 0) // while length of the list is greater than 0
        {

            G->DFS = front(S); // getting the DFS value from the list
            deleteFront(S); // deleting the first elemnt

            if (G->color[G->DFS] == WHITE) // if the color at the index is WHITE
            {
                init_time = Visit(G, newS, G->DFS, init_time); // calling the visit function and storing returning value in init_time
            }
        }

        moveFront(newS); // moving front
        while (index(newS) >= 0) // while the index of the list is greater than 0
        {
            int x = get(newS); // getting the value from the list
            append(S, x); // appending the value to list
            moveNext(newS); // moving front in the list
        }
        freeList(&newS); // freeing the list
    }
    else{
        fprintf(stderr,"1.Graph Error.\n2.void DFS(Graph G, List S).\n3.Error the pointer is equal to NULL.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

Graph transpose(Graph G)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        Graph temp_graph = newGraph(getOrder(G)); // creating a new Graph 
        for (int i = 1; i <= getOrder(G); i++) // for loop starting from 1 to order of Graph
        {
            List neighbour = G->neighbour[i]; // List of adjacency is taken
            if (length(neighbour) > 0) // checking if the length is greater than 0
            {
                moveFront(neighbour); // moving front in the list
                while (index(neighbour) != -1) // while index is not equal to -1
                {
                    int list_value = get(neighbour); // getting the value from the list
                    addArc(temp_graph, list_value, i); // Adding the arc in the list
                    moveNext(neighbour); // moving in the list
                }
            }
        }
        return temp_graph; // returning the graph
    }
    else // else
    {
        fprintf(stderr, "1.Graph Error.\n2.void transpose(Graph G).\n3.Calling Function on NULL pointer."); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

Graph copyGraph(Graph G)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        Graph copyG = newGraph(getOrder(G)); // creating new graph
        for (int i = 0; i <= getOrder(copyG); i++) // for loop from 0 to the order of the graph
        {
            if (length(G->neighbour[i]) > 0) // checking if the length is 
            {
                moveFront(G->neighbour[i]); // moving front in the list
                while (index(G->neighbour[i]) != -1) // cehcking if the index is not equal to -1
                {
                    addArc(copyG, i, get(G->neighbour[i])); // adding Arc
                    moveNext(G->neighbour[i]); // moving next in the list
                }
            }
        }
        copyG->order = getOrder(G); // geting the order of the graph
        return copyG; // returning the copy graph
    }
    else
    {
        fprintf(stderr, "1.Graph Error.\n2.void copyGraph(Graph G).\n3.Calling Function on NULL pointer."); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

void printGraph(FILE *out, Graph G)
{
    if (G) // checking  if pointer is not equal to NULL
    {
        for (int i = 1; i <= getOrder(G); i++) // for loop starting from 1 to order of the graph
        {
            fprintf(out, "%d:", i); // printing out the index i in out FILE
            if (length(G->neighbour[i]) != 0) // checking if the lis is not equal to 0
            {
                fprintf(out, " "); // printing out the blank space
                moveFront(G->neighbour[i]); // moving front in the list
                while (index(G->neighbour[i]) != -1) // checking if the index is not euqla to -1
                {
                    fprintf(out, "%d", get(G->neighbour[i])); // printing out the list element
                    moveNext(G->neighbour[i]); // moving front in the list
                    if (index(G->neighbour[i]) != -1) // checking if the index is not equal to -1
                    {
                        fprintf(out, " "); // printing the blank space
                    }
                    else // else
                    {
                        if (i != getOrder(G)) // checking i is not equal to order of the Graph
                        {
                            fprintf(out, "\n"); // printing new line in the out FILE
                        }
                    }
                }
            }
            else // else
            {
                fprintf(out, "\n"); // printing the new line in the out FILE
            }
        }
        fprintf(out, "\n"); // printing the new line in the out FILE
    }
    else // else
    {
        fprintf(stderr, "1.Graph Error.\n2.void printGraph(FILE *out, Graph G).\n3.Calling Function on NULL pointer."); // Error Message
        exit(EXIT_FAILURE); // Exiting in failure
    }
}

