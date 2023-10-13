#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Tree_Node* create_node (char data){
    Tree_Node *newNode = (Tree_Node*)malloc(sizeof(Tree_Node));
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}


void tree_insert(Tree_Node** root, char data){

    if(*root == NULL) {
        *root = create_node(data);
        return;

    }
    else if( data <= (*root)->data){
        tree_insert(&(*root)->left, data);
    }else{
        tree_insert(&(*root)->right, data);
    }
}

Tree_Node* create_bst (char data[]){
        struct Tree_Node* root = NULL;

        int i = 0;
        while(data[i] != '\0'){
            tree_insert(&root, data[i]);
            i++;
        }

        return root;
}

Tree_Node* tree_search(Tree_Node* root, char data){
    if(root == NULL) return NULL;
    else if(root->data == data) return root;
    else if(data < root->data) return tree_search(root->left, data);
    else return tree_search(root->right, data);
}

void tree_print_sorted(Tree_Node* root){
    if(root == NULL) {return;}

    tree_print_sorted(root->left);   
    tree_print_sorted(root->right);

    printf("%c", root->data);
}

void tree_delete(Tree_Node* root){
    if(root == NULL){return;}

    tree_delete(root->left);
    tree_delete(root->right);

    free(root);
}
