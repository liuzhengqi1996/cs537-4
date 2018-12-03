
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
#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "avltree.h"

extern void * malloc537(size_t size);
extern void free537(void *ptr);
extern void *realloc537(void *ptr,size_t size);
extern void memcheck537(void *ptr,size_t size);
static Node * root;
//root -> right = NULL;
//root -> left = NULL;

//= (Node*)malloc(sizeof(Node));//the node of memory tree



/*
 allocate memory by malloc, store a tuple of address and length in AVL Tree
 */


void * malloc537(size_t size){
	void * return_ptr;
	//malloc a size 0 pointer
	if(size == 0){
		printf("malloc537: Need to malloc a size 0 pointer.\n");
		     }
	//malloc the pointer
	return_ptr = malloc(size);
	//create a node for this pointer
	//Node * newnode = create_node(return_ptr,size);
	//if allocated memory was previously freed,delete all the nodes in the range
	for (size_t i=0;i<size;i++ ){
		root = delete_node(root,return_ptr+i);
	}
	//insert the node to the tree
	root= insert_node(root,return_ptr,size);
	return return_ptr;
				}
//free537 is a safe free function
void free537(void *ptr){
	int *temp1 = search_range(root, ptr);
	
	//search ptr in the tree
	Node *temp2 =search_node(root,ptr);
	if (ptr == NULL){
		printf("free537: Freeing a null pointer\n");	
		exit(-1);	
			}
	//if ptr cannot be found in tree or any range within the tree, then the memory has not be allocated previously
	else if(temp1 == 0 && temp2 == NULL){
		printf("free537: Freeing memory has not been allocated by malloc537\n");
		exit(-1);
			}
	// If ptr can be found in the range, but not as the start address
	else if (temp1 == 1 && temp2 == NULL) {
		printf("free537: Freeing memory that is not the first byte of the range of memory that was allocated\n");
		exit(-1);
	}
	//check if the pointer is double freed
	if(temp2 -> flag == 0){
		printf("free537: Freeing memory that was previously freed (double free)\n");
		exit(-1);		
				}
	//turn the node flag to 0, free the pointer
	temp2 -> flag =0;
	free(ptr);	
	}

//similar to realloc, but checking on the pointer
void *realloc537(void *ptr, size_t size){
	void * return_ptr;
	//if ptr is NULL,same as malloc537
	if(ptr == NULL){
		return malloc537(size);
	}
	//if size is 0,same to free537
	else if(size == 0){
		printf("realloc537: Need to realloc a size 0 pointer.\n");
		free537(ptr);
		return NULL;
			}
	//general case
	else{
		//search the pointer in the tree
		Node * temp = search_node(root,ptr);
		//if the pointer has been allocated ,delete it
		if (temp != NULL) root = delete_node(root,temp);
		//realloc for the pointer
		return_ptr = realloc(ptr,size);
		//create node for the return_ptr,and insert it in to tree
		//node * newnode = create_node(return_ptr,size);
		insert_node(root,return_ptr,size);
		return return_ptr;	
	}
}
//check pointer with address and the range
void memcheck537(void *ptr,size_t size){
	//search the pointer in the tree
	Node * temp = search_node(root,ptr);
	if(temp == NULL){
		printf("memcheck537: The pointer has not been allocated before.\n");
		exit(0);	
	}
	//check if the pointer has been freed
	else if (temp ->flag == 0){
		printf("memcheck537: The pointer has already been freed.\n");
	}
	//check if the size is out of the range of pointer
	else if (size > temp -> len){
		printf("memcheck537: The pointer %p contains %d byte when %d bytes is needed.\n", ptr, (int)temp -> len, (int)size);
	}
}
