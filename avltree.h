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

#include <sys/types.h>

// Structure for AVL tree node
typedef struct Node
{
	// Address of the pointer and its range
	void *addr;
	size_t len;
	
	// Left and right children of the node
	struct Node *left;
	struct Node *right;
	
	// Use 1 to indicate allocated memory, use 0 to indicate freed memory
	int flag;
	
	// Height of the node in AVL tree
	int height;
} Node;

/*
 * create_node - create an AVL tree node and initialize the node.
 */
Node* create_node(void *address, size_t length);

/*
 * get_height - return the height of the node in AVL tree.
 */
int get_height(Node *node);

/*
 * insert_node - return the height of the node in AVL tree.
 */
Node* insert_node(Node* node, void *address, size_t length);

/*
 * balance_factor - calculate the balance factor of a node.
 */
int balance_factor(Node* node);

/*
 * left_rotate - do left rotation at a node.
 */
Node* left_rotate(Node* node);

/*
 * right_rotate - do right rotation at a node.
 */
Node* right_rotate(Node* node);

/*
 * delete_node - delete a node from AVL tree.
 */
Node* delete_node(Node *node, void *address);

/*
 * in_order_predecessor - find in-order predecessor of a node from AVL tree.
 */
Node* in_order_predecessor(Node *node);

/*
 * search_node - search for a node matching the given address
 */
Node* search_node(Node *node, void *address);
