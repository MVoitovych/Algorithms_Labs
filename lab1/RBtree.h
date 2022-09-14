#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum COLOR {
    RED, BLACK
};


typedef struct TreeNode {
    int data;
    struct TreeNode *left_child, *right_child, *parent;
    enum COLOR color;

} TreeNode;

TreeNode *createNode(int data) {
    TreeNode *new_node = (TreeNode *) (malloc(sizeof(TreeNode)));
    new_node->left_child = NULL;
    new_node->right_child = NULL;
    new_node->parent = NULL;
    new_node->color = RED;
    new_node->data = data;
    return new_node;
}

TreeNode *createRoot(int value) {
    TreeNode *root = createNode(value);
    root->color = BLACK;
    return root;
}

bool isLeft(TreeNode *node) {
    return (node->parent->left_child == node && node->parent != NULL);
}

void colorSwap(enum COLOR *a, enum COLOR *b) {
    enum COLOR temp = *a;
    *a = *b;
    *b = temp;
}

void dataSwap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void rightRotate(TreeNode *node) {
    if (node == NULL) return;
    TreeNode *left = node->left_child;
    if (left == NULL) return;
    TreeNode *left_right_child = left->right_child;
    left->right_child = node;
    left->parent = node->parent;
    node->parent = left;
    node->left_child = left_right_child;
    if (left_right_child != NULL) {
        left_right_child->parent = node;
    }
    if (left->parent != NULL) {
        if (left->data < left->parent->data) {
            left->parent->left_child = left;
        } else {
            left->parent->right_child = left;
        }
    }
}

void leftRotate(TreeNode *current_node) {
    if (current_node == NULL) return;
    TreeNode *right = current_node->right_child;
    if (right == NULL) return;
    TreeNode *right_left_child = right->left_child;
    right->left_child = current_node;
    right->parent = current_node->parent;
    current_node->parent = right;
    current_node->right_child = right_left_child;
    if (right_left_child != NULL) {
        right_left_child->parent = current_node;
    }
    if (right->parent != NULL) {
        if (right->data < right->parent->data) {
            right->parent->left_child = right;
        } else {
            right->parent->right_child = right;
        }
    }
}

bool isRed(TreeNode *current_node) {
    return (current_node != NULL && current_node->color == RED);
}

void fixRedChildRedParent(TreeNode *current_node) {
    if (current_node->parent == NULL) {
        current_node->color = BLACK;
        return;
    }
    TreeNode *parent = current_node->parent;
    TreeNode *grandparent = parent->parent;
    TreeNode *uncle = (grandparent == NULL ? NULL : (isLeft(parent) ? grandparent->right_child
                                                                    : grandparent->left_child));
    if (isRed(parent)) {
        if (isRed(uncle)) {
            parent->color = BLACK;
            uncle->color = BLACK;
            if (grandparent != NULL) {
                grandparent->color = RED;
                fixRedChildRedParent(grandparent);
            }

        } else {
            if (isLeft(parent)) {
                if (!isLeft(current_node)) {
                    leftRotate(parent);
                    colorSwap(&current_node->color, &grandparent->color);
                } else {
                    colorSwap(&parent->color, &grandparent->color);
                }


                rightRotate(grandparent);
            } else {
                if (isLeft(current_node)) {
                    rightRotate(parent);
                    colorSwap(&current_node->color, &grandparent->color);
                } else {
                    colorSwap(&parent->color, &grandparent->color);
                }

                leftRotate(grandparent);
            }
        }
    }
}

void fixDelete(TreeNode *node, TreeNode **p_root) {
    if (node == *p_root) {
        return;
    }
    TreeNode *parent = node->parent;
    TreeNode *sibling = (isLeft(node) ? parent->right_child : parent->left_child);

    if (isRed(sibling)) {
        colorSwap(&sibling->color, &parent->color);
        if (isLeft(sibling)) {
            rightRotate(sibling);
        } else {
            leftRotate(sibling);
        }

        fixDelete(node, p_root);

    } else {
        if (sibling == NULL || (!isRed(sibling->left_child) && !isRed(sibling->right_child))) {
            if (sibling != NULL) {
                sibling->color = RED;
                if (parent->color == BLACK) {
                    fixDelete(node->parent, p_root);
                } else {
                    node->parent->color = BLACK;
                }
            }
        } else {

            if (isLeft(sibling)) {
                if (isRed(sibling->left_child)) {
                    sibling->left_child->color = sibling->color;
                    sibling->color = parent->color;
                    rightRotate(parent);

                } else {
                    sibling->right_child->color = parent->color;
                    leftRotate(sibling);
                    rightRotate(parent);
                }

            } else {
                if (isRed(sibling->right_child)) {
                    sibling->right_child->color = sibling->color;
                    sibling->color = parent->color;
                    leftRotate(parent);

                } else {
                    sibling->left_child->color = parent->color;
                    rightRotate(sibling);
                    leftRotate(parent);
                }
            }
            parent->color = BLACK;
        }
    }
}

TreeNode *findByValue(int value, TreeNode **p_root) {
    TreeNode *node = *p_root;
    while (node != NULL) {
        if (node->data == value) {
            break;
        }
        if (node->data > value) {
            node = node->left_child;
        } else {
            node = node->right_child;
        }
    }
    return node;
}

TreeNode *findReplacement(TreeNode *current_node) {
    if (current_node == NULL) return NULL;
    if (current_node->left_child == NULL && current_node->right_child == NULL) return NULL;
    if (current_node->left_child != NULL && current_node->right_child != NULL) {
        TreeNode *temp = current_node->right_child;
        while (temp->left_child != NULL) {
            temp = temp->left_child;
        }
        return temp;
    }
    if (current_node->left_child != NULL) return current_node->left_child;
    else return current_node->right_child;
}

void removeNode(TreeNode *current_node, TreeNode **p_root) {
    if (current_node == NULL) return;

    TreeNode *u = findReplacement(current_node);

    bool both_are_black = (!isRed(current_node) && !isRed(u));

    if (u == NULL) {
        if (current_node == (*p_root)) {
            (*p_root) = NULL;
        } else {
            if (both_are_black) {
                fixDelete(current_node, p_root);
            } else {
                TreeNode *sibling = (isLeft(current_node) ? current_node->parent->right_child
                                                          : current_node->parent->left_child);
                if (sibling != NULL) {
                    sibling->color = RED;
                }
            }
            if (isLeft(current_node)) {
                current_node->parent->left_child = NULL;
            } else {
                current_node->parent->right_child = NULL;
            }
        }
        free(current_node);
        return;
    }

    if (current_node->left_child == NULL || current_node->right_child == NULL) {
        if (current_node == (*p_root)) {
            current_node->data = u->data;
            current_node->left_child = current_node->right_child = NULL;
            free(u);
        } else {
            if (isLeft(current_node)) {
                current_node->parent->left_child = u;
            } else {
                current_node->parent->right_child = u;
            }
            u->parent = current_node->parent;
            free(current_node);
            if (both_are_black) {
                fixDelete(u, p_root);
            } else {
                u->color = BLACK;
            }
        }
        return;
    }

    dataSwap(&current_node->data, &u->data);
    removeNode(u, p_root);
}

void recursivePrintTree(TreeNode *current_node) {

    if (current_node == NULL) return;

    char *colour = current_node->color == RED ? "RED" : "BLACK";;
    int parent = current_node->parent == NULL ? current_node->data : current_node->parent->data;;
    recursivePrintTree(current_node->left_child);
    printf("(%d(%s)(my parent %d))\n", current_node->data, colour, parent);
    recursivePrintTree(current_node->right_child);


}

bool isContains(int value, TreeNode **root) {
    return (findByValue(value, root) != NULL);
}

void printTree(TreeNode *root) {
    recursivePrintTree(root);
}

void add(int value, TreeNode **root) {
    if (isContains(value, root)) return;
    TreeNode *new_node = createNode(value);
    if (*root == NULL) {
        *root = new_node;
        (*root)->color = BLACK;
    } else {
        TreeNode *parent = *root;
        while (new_node->parent == NULL) {
            if (parent->data < value) {
                if (parent->right_child == NULL) {
                    parent->right_child = new_node;
                    new_node->parent = parent;
                    break;
                } else {
                    parent = parent->right_child;
                }
            } else {
                if (parent->left_child == NULL) {
                    parent->left_child = new_node;
                    new_node->parent = parent;
                    break;
                } else {
                    parent = parent->left_child;
                }
            }
        }
        fixRedChildRedParent(new_node);
        while ((*root)->parent != NULL) {
            *root = (*root)->parent;
        }
    }
}

void delete(int value, TreeNode **p_root) {
    if ((*p_root) == NULL) return;

    if (!isContains(value, p_root)) return;
    TreeNode *v = findByValue(value, p_root);
    removeNode(v, p_root);

}


void run() {
    char input_sign;
    int number = 0;
    scanf("%d%c", &number);
    printf("root created\n");
    TreeNode *root = createRoot(number);
    printTree(root);


    while (true) {
        scanf("%c %d%c", &input_sign, &number);
        printf("===================================\n");

        if (input_sign == '+') {
            add(number, &root);


        } else if (input_sign == '-') {
            delete(number, &root);

        } else if(input_sign == 'x'){
            return;
        }

        printTree(root);

    }
}
