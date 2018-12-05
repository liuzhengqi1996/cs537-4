////////////////////////////////////////////////////////////////////////////////
// Main File:        537malloc.c
// This File:        537malloc.c
// Other Files:      537malloc.h, range_tree.c, range_tree.h
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "537malloc.h"
#include "range_tree.h"

extern void * malloc537(size_t size);
extern void free537(void *ptr);
extern void *realloc537(void *ptr, size_t size);
extern void memcheck537(void *ptr, size_t size);
static Node *root;

/*
 * malloc537 - allocate memory by calling malloc, store a tuple of address and length in AVL Tree
 */
void *malloc537(size_t size) {
	// Check the size parameter for zero length
	if(size == 0){
		printf("malloc537: Need to malloc a size 0 pointer.\n");
	}
	
	// Allocate memory by calling malloc
	void *return_ptr = malloc(size);

	// Delete all the nodes within the range of newly allocated memory in AVL tree
	for (size_t i = 0; i < size; i++) {
		root = delete_node(root, return_ptr + i);
	}
	
	// Insert the new node into AVL tree
	root = insert_node(root, return_ptr, size);
	return return_ptr;
}

/*
 * free537 - safely free the memory specified by a pointer, report error conditions
 */
void free537(void *ptr) {
	
	// Search if the pointer is within any range in the tree
	Node *temp1 = search_range(root, ptr);
	// Search if the pointer is any start address in the tree
	Node *temp2 = search_node(root, ptr);
	
	// If the pointer cannot be found in tree or any range within the tree, 
	// it has not be allocated previously, report error
	if (temp1 == NULL && temp2 == NULL) {
		printf("free537: Freeing memory has not been allocated by malloc537.\n");	
		exit(-1);	
	}
	// If the pointer can be found within the range, but not as the start address, report error
	else if (temp1 != NULL && temp2 == NULL) {
		printf("free537: Freeing memory that is not the first byte of the range of memory that was allocated.\n");
		exit(-1);
	}
	// If the pointer is already been freed, report error
	else if (temp2 -> flag == 0){
		printf("free537: Freeing memory that was previously freed (double free).\n");
		exit(-1);		
	}
	
	//If no error conditions are encounterd, change the flag to 0, free the pointer
	temp2 -> flag = 0;
	free(ptr);	
}

/*
 * realloc537 - allocate memory for a pointer, store a tuple of address and length in AVL Tree
 */
void *realloc537(void *ptr, size_t size) {
	// If the pointer is NULL, follow the specification of malloc537()
	if (ptr == NULL) {
		return malloc537(size);
	}
	// If size is zero and ptr is not NULL, follow the specification of free537()
	else if (size == 0) {
		printf("realloc537: Need to realloc a size 0 pointer.\n");
		free537(ptr);
		return NULL;
	}
	//general case
	else{
		// Search for the pointer in AVL tree
		Node *temp = search_node(root, ptr);
		
		// If the pointer has been previously allocated, delete the pointer
		if (temp != NULL) {
			root = delete_node(root, temp);
		}
		
		//Call realloc for the pointer
		void *return_ptr = realloc(ptr, size);
		
		// Insert the new node into AVL tree
		root = insert_node(root, return_ptr, size);
		return return_ptr;	
	}
}

/*
 * memcheck537 - check if the address range specified by address ptr and length size
 * are fully within a range allocated by malloc537() and memory not yet freed by free537()
 */
void memcheck537(void *ptr, size_t size) {
	// Search if the pointer is within any range in the tree
	Node *temp1 = search_range(root, ptr);
	// Search if the pointer is any start address in the tree
	Node *temp2 = search_node(root, ptr);
	
	// If the pointer cannot be found in tree or any range within the tree, 
	// it has not be allocated previously, report error
	if (temp1 == NULL && temp2 == NULL) {
		printf("memcheck537: The pointer has not been allocated.\n");
		exit(-1);	
	}
	// If the pointer can be found within the range, check its range, 
	// report error if the size exceeds the range
	else if (temp1 != NULL && temp2 == NULL) {
		if ((temp1 -> addr + temp1 -> len) < (ptr + size)) {
			printf("memcheck537: The pointer %p is within the range of pointer %p, but its size exceeds the allocated memory.\n", ptr, temp1);
			exit(-1);
		}
	}
	// If the pointer is already been freed, report error
	else if (temp2 -> flag == 0){
		printf("memcheck537: The pointer has already been freed.\n");
		exit(-1);
	}
	// If the size of pointer is out of the range
	else if (temp2 -> len < size) {
		printf("memcheck537: The pointer %p has allocated memory of %d bytes when %d bytes are needed.\n", ptr, (int) temp2 -> len, (int) size);
		exit(-1);
	}
}
