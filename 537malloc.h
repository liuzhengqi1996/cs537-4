////////////////////////////////////////////////////////////////////////////////
// Main File:        537malloc.c
// This File:        537malloc.h
// Other Files:      537malloc.c, range_tree.c, range_tree.h
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
/////////////////////////////////////////////////////////////////////////////////

/*
 * malloc537 - allocate memory by calling malloc, store a tuple of address and length in AVL Tree
 */
void *malloc537(size_t size);

/*
 * free537 - safely free the memory specified by a pointer, report error conditions
 */
void free537(void *ptr);

/*
 * realloc537 - allocate memory for a pointer, store a tuple of address and length in AVL Tree
 */
void *realloc537(void *ptr, size_t size);

/*
 * memcheck537 - check if the address range specified by address ptr and length size
 * are fully within a range allocated by malloc537() and memory not yet freed by free537()
 */
void memcheck537(void *ptr, size_t size);
