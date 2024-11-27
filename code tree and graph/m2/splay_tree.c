// 1.	Write a C program for implementation of AVL tree creation. (1-10)
#include<stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* left;
    struct node* right;
    struct node* parent;
};


void Inorder_tree_walk(struct node * root)
{
    if (root!=NULL)
    {
        Inorder_tree_walk(root->left);
        printf("%d ",root->data);
        Inorder_tree_walk(root->right);
    }
}
void Pre_order(struct node * root)
{
    if (root!=NULL)
    {
        printf("%d ",root->data);
        Pre_order(root->left);
        Pre_order(root->right);
    }
}
void Post_order(struct node * root)
{
    if (root!=NULL)
    {
        Post_order(root->left);
        Post_order(root->right);
        printf("%d ",root->data);

    }
}

struct node * Tree_search(struct node *root, int k)
{
    if ((root == NULL) || (k==root->data))
    {
     return root;   
    }
    if (k<root->data)
    {
        return Tree_search(root->left,k);
    }
    else
    {
        return Tree_search(root->right,k);
    }
}

//  struct node * Iterative_tree_search(struct node* root, int k)
//  {
//     while (root!=NULL && k!=root->data)
//     {
//         if (k < root->data)
//         {
//           root = root->left;
//         }
//         else
//         {
//             root = root->right;
//         }
//     }
//     return root;
    
//  }


 struct node * Tree_minimum(struct node * root)
 {
    while (root->left != NULL)
    {
        root = root->left;
    }
    return root;
    
 }

struct node * Tree_maximum(struct node * root)
{
      while (root->right != NULL)
      {
        root = root->right;
      }
      return root;
      
}

struct node* Tree_successor(struct node* root)
{
    if (root->right != NULL)
    {
        return Tree_minimum(root->right);
    }
    struct node * tamp = root->parent;
    while (tamp != NULL && root == tamp->right)
    {
        root =tamp;
        tamp = tamp->parent;
    }
    return tamp;
}


struct node* Tree_Predecessor(struct node* root)
{
    if (root->left != NULL)
    {
        return Tree_maximum(root->left);
    }
    struct node * tamp = root->parent;
    while (tamp != NULL && root == tamp->left)
    {
        root =tamp;
        tamp = tamp->parent;
    }
    return tamp;
}

struct node* rightRotate(struct node* x) {
    struct node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct node* leftRotate(struct node* x) {
    struct node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

void Left_rotation(struct node *root, struct node *x)
{
    struct node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Right rotation
void Right_rotation(struct node *root, struct node *y)
{
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL)
    {
        root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
}


struct node* splay(struct node* root, int key) {
    if (root == NULL || root->data == key)
        return root;

    if (root->data > key) {
        if (root->left == NULL)
            return root;
        if (root->left->data > key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        else if (root->left->data < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }
        return (root->left == NULL) ? root : rightRotate(root);
    }
    else {
        if (root->right == NULL)
            return root;
        if (root->right->data > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        else if (root->right->data < key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }
        return (root->right == NULL) ? root : leftRotate(root);
    }
}


struct node* insert(struct node* root, int key) {
    if (root == NULL)
        return newNode(key);

    root = splay(root, key);

    if (root->data == key)
        return root;

    struct node* new_node = (struct node*)malloc(sizeof(struct node*));
    if (root->data > key) {
        new_node->right = root;
        new_node->left = root->left;
        new_node->left = NULL;
    }
    else {
        new_node->left = root;
        new_node->right = root->right;
        new_node->right = NULL;
    }
    return new_node;
}




void Tree_insert(struct node** root, int val)
{
    struct node * y = NULL;
    struct node * x = *root;
    struct node * z;
    z = (struct node*)malloc(sizeof(struct node));    
    z->data = val;
    z->left=NULL;
    z->right=NULL;
    while (x!=NULL)
    {
        y=x;
        if ((z->data) < (x->data))
        {
           x = x->left;
        } 
        else 
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y==NULL)
    {
        *root=z;
    }
    else if (z->data < y->data)
    {
        y->left = z;
    }
    else
    {
        y->right =z;
    }
    
}

void Transplant(struct node ** root, struct node* u, struct node * v)
{
    if (u->parent ==NULL)
    {
        *root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right =v;
    }
    if (v !=NULL)
    {
        v->parent = u->parent;
    }
}


void Tree_delete(struct node** root, int val)
{
    struct node* z = Tree_search(*root,val);
    if (z->left ==NULL)
    {
        Transplant(root,z,z->right);
    }
    else if(z->right == NULL)
    {
        Transplant(root, z, z->left);
    }
    else 
    {
        struct node* y = Tree_minimum(z->right);
        if (y->parent != z)
        {
            Transplant(root,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(root,z,y);
        y->left = z->left;
        y->left->parent = y;
    }
    free(z);
}


int main() {
    struct node* root = NULL;

    // Insert nodes into the binary tree
    Tree_insert(&root, 15);
    Tree_insert(&root, 6);
    Tree_insert(&root, 18);
    Tree_insert(&root, 3);
    Tree_insert(&root, 7);
    Tree_insert(&root, 17);
    Tree_insert(&root, 20);

    printf("Inorder traversal: ");
    Inorder_tree_walk(root);
    printf("\n");

    printf("Preorder traversal: ");
    Pre_order(root);
    printf("\n");

    printf("Postorder traversal: ");
    Post_order(root);
    printf("\n");

    // Test searching for a node
    struct node* found = Tree_search(root, 6);
    if (found) {
        printf("Node %d found in the tree.\n", found->data);
    } else {
        printf("Node not found.\n");
    }

    // Delete a node from the tree
    Tree_delete(&root, 6);
    printf("Inorder traversal after deletion: ");
    Inorder_tree_walk(root);
    printf("\n");

    return 0;
}







