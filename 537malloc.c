
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
		printf("allocating a pointer of size 0\n");
		     }
	//malloc the pointer
	return_ptr = malloc(size);
	//create a node for this pointer
	//Node * newnode = create_node(return_ptr,size);
	//if allocated memory was previously freed,delete all the nodes in the range
	for (long i=0;i<size;i++ ){
		root = delete_node(root,return_ptr+i);
	}
	//insert the node to the tree
	root= insert_node(root,return_ptr,size);
	return return_ptr;
				}

void free537(void *ptr){
	//search ptr in the tree
	Node *temp = (Node*)malloc(sizeof(Node));
	//search the pointer in the tree
	temp=search_node(root,ptr);
	if (ptr == NULL){
		printf("freeing a null pointer\n");	
		exit(-1);	
			}
	//if ptr cannot be found in tree, then means the memory has not be allocated eith malloc537().
	if(temp == NULL){
		printf("free memory has not been allocated by malloc537\n");
		exit(-1);
			}
	//check if the pointer is double freed
	if(temp -> flag == 0){
		printf("double free\n");
		exit(-1);		
				}
	//turn the node flag to 0, free the pointer
	temp -> flag =0;
	free(ptr);	
	}


void *realloc537(void *ptr, size_t size){
	void * return_ptr;
	//if ptr is NULL,same as malloc537
	if(ptr == NULL){
		return malloc537(size);
	}
	//if size is 0,same to free537
	else if(size == 0){
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

void memcheck537(void *ptr,size_t size){
	//search the pointer in the tree
	Node * temp = search_node(root,ptr);
	if(temp == NULL){
		printf("the pointer hasn't allocated\n");
			}
	//check if the pointer has been freed
	else if (temp ->flag == 0){
		printf("the pointer has benn freed\n");
	}
	//check if the size is out of the range of pointer
	else if (size > temp -> len){
	printf("trying to use %d bytes,but pointer %p has only %d\n",(int)size,ptr,(int)temp -> len);
	}
}
