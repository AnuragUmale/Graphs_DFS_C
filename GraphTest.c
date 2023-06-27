/*
=================================================
Name: Anurag Prashant Umale                     =   
Student Id: 1887255                             =
E-mail: aumale@ucsc.edu                         =
File: GraphTest.c (Testing of Graph ADT)        =
Class: CSE 101 Spring 2023                      =
=================================================
*/

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>

#define SUCCESS 1 // defining success as 1
#define FAILURE 0 // defining failure as 0


bool v = false; // global falg for verbose

int constructor_and_destructor_test(){
    for (int n = 1; n < 100; n++) { // running loop 100 times
        Graph G = newGraph(n); // creating new graph
        freeGraph(&G); // deleting the grpah
        if (G != NULL) { // checking if the pointer is not equal to NULL
            return FAILURE; // returning FAILURE
        }
    }
    return SUCCESS; // returning success
}

int getOrder_test(){
    for(int n = 1; n < 100; n++){ // running ht eloop 100 times
        Graph G = newGraph(n); // creating the new graph
        int order = getOrder(G); // getting the order of the graph
        if (order != n) { // checking if the order is not equal to n
            return FAILURE; // returning failure
        }
        freeGraph(&G); // freeing the graph
    }
    return SUCCESS; // returning success
}

int getSize_test(){
    for(int n = 1; n < 100; n++){ // running the loop 100 times
        Graph G = newGraph(n); // creating the graph
        if (getSize(G) != 0) { // checking if size if not equal to n
            return FAILURE; // returning failure
        }
        for(int j = 1; j <= n; j++){ // running the loop 100 times
            addArc(G,j,(j % n ) + 1); // adding arc in thr graph
            if (getSize(G) != j) { // checking the size of the graph is not  equal to J
                return FAILURE; // returning failure
            }
        }
        freeGraph(&G); // freeing the Graph
    }
    return SUCCESS; // returning success
}

int dfs_and_helper_test(){
    List L = newList(); // creating new list
    for(int n = 1; n < 10; n++){ // loop 10 times
        clear(L); // clearing the list
        Graph G = newGraph(n); // creating new Graph
        for(int i = 0; i < n; i++){ // loop from 0 to n - 1
            append(L,i); // appending the i value to list L
        }
        for (int i = 0; i < 10; i++) { // loop 10 times
            int u = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph 
            int v = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph 
            addEdge(G, u, v);  // adding the edge
        }
        DFS(G,L); // calling DFS
        if(v){ // checking if verbose is enabled
            fprintf(stdout,"Edge\n"); // printing info
            fprintf(stdout, "===========\n"); // printing info
            fprintf(stdout, "x:  d  f  p\n"); // printing info
            for (int i = 1; i <= n; i++)
            {
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i)); // printing info by calling the functions
            }
            fprintf(stdout, "===========\n"); // printing info
        }
        freeGraph(&G); // freeing the graph
    }
    for(int n = 1; n < 10; n++){ // loop 10 times
        clear(L); // clearing the list
        Graph G = newGraph(n); // creating new Graph
        for(int i = 0; i < n; i++){ // loop from 0 to n - 1
            append(L,i); // appending the i value to List L
        }
        for (int i = 0; i < 10; i++) { // loop 10 times
            int u = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph
            int v = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph
            addArc(G, u, v); // adding the arc
        }
        DFS(G,L); // calling DFS
        if(v){ // checking if verbose is enabled
            fprintf(stdout,"Arcs\n"); // printing info
            fprintf(stdout, "===========\n"); // printing info
            fprintf(stdout, "x:  d  f  p\n"); // printing info
            for (int i = 1; i <= n; i++) // looping from 1 to n 
            { 
                fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i)); // printing info by calling the function
            }
            fprintf(stdout, "===========\n"); // printing info
        }
        freeGraph(&G); // freeing the Graph
    }
    freeList(&L); // freeing the list
    return SUCCESS; // returning the succes
}

int copygraph_test(){
    
    for(int i = 0; i < 10; i++){ // running the loop 10 times
        Graph G = newGraph(i); // creating the graph of order i
        Graph H = copyGraph(G); // coping the graph G
        if(getOrder(G) != getOrder(H)){ // checking if the order is not equal
            return FAILURE; // returning failure
        }
        freeGraph(&G); // freeing the Graph
        freeGraph(&H); // freeing the Graph
    }
    return SUCCESS; // returning success
}


int transpose_and_print_graph(){
    if(v){ // checking if verbose is enabled
        fprintf(stderr,"Unidirected Graph\n"); // printing info
    }
    for(int i = 1; i <= 10; i++){ // looping 10 times
        Graph G = newGraph(i); // creating new graph of order i
        for (int i = 0; i < 10; i++) { // looping 10 times
            int u = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph
            int v = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph
            addEdge(G, u, v); // adding the edge
        }
        if(v){ // checking if verbose is enabled
            fprintf(stdout,"====== Normal Graph ======\n"); // printing the info
            printGraph(stdout,G); // priting the Graph
            fprintf(stdout,"====== Transposed Graph ======\n"); // printing the info
        }
        Graph H = transpose(G); // transpose of graph G
        if(v){ // checking if verbose is enabled
            printGraph(stdout,H); // printing out the Graph
        }
        freeGraph(&G); // freeing the graph 
        freeGraph(&H); // freeing the graph
    }
    if(v){ // checking if verbose is enabled
        fprintf(stdout,"Directed Graph\n"); // printing the info
    }
    for(int i = 1; i <= 10; i++){
        Graph G = newGraph(i);
        for (int i = 0; i < 10; i++) {
            int u = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph
            int v = (rand() % getOrder(G)) + 1; // getting random number in limit of order of graph
            addArc(G, u, v); // adding Arc in the Graph
        }
        if(v){ // checking if verbose is enabled
            fprintf(stdout,"====== Normal Graph ======\n"); // printing the info
            printGraph(stdout,G); // printing out the Graph
            fprintf(stdout,"====== Transposed Graph ======\n"); // printing the info
        }
        Graph H = transpose(G); // transpose of graph G
        if(v){ // checking if verbose is enabled
            printGraph(stdout,H); // printing out the Graph
        }
        freeGraph(&G); // freeing the graph
        freeGraph(&H); // freeing the graph
    }
    return SUCCESS; // returning the success 
}

void tester(){
    fprintf(stdout,"=================================================\n"); // printing the info
    if(constructor_and_destructor_test()){ // checking if success is returned
        fprintf(stdout,"Constructor and Destructor Test passed          =\n"); // printing the info
    }
    if(getSize_test()){ // checking if success is returned
        fprintf(stdout,"Get Size Test passed                            =\n"); // printing the info
    }
    if(getOrder_test()){ // checking if success is returned
        fprintf(stdout,"Order Test passed                               =\n"); // printing the info
    }
    if(dfs_and_helper_test()){ // checking if success is returned
        fprintf(stdout,"Discover Time Test passed                       =\n"); // printing the info
        fprintf(stdout,"Finish Time Test passed                         =\n"); // printing the info
        fprintf(stdout,"Parent Test passed                              =\n"); // printing the info
        fprintf(stdout,"Adding Edge Test passed                         =\n"); // printing the info
        fprintf(stdout,"Adding Arc Test passed                          =\n"); // printing the info
        fprintf(stdout,"DFS Test passed                                 =\n"); // printing the info
    }
    if(copygraph_test()){ // checking if success is returned
        fprintf(stdout,"Copy Graph Test passed                          =\n"); // printing the info
    }
    if(transpose_and_print_graph()){ // checking if success is returned
        fprintf(stdout,"Transpose Graph and Print Graph Test passed     =\n"); // printing the info
    }
    fprintf(stdout,"=================================================\n"); // printing the info
}

int main(int argc, char **argv)
{
    int opt = 0; // storing the option from commandline
    while( (opt = getopt(argc,argv,"v")) != -1){ // while option is not equal to -1
        switch(opt){ // switching accoring to opt
            case 'v': // case v for verbpse
                v = true; // make verbose flag ture
                break; // breaking out the loop
            default: // default value
                fprintf(stdout,"You have entered the wrong option the program will run without verbose\n"); //error message
                break; // breaking through the loop
        }
    }
    tester(); // calling the tester function
    if(!v){ // checking if the flag is not enables
        fprintf(stdout,"****************** Verbose mode is off ******************\n"); // message
        fprintf(stdout,"You can pass -v through command line to enable verbose. *\n./GraphTest -v \t\t\t\t\t\t*\n"); // message
        fprintf(stdout,"*********************************************************\n"); // message

    }
    return EXIT_SUCCESS; // returning success 
}