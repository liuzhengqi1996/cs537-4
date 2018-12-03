// Semester:         CS 537 Fall 2018
// Lecture:          Lec 001
// Authors:          Zhengqi Liu, Tian Zheng
// CS Login:         zhengqi, tian
// NetID:            mliu292, tzheng24

This program writes a special version of the malloc and free library that checks on common heap and usage mistake.
The information of pointer is in Node. Each node has the contain the address and length
Our Library is contained by two parts. Avltree is a structure of nodes.We can search the address, insert node, remove node by AVL tree, We can search the address, insert node, remove node by AVL tree,

The second part is the specific methods.
 Malloc537 is a safe malloc method, it can add the node into the tree and handle the case that malloc the freed memory.
Free537 is a safe free method , it can turn off the flag in the tree, check the double-free pointer and bad range.
Realloc537 is similar to realloc, it first search the pointer in the tree, delete the node and re-insert the new pointer.
Memcheck537 is used to check the memory range. It will search the pointer address and check if the range is valid.

