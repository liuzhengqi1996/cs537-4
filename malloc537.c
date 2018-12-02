
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


void * malloc537(size_t size){i
	void * return_ptr;
	node * remove_node = NULL;
	if(size == 0){
		printf("allocating a pointer of size 0\n");
		     }
	return_ptr = malloc(size);

	create_ptr(return_ptr,size);


				}
