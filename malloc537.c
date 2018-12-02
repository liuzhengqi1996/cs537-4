
////////////////////////////////////////////////////////////////////////////////
// Main File:        
// This File:        malloc537.c
// Other Files:      
//                   
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////
#include <studio.h>
#include <stdlib.h>
#include "malloc537.h"
#include "avltree.h"

extern node * root;//the node of memory tree


/*
 allocate memory by malloc, store a tuple of address and length in AVL Tree
 */


void * malloc537(size_t size){
	void * return_ptr;
	if(size == 0){
		printf("allocating a pointer of size 0\n");
		     }
	return_ptr = malloc(size);
	node * newnode = create_node(return_ptr,size);
	delete_node(newnode);
	insert_node(newnode);
	return return_ptr;
		

				}

void free537(void *ptr){
	node *temp;
	temp=search(ptr);
	if (ptr == NULL){
		printf("freeing a null pointer");	
		exit(-1);	
			}
	if(temp == NULL){
		print("free memory has not be allocated by malloc537");
		exit(-1);
			}
	if(temp -> flag == 0){
		print("double free");
		exit(-1);		
				}
	temp -> flag =0;
	free(ptr);	
	}


void *realloc537(void *ptr, size_t size){
	void * return_pointer;
	node * remove_node = NULL;
	if(ptr == NULL){
		return malloc537(size);
	}
	else if(size == 0){
		free537(ptr);
		return NULL;
			}
	else{
		node * temp = search(ptr);
		delete_node(temp);
		free537(temp);
		return_ptr = realloc(size);
		node * newnode = create_node(return_ptr);
		insert_node(newnode);
		}

				}

void memcheck537(void *ptr,size_t size){
	node * temp = search(ptr);
	if(temp == NULL){
		
			}


}
