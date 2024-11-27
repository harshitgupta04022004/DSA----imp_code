#include<stdio.h>
#include<stdlib.h>


// A splay tree is a self-balancing binary search tree, designed for efficient access to data elements based on their key values.

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct node *));
    node->key = key;
    node->left = node->right =NULL;
    return node;
}

struct Node* rightRotate(struct Node* x) {
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

struct Node* splay(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == NULL)
            return root;
        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else {
        if (root->right == NULL)
            return root;
        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (root->key == key)
        return root;

    struct Node* node = newNode(key);
    if (root->key > key) {
        node->right = root;
        node->left = root->left;
        root->left = NULL;
    }
    else {
        node->left = root;
        node->right = root->right;
        root->right = NULL;
    }
    return node;
}

void preOrder(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->key);
        preOrder(node->left);
        preOrder(node->right);
    }
}

int main() {
    struct Node* root = NULL;
    root = insert(root, 100);
    root = insert(root, 50);
    root = insert(root, 200);
    root = insert(root, 40);
    root = insert(root, 60);
    printf( "Preorder traversal of the modified Splay tree:");
    preOrder(root);
    return 0;
}
