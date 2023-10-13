#include "bstdb.h"

// Write your submission in this file
//
// A main function and some profiling tools have already been set up to test
// your code in the task2.c file. All you need to do is fill out this file
// with an appropriate Binary Search Tree implementation.
//
// The input data will be books. A book is comprised of a title and a word
// count. You should store both these values in the tree along with a unique
// integer ID which you will generate.
//
// We are aiming for speed here. A BST based database should be orders of
// magnitude faster than a linked list implementation if the BST is written
// correctly.
//
// We have provided an example implementation of what a linked list based
// solution to this problem might look like in the db/listdb.c file. If you
// are struggling to understand the problem or what one of the functions
// below ought to do, consider looking at that file to see if it helps your
// understanding.
//
// There are 6 functions you need to look at. Each is provided with a comment
// which explains how it should behave. The functions are:
//
//  + bstdb_init
//  + bstdb_add
//  + bstdb_get_word_count
//  + bstdb_get_name
//  + bstdb_stat
//  + bstdb_quit
//
// Do not rename these functions or change their arguments/return types.
// Otherwise the profiler will not be able to find them. If you think you
// need more functionality than what is provided by these 6 functions, you
// may write additional functions in this file.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct bst_node {
    int   doc_id;           // unique identifier for the document
    char *name;             // file name of the document    
    int   word_count;       // number of words in the document      
    struct bst_node *right; // pointer to the next node in the list
	struct bst_node *left; // pointer to the next node in the list
}bst_node;

bst_node* create_node (int doc_id, char *name, int word_count){
    bst_node *newNode = (bst_node*)malloc(sizeof(bst_node));
    newNode->doc_id = doc_id;
	newNode->name = name;
	newNode->word_count = word_count;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

struct bst_node* ancient_root = NULL;

int
bstdb_init ( void ) {
	// This function will run once (and only once) when the database first starts. 
	//struct bst_node* ancient_root = NULL;

	return 1;
}

int hash(char* s){
    int hash = 0;

    while(*s){
        hash = (31 * hash + *s + rand()) % 1586089; //Highest palindromic prime below 100,000
        s++;
    }
    return hash;
}

void tree_insert(bst_node** root, char *name, int word_count, int doc_id){

    if(*root == NULL) {
        *root = create_node(doc_id, name, word_count);
        return;
    }

    else if( doc_id <= (*root)->doc_id){
        tree_insert(&(*root)->left, name, word_count, doc_id);
    }else{
        tree_insert(&(*root)->right, name, word_count, doc_id);
    }
}

bool tree_search(bst_node* root, int doc_id){
	if(root == NULL) return NULL;
    else if(root->doc_id == doc_id) return doc_id;
    else if(doc_id < root->doc_id) return tree_search(root->left, doc_id);
    else return tree_search(root->right, doc_id);
}

int
bstdb_add ( char *name, int word_count ) {
	//Create new node, insert it, generate an id
	int id;
	if(ancient_root == NULL){
		ancient_root = create_node(1586089/2, name, word_count);
	}else {
		id = hash(name);
		while(tree_search(ancient_root, id)){
			id = hash(name);
		}
	}

	tree_insert(&ancient_root, name, word_count, id);

	return -1;
}

int tree_search_int(bst_node* root, int doc_id){
    if(root == NULL) return -1;
    else if(root->doc_id == doc_id) return root->word_count;
    else if(doc_id < root->doc_id) return tree_search_int(root->left, doc_id);
    else return tree_search_int(root->right, doc_id);
}

int
bstdb_get_word_count ( int doc_id ) {
	
	int words = tree_search_int(ancient_root, doc_id);
	if(words < 0){
		return words;
	}

	return -1;
}

char* tree_search_char(bst_node* root, int doc_id){
    if(root == NULL) return 0;
    else if(root->doc_id == doc_id) return root->name;
    else if(doc_id < root->doc_id) return tree_search_char(root->left, doc_id);
    else return tree_search_char(root->right, doc_id);
}

char*
bstdb_get_name ( int doc_id ) {

	char* title = tree_search_char(ancient_root, doc_id);
	if(title < 0){
		return title;
	}
	
	return 0;
}

void
bstdb_stat ( void ) {
	// Use this function to show off! It will be called once after the 
	// profiler ends. The profiler checks for execution time and simple errors,
	// but you should use this function to demonstrate your own innovation.
	//
	// Suggestions for things you might want to demonstrate are given below,
	// but in general what you choose to show here is up to you. This function
	// counts for marks so make sure it does something interesting or useful.
	//
	//  + Check if your tree is balanced and print the result
	//
	//  + Does the number of nodes in the tree match the number you expect
	//    based on the number of insertions you performed?
	//
	//  + How many nodes on average did you need to traverse in order to find
	//    a search result? 
	//
	//  + Can you prove that there are no accidental duplicate document IDs
	//    in the tree?
}

void tree_delete(bst_node* root){
    if(root == NULL){return;}

    tree_delete(root->left);
    tree_delete(root->right);

    free(root);
}

void
bstdb_quit ( void ) {
	// This function will run once (and only once) when the program ends
	tree_delete(ancient_root);
}
