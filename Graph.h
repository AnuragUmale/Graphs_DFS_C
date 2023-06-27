/*
==============================
Name: Anurag Prashant Umale  =   
Student Id: 1887255          =
E-mail: aumale@ucsc.edu      =
File: Graph.h                =
Class: CSE 101 Spring 2023   =
==============================
*/

#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_

#include <stdio.h>
#include "List.h" // Including the list ADT

#define UNDEF -1 // defining UNDEF as -1
#define NIL 0 // defining NIL as 0
#define WHITE 0 // defining WHITE as 0
#define GRAY 1 // defining GRAY as 1
#define BLACK 2 // defining BLACK as 2

typedef struct GraphObj* Graph; // typecasting the object pointer to type Graph

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif