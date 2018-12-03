
////////////////////////////////////////////////////////////////////////////////
// Main File:        
// This File:        avltree.c
// Other Files:      
// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24
////////////////////////////////////////////////////////////////////////////////

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

extern Node* create_node(void *address, size_t length);
extern int get_height(Node *node);
extern Node* insert_node(Node* node, void *address, size_t length);
extern int balance_factor(Node* node);
extern Node* left_rotate(Node* node);
extern Node* right_rotate(Node* node);
extern Node* delete_node(Node *node, void *address);
extern Node* in_order_predecessor(Node *node);
extern Node* search_node(Node *node, void *address);
extern int search_range(Node *node, void *address);

/*
 * create_node - create an AVL tree node and initialize the node.
 */
Node *create_node(void *address, size_t length) {
	Node *node = (Node*) malloc(sizeof(Node));
	node -> addr = address;
	node -> len = length;
	node -> left = NULL;
	node -> right = NULL;
	// Use 1 to indicate allocated memory
	node -> flag = 1;
	node -> height = 1;
	return node;
}

/*
 * get_height - return the height of the node in AVL tree.
 */
int get_height(Node *node) { 
    // If the node is null, return 0, otherwise, return height of node
	if (node == NULL) {
		return 0;
	}
	return node -> height;
}

/*
 * insert_node - insert a node into AVL tree.
 */
Node* insert_node(Node* node, void *address, size_t length) {
	// If the node is empty, create a new node
	if (node == NULL) {
		return create_node(address, length);
	}

	// If address is smaller than current node address, insert in left subtree, otherwise,
	// insert in right subtree
	if (address < node -> addr) {
		node -> left = insert_node(node -> left, address, length);
	} else if (address > node -> addr) {
		node -> right = insert_node(node -> right, address, length);
	} else {
		// If address is the same as the node address already in the tree, insertion is not allowed
		return node;
	}

	// Update height of node
	if (get_height(node -> left) > get_height(node -> right)) {
		node -> height = get_height(node -> left) + 1;
	} else {
		node -> height = get_height(node -> right) + 1;
	}

	// Find balance factor of current node to change structure of tree
	int BF = balance_factor(node);
		
	// Do left rotation
	if (BF < -1 && address > node -> right -> addr) {
		return left_rotate(node);
	}
		
	// Do right rotation
	if (BF > 1 && address < node -> left -> addr) {
		return right_rotate(node);
	}
		
	// Do right-left rotation
	if (BF < -1 && address < node -> right -> addr) {
		node -> right = right_rotate(node -> right);
		return left_rotate(node);
	}
		
	// Do left-right rotation
	if (BF > 1 && address > node -> left -> addr) {
		node -> left = left_rotate(node -> left);
		return right_rotate(node);
	}
	
	// If no rotation is needed, return the node
	return node;
}

/*
 * balance_factor - calculate the balance factor of a node.
 */
int balance_factor(Node* node) {
	// If node is null, balance factor is 0
	if (node == NULL) {
		return 0;
	}
	
	// Otherwise, balance factor is height of left subtree minus height of right subtree
	return get_height(node -> left) - get_height(node -> right);
}

/*
 * left_rotate - do left rotation at a node.
 */
Node* left_rotate(Node* node) {
	// Create grandparent node and parent node
	Node *G = node;
	Node *P = G -> right;
	G -> right = P -> left;
	P -> left = G;
	
	// Update height of G
	if (get_height(G -> left) > get_height(G -> right)) {
		G -> height = get_height(G -> left) + 1;
	} else {
		G -> height = get_height(G -> right) + 1;
	}
	
	// Update height of P
	if (get_height(P -> left) > get_height(P -> right)) {
		P -> height = get_height(P -> left) + 1;
	} else {
		P -> height = get_height(P -> right) + 1;
	}
	
	return P;
}

/*
 * right_rotate - do right rotation at a node.
 */
Node* right_rotate(Node* node) {
	// Create grandparent node and parent node
	Node *G = node;
	Node *P = G -> left;
	G -> left = P -> right;
	P -> right = G;
	
	// Update height of G
	if (get_height(G -> left) > get_height(G -> right)) {
		G -> height = get_height(G -> left) + 1;
	} else {
		G -> height = get_height(G -> right) + 1;
	}
	
	// Update height of P
	if (get_height(P -> left) > get_height(P -> right)) {
		P -> height = get_height(P -> left) + 1;
	} else {
		P -> height = get_height(P -> right) + 1;
	}
	
	return P;
}

/*
 * delete_node - delete a node from AVL tree.
 */
Node* delete_node(Node *node, void *address) {
	// If the tree is empty or the node can't be found, delete nothing
	if (node == NULL) {
		return node;
	}
	
	// If address is smaller than current node address, delete from left subtree, otherwise,
	// delete from right subtree
	if (address < node -> addr) {
		node -> left = delete_node(node -> left, address);
	} else if (address > node -> addr) {
		node -> right = delete_node(node -> right, address);
	} else {
		// When address matches current node address, do deletion in the following cases
		// Case 1: when node has no children
		if (node -> left == NULL && node -> right == NULL) {
			// Unlink the node by returning null to its parent
			return NULL;
		}
		
		// Case 2: when node has one child
		// Current node's child becomes current node
		if (node -> left == NULL) {
			return node -> right;
		}
		if (node -> right == NULL) {
			return node -> left;
		}
		
		// Case 3: when node has two children
		// Find largest value in left subtree (in-order predecessor) to be replacement value
		Node *replacement = in_order_predecessor(node);
		// Copy replacement value into current node
		node -> addr = replacement -> addr;
		node -> len = replacement -> len;
		node -> left = replacement -> left;
		node -> right = replacement -> right;
		node -> flag = replacement -> flag;
		node -> height = replacement -> height;
		// Recursively delete replacement node from left subtree
		node -> left = delete_node(node -> left, replacement -> addr);
	}
	
	// Update height of node
	if (get_height(node -> left) > get_height(node -> right)) {
		node -> height = get_height(node -> left) + 1;
	} else {
		node -> height = get_height(node -> right) + 1;
	}

	// Find balance factor of current node to change structure of tree
	int BF = balance_factor(node);

	// Do left rotation
	if (BF < -1 && balance_factor(node -> right) <= 0) {
		return left_rotate(node);
	}
	
	// Do right rotation
	if (BF > 1 && balance_factor(node -> left) >= 0) {
		return right_rotate(node);
	}
	
	// Do right-left rotation
	if (BF < -1 && balance_factor(node -> right) > 0) {
		node -> right = right_rotate(node -> right);
		return left_rotate(node);
	}
	
	// Do left-right rotation
	if (BF > 1 && balance_factor(node -> left) < 0) {
		node -> left = left_rotate(node -> left);
		return right_rotate(node);
	}
	
	// If no rotation is needed, return the node
	return node;
}

/*
 * in_order_predecessor - find in-order predecessor of a node from AVL tree.
 */
Node* in_order_predecessor(Node *node) {
	// Set starting node of left subtree to be the left node of input node 
	// (which is known to have two children)
	node = node -> left;
	
	// Keep updating current node to be right node if the right node is not null
	while (node -> right != NULL) {
		node = node -> right;
	}
	return node;
}

/*
 * search_node - search for a node matching the given address
 */
Node* search_node(Node *node, void *address) {
	// Traverse the tree to search
	while (node != NULL) {
		// If address is smaller than current node address, search in left subtree
		if (address < node -> addr) {
			node = node -> left;
		}
		// If address is larger than current node address, search in left subtree
		else if (address > node -> addr) {
			node = node -> right;
		}
		// If a matching address is found, return the node
		else {
			return node;
		}
	}
	
	// If reaches null, the node can't be found, return null
	return NULL;
}

/*
 * search_range - search for an address that matches the range in any node
 */
int search_range(Node *node, void *address) {
	// Traverse the tree to search
	while (node != NULL) {
		// If address is smaller than current node address+length, search in left subtree
		if (address < node -> addr && address < (node -> addr + node -> len)) {
			node = node -> left;
		}
		// If address is larger than current node address+length, search in left subtree
		else if (address > node -> addr && address > (node -> addr + node -> len)) {
			node = node -> right;
		}
		// If a matching address is found within the range, return 1
		else {
			return 1;
		}
	}
	
	// If reaches null, the node can't be found, return 0
	return 0;
}
