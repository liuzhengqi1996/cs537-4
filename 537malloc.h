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
//
void * malloc537(size_t size);

void free537(void *ptr);

void *realloc537(void *ptr, size_t size);

void memcheck537(void *ptr,size_t size);
