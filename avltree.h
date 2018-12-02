////////////////////////////////////////////////////////////////////////////////
// Main File:        
// This File:        avltree.h
// Other Files:      
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////
/*
 



 */

#include <sys/types.h>
//define the node of avltree
typedef struct node
{
	struct node * left;
	struct node * right;
	void * add;
	size_t len;
	int flag;
	int height;
}node;

//create the node in the tree
node * create_node(void *add, size_t len);

//insert the node 
node *  insert_node(struct node * input);

//delete the node
node * delete_node(struct node * input);

// search address
struct node * search(struct node * input);




