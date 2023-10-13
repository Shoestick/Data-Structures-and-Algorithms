#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bst.h"

Tree_Node *createnode(char data){
    Tree_Node* result = malloc(sizeof(Tree_Node));
    if(result != NULL){
        result->left = NULL;
        result->right = NULL;
        result->data = data;
    }
    return result;
}

bool insertnumber(Tree_Node **rootptr, char data){
    Tree_Node *root = *rootptr;

    if(root == NULL) {
        //tree empty
        (*rootptr) = createnode(data);
        return true;
    }
    if(data <= root->data){
        return insertnumber(&(root->left), data);
    } else {
        return insertnumber(&(root->right), data);
    }
}

void printtree(Tree_Node *root){
    if(root == NULL){
        printf("---<empt>---\n");
        return;
    }
    printf("value = %d\n", root->data);
    printf("left\n");
    printtree(root->left);
    printf("right\n");
    printtree(root->right);
    printf("done\n");
}

void tree_print_sorted(Tree_Node* root){
    if(root == NULL) {};

    tree_print_sorted(root->right);
    tree_print_sorted(root->left);

    printf("%c", root->data);
}

int main(){
    Tree_Node *root = NULL;

    char* word = "SBRLOD";

    insertnumber(&root, word[0]);
    insertnumber(&root, word[1]);
    insertnumber(&root, word[2]);
    insertnumber(&root, word[3]);
    insertnumber(&root, word[4]);
    insertnumber(&root, word[5]);

    //printtree(root);
    tree_print_sorted(root);

}
