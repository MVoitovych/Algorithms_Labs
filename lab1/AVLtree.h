#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data, height;
    struct TreeNode *left_child, *right_child, *parent;


} TreeNode;

TreeNode *createNode(int data) {
    TreeNode *new_node = (TreeNode *) (malloc(sizeof(TreeNode)));
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->parent = NULL;
    new_node->data = data;
    return new_node;
}

TreeNode *createRoot(int value) {
    TreeNode *root = createNode(value);
    return root;
}

int getHeight(TreeNode* node){
    if(node == NULL)
        return 0;
    return node->height;
}