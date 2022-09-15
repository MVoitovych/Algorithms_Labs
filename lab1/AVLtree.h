#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data, height;
    struct TreeNode *left_child, *right_child;


} TreeNode;

TreeNode *createNode(int data) {
    TreeNode *new_node = (TreeNode *) (malloc(sizeof(TreeNode)));
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->data = data;
    new_node->height = 1;
    return new_node;
}

//TreeNode *createRoot(int value) {
//    TreeNode *root = createNode(value);
//    return root;
//}

int getHeight(TreeNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int getMax(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(TreeNode *node) {
    if (node == NULL) return 0;
    return getHeight(node->left_child) - getHeight(node->right_child);
}

TreeNode *rightRotate(TreeNode *y) {
    TreeNode *x = y->left_child;
    TreeNode *x_right_child = x->right_child;

    x->right_child = y;
    y->left_child = x_right_child;

    x->height = getMax(getHeight(x->right_child), getHeight(x->left_child)) + 1;
    y->height = getMax(getHeight(y->left_child), getHeight(y->right_child)) + 1;

    return x;
}

TreeNode *leftRotate(TreeNode *x) {

    TreeNode *y = x->right_child;
    TreeNode *y_left_child = y->left_child;

    y->left_child = x;
    x->right_child = y_left_child;

    x->height = getMax(getHeight(x->right_child), getHeight(x->left_child)) + 1;
    y->height = getMax(getHeight(y->right_child), getHeight(y->right_child)) + 1;

    return y;
}


TreeNode *insert(TreeNode *current_node, int data) {

    if (current_node == NULL) {
        return createNode(data);
    }

    if (current_node->data > data) {
        current_node->left_child = insert(current_node->left_child, data);

    } else if (current_node->data < data) {
        current_node->right_child = insert(current_node->right_child, data);

    } else return current_node;

    current_node->height = 1 + getMax(getHeight(current_node->left_child), getHeight(current_node->right_child));

    int balance = getBalance(current_node);

    if (balance > 1 && current_node->left_child->data > data) {
        return rightRotate(current_node);
    }
    if (balance > 1 && current_node->left_child->data < data) {
        current_node->left_child = leftRotate(current_node->left_child);
        return rightRotate(current_node);
    }

    if (balance < -1 && current_node->right_child->data < data) {
        return leftRotate(current_node);
    }
    if (balance < -1 && current_node->right_child->data > data) {
        current_node->right_child = rightRotate(current_node->right_child);
        return leftRotate(current_node);
    }

    return current_node;

}

void add(int value, TreeNode **root) {
    (*root) = insert(*root, value);
}


void recursivePrintTree(TreeNode *current_node) {

    if (current_node == NULL) return;

    int balance = getBalance(current_node);

    recursivePrintTree(current_node->left_child);
    printf("(%d (balance %d))\n", current_node->data, balance);
    recursivePrintTree(current_node->right_child);

}


void printTree(TreeNode *root) {
    recursivePrintTree(root);
}

void run() {
    char input_sign;
    int value;
    TreeNode *root = NULL;

    while (1) {
        scanf("%d", &value);
        add(value, &root);
        printTree(root);
        if (value == -404 ) return;
    }

}