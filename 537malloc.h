////////////////////////////////////////////////////////////////////////////////
// Main File:        
// This File:        537malloc.h
// Other Files:      
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
/////////////////////////////////////////////////////////////////////////////////
//maolloc537 is a safe malloc function
void * malloc537(size_t size);

//free537 is a safe free function
void free537(void *ptr);

//similar to realloc, but checking on the pointer
void *realloc537(void *ptr, size_t size);

//check pointer with address and the range
void memcheck537(void *ptr,size_t size);
