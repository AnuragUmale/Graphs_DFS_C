/*
==========================================
Name: Anurag Prashant Umale              =   
Student Id: 1887255                      =
E-mail: aumale@ucsc.edu                  =
File: List.h                             =
Class: CSE 101 Spring 2023               =
==========================================
*/

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdio.h>
#include <stdbool.h>

typedef struct ListObj* List;


// ========= Constructors =========
List newList(void);

// ========= Destructors =========

void freeList(List* pL);

// ========= Access Function =========

int length(List L);

int front(List L);

int back(List L); 

int get(List L);

int index(List L);

bool equals(List A, List B);

// ========= Manipulation Functions =========

void clear(List L);

void set(List L, int x);

void moveFront(List L);  

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);  

void insertAfter(List L, int x); 

void deleteFront(List L);  

void deleteBack(List L);

void delete(List L);

List copyList(List L);

List concatList(List A, List B);

void printList(FILE* output, List L);

#endif