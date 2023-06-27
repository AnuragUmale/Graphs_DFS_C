/*
==========================================
Name: Anurag Prashant Umale              =   
Student Id: 1887255                      =
E-mail: aumale@ucsc.edu                  =
File: List.c (Implementation of List ADT)=
Class: CSE 101 Spring 2023               =
==========================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// =================== Structures ===================

typedef struct NodeObj* Node;

typedef struct NodeObj{
   int d; // Data for the node
   Node n; // Pointter to next node
   Node p; // 
} NodeObj;

typedef struct ListObj{
   Node f; // Pointer to front of the list
   Node b; // Pointer to the back of the list
   Node c; // Pointer to the current node
   int l; // Length of the list
   int i; // Index of the list
} ListObj;

// =================== Constructors ===================
Node newnode (int x){
    Node n = (Node)malloc(sizeof(NodeObj)); // Dynamically allocating memory
    if(n){ // Checking if pointer is not null
        n->d = x; // Node's data is set to data
        n->n = NULL; // Node's next pointer is set to NULL
        n->p = NULL; // Node's previous pointer is set to NULL
        return n; // returning the Node
    }
    else{
        fprintf(stderr,"Constructor for Node: Error in allocating memory on heap.\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
}

// =================== Destructor ===================

void freenode(Node* n){
    if(n != NULL && *n != NULL){ // Checking if pointer or pointer to pointer is null or not
        free(*n); // freeing the pointer to pointer
        *n = NULL; // setting the pointer to pointer NULL
    }
}

// =================== Constructor For List ===================

List newList(void){
    List l = (List)malloc(sizeof(ListObj)); // dynamically allocating memory
    if(l){ // Pointer is not NULL
        l->b = NULL; // Setting the back pointer NULL
        l->c = NULL; // setting cursor to NULL
        l->f = NULL; // Setting front pointer to NULL
        l->i = -1; // Setting the index to -1
        l->l = 0; // Setting length of to 0
        return l; // returns the list
    }else{
        fprintf(stderr,"Constructor for list: Error in allocating memory on heap.\n");// Error Message
        exit(EXIT_FAILURE); // Exiting
    }
}

// =================== Destructor For List ===================

void freeList(List* pL){
    if(pL != NULL && *pL !=NULL){ // Checking if pointer or pointer to pointer is null or not
        while(length(*pL) > 0){ // Checking if length is greater than 0
            deleteFront(*pL); // deleteing front node
        }
    }
    free (*pL); // freeing the pointer
    *pL = NULL; // setting it to NULL
}

// =================== Access Function ===================

int length(List L){
    if(L == NULL){
        fprintf(stderr,"1. List Error\n2. Function length()\n3. Calling function on a NULL pointer\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    return L->l; // returning the length
}


int front(List L){
    if(L == NULL){
        fprintf(stderr,"1. List Error\n2. Function front()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){
        fprintf(stderr,"1. List Error\n2. Function front()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    return L->f->d; // returning the data of the front node
}

int back(List L){
    if(L == NULL){
        fprintf(stderr,"1. List Error\n2. Function back()\n3. Calling function on a NULL pointer");// Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){
        fprintf(stderr,"1. List Error\n2. Function back()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    return L->b->d; // returning the data of the back node
}

int index (List L){
    if(L == NULL){
        fprintf(stderr,"1. List Error\n2. Function index()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(L->c){ // checking if cursor is not null
        return L->i; // returning the index
    }
    else{ // else
        return -1; // return -1
    }
}


int get(List L){
    if(L == NULL){
        fprintf(stderr,"1. List Error\n2. Function get()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(index(L) < 0){
        fprintf(stderr,"1. List Error\n2. Function get()\n3. Calling function while cursor is undefined\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    return L->c->d; // Returning the cursor data
}

bool equals(List A, List B){
    if(A == NULL || B == NULL){ // checking if pointers are not equal to null
        fprintf(stderr,"1. List Error\n2. Function equals()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(A->l != B->l){ // checking if length are equal
        return false; // returning false
    }
    if(A->l == 0 && B->l == 0){ // if the both list length is 0
        return true; // return true
    }
    Node temp_1 = A->f; // setting the node to value of front's pointer
    Node temp_2 = B->f; // setting the node to value of front's pointer
    while( temp_1 != NULL && temp_2 != NULL){ //  while the pointers are not NULL
        if(temp_1->d != temp_2->d){ // if data is not equal
            free(temp_1); // freeing the pointer
            free(temp_2); // freeing the pointer
            return false; // returning false
        }
        temp_1 = temp_1->n; // setting to the next node
        temp_2 = temp_2->n; // setting to the next node
    }
    free(temp_1); // freeing the pointer
    free(temp_2); // freeing the pointer
   return true;
}

// =================== Manipulation Function ===================


void clear(List L){
    if(L == NULL){
        fprintf(stderr,"1. List Error\n2. Function clear()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    Node temp_node_1 = L->f; // setting the node to front
    while(temp_node_1 != L->b){ // checking if front and back are not equal
        Node temp_node_2 = temp_node_1->n; // setting 
        freenode(&temp_node_1); // freeing the node
        temp_node_1 = temp_node_2; // temp_1 is set to temp_2
    }
    free(L->b); // freeing the pointer
    L->f = L->b = L->c = NULL; // setting front back and cursor to NULL
    L->l = 0; // setting length to 0
    L->i = -1; // setting i == -1
}

void set(List L, int x){
    if(L == NULL){ // Checking the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function set()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function set()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(index(L) < 0){ // Checking if index is less than 0
        fprintf(stderr,"1. List Error\n2. Function set()\n3. Calling function while cursor is undefined\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    L->c->d = x; // setting the data to to cursor's data
}

void moveFront(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function moveFront()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){
        fprintf(stderr,"1. List Error\n2. Function moveFront()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    L->i = 0; // Index is set to 0
    L->c = L->f; // Cursor is set to front pointer
}


void moveBack(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function moveBack()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function moveBack()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    L->i = L->l - 1; // Decrement the index
    L->c = L->b; // cursor is set to back
}

void movePrev(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function movePrev()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function movePrev()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(index(L) < 0){ // Checking if index is less than 0
        fprintf(stderr,"1. List Error\n2. Function set()\n3. Calling function while cursor is undefined\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(L->f != L->c){ // Checking if cursor and front are equal or not
        L->c = L->c->p; // seeting cursor to cursor's previous node
        L->i -= 1; // dcrementing index
    }
    else{ // else
        L->c = NULL; // Setting cursor NULL
        L->i = -1; // Setting index to -1
    }
    
}


void moveNext(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function moveNext()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function moveNext()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(L->c != NULL){ // checking if cursor is NULL
        if(L->c != L->b){ // Checking if cursor and back are not equal
            L->c = L->c->n; // setting cursor to cursor's next node
            L->i += 1; // incrementing indexs
        }
        else{
            L->c = NULL; // setting cursor to NULL
            L->i = -1; // Setting index to -1
        }
    }
}


void prepend(List L, int x){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function prepend()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    Node new_node = newnode(x); // creating new node
    new_node->p = NULL; // setting previous pointor to NULL
    new_node->n = L->f; // next node is set to front's value

    if(length(L) == 0){ // checking if length is 0 or not
        L->f = new_node; //  front is set to new node
        L->b = new_node; // back is set tp new node
    }
    else{ // else
        L->f->p = new_node; // previous is set to new node 
        L->f = new_node; // front is set to new node
    }
    L->l += 1; // list increment
    L->i += 1; // index increment
}

void append(List L, int x){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function append()\n3. Calling function on a NULL pointer");// Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    L->l += 1; // length increment
    Node temp_1 = L->b; // Temporary back node
    Node new_node = newnode(x); // creating new node
    if(L->l > 1){ // List length is greater than 1
        temp_1->n = new_node; // temp next node is set to set to new node
        new_node->p = temp_1; // new node's previous is set to new node
        L->b = new_node; // back pointer is set to new node
    }
    else{
        L->f = new_node; // front is set to new node
        L->b = L->f; // back is set to front node
    }
}

void insertBefore(List L, int x){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function insertBefore()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function insertBefore()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(L->c == L->f){ // checking is cursor equals front
        prepend(L,x); // prepending the element
        return; // returning
    }
    Node new_node = newnode(x); // new node is created
    new_node->p = L->c->p; // previous is set to cursor previous pointor
    new_node->n = L->c; // next node is set to cursor
    L->c->p->n = new_node; // List cursor's previous node's next node is set to new node
    L->c->p = new_node; // List cursor's previous node is set to new node
    L->l += 1; // Length is incremented
    L->i += 1; // Index is incremented
}

void insertAfter(List L, int x){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function insertAfter()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function insertAfter()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(L->i == L->l - 1){ // Checking if index is equal to length - 1
        append(L,x); // appending the element
        return; // returning
    }

    Node new_node = newnode(x); // creatinf new node
    new_node->p = L->c; // setting new node's previous node to List's cursor
    new_node->n = L->c->n; // next node is set to cursor's next node
    L->c->n = new_node; // List's cursor next node is set to new node
    L->c->n->p = new_node; // List cursor's previous node's next node is set to new node
    L->l += 1; // incrementing length
}

void deleteFront(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function deleteFront()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function deleteFront()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    Node temp = L->f; // Temp is set to list's front pointor
    if(index(L) == 0){ // checking ig index equal 0
        L->c = NULL; // cursor is set to NULL
        L->i = -1; // Index is set to -1
        
    }
    else{
        L->i -= 1; // decrement the index
    }
    if(length(L) == 1){ // If length is 1
        clear(L); // clearing the list
        return; // returning
        
    }
    else{ // else
        L->f = L->f->n; // List front pointer is set to List front's next node
        L->f->p = NULL; // List front's previous pointer is set to NULL
    }
    L->l -= 1; // Length is decremented
    freenode(&temp); // free the node

}

void deleteBack(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function deleteBack()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function deleteBack()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    Node temp = L->b; // node is set to back pointor
    if(L->l>1){ // Cheking if length is greater than 1
      L->b = L->b->p; // Back pointor is set to List back's previous pointor
      L->b->n=NULL; // Next node is set to NULL
      if(L->i == L->l-1){ // Checking index equal length - 1
        L->i = -1; // index is set to -1
      }
    }else{
      L->f = NULL; // Setting to NULL
      L->b = NULL; // Setting to NULL
      L->i = -1; // index is set to -1
    }
    L->l -= 1; // length decrement
    freenode(&temp); // freeing the node
}



void delete(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function delete()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(length(L) <= 0){ // cheking if length is 0
        fprintf(stderr,"1. List Error\n2. Function delete()\n3. Calling function on Empty list\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(index(L) < 0){ // Checking if index is less than 0
        fprintf(stderr,"1. List Error\n2. Function delete()\n3. Calling function while cursor is undefined\n"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    if(L->l - 1 == L->i){ // Checking if length  - 1 is equal to Length index
        deleteBack(L); // deleteing back
        return; // returning
    }
    if(L->f == L->c){ // checking front equals cursor
        deleteFront(L); // deleting front
        return; // returing 
    }
    Node temp = L->c; // node is set to cursor
    L->c->p->n = L->c->n; // cursor's previous' next node is set to cursor's next node
    L->c->n->p = L->c->p; // cursor's next's previous node is set to cursor's previous node
    freenode(&temp); // freeing the node
    L->l -= 1; // decrement in length 
    L->i -= 1;// decrememtn in index

}

List copyList(List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function copyList()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    List new_list = newList(); // creating the new list
    Node temp_node = L->f; // temp front pointer
    while(temp_node != NULL){ // Checking pointe r npot equal null
        append(new_list,temp_node->d); // appending the elemnt
        temp_node = temp_node->n; // temp node is set to next
    }
    return new_list; // returning the list
}

List concatList(List A, List B){
    if(A == NULL || B == NULL){ // checking if the pointers is not null
        fprintf(stderr,"1. List Error\n2. Function concatList()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    List L = newList();
    moveFront(A);
    while(index(A) >= 0){
      int x = get(A);
      append(L, x);
      moveNext(A);
    }
    moveFront(B);
    while(index(B) >= 0){
      int x = get(B);
      append(B, x);
      moveNext(B);
    }
    return(L);
}

void printList(FILE* out, List L){
    if(L == NULL){ // checking if the pointer is not null
        fprintf(stderr,"1. List Error\n2. Function printList()\n3. Calling function on a NULL pointer"); // Error Message
        exit(EXIT_FAILURE); // Exiting
    }
    int index_value=index(L); // getting index value
    for(moveFront(L);index(L)>=0;moveNext(L)){ // moving front the elemnt and moving next by checking incex > 0
        fprintf(out,"%d ",get(L));
    }
    fprintf(out,"\n");
    L->i=index_value;
}


