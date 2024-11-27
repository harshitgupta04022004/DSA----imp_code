#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node
{
    int data;
    int col; // Red = 1, Black = 0
    struct node *left;
    struct node *right;
    struct node *parent;
};

// Global NIL node
struct node *nil = NULL;

// Function to initialize NIL node
void initialize_nil()
{
    nil = (struct node *)malloc(sizeof(struct node));
    nil->col = 0; // Black
    nil->left = NULL;
    nil->right = NULL;
    nil->parent = NULL;
    nil->data = 0;
}

// In-order traversal
void Inorder_tree_walk(struct node *root)
{
    if (root != nil)
    {
        Inorder_tree_walk(root->left);
        printf("%d (%d) ", root->data, root->col);
        Inorder_tree_walk(root->right);
    }
}

// Pre-order traversal
void Pre_order(struct node *root)
{
    if (root != nil)
    {
        printf("%d ", root->data);
        Pre_order(root->left);
        Pre_order(root->right);
    }
}

// Post-order traversal
void Post_order(struct node *root)
{
    if (root != nil)
    {
        Post_order(root->left);
        Post_order(root->right);
        printf("%d ", root->data);
    }
}

// Search for a node
struct node *Tree_search(struct node *root, int k)
{
    if (root == nil || k == root->data)
    {
        return root;
    }
    if (k < root->data)
    {
        return Tree_search(root->left, k);
    }
    else
    {
        return Tree_search(root->right, k);
    }
}

// Minimum node
struct node *Tree_minimum(struct node *root)
{
    while (root->left != nil)
    {
        root = root->left;
    }
    return root;
}

// Maximum node
struct node *Tree_maximum(struct node *root)
{
    while (root->right != nil)
    {
        root = root->right;
    }
    return root;
}

// Transplant nodes
void Transplant(struct node **root, struct node *u, struct node *v)
{
    if (u->parent == nil)
    {
        *root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v != nil)
    {
        v->parent = u->parent;
    }
}

// Left rotation
void Left_rotation(struct node **root, struct node *x)
{
    struct node *y = x->right;
    x->right = y->left;
    if (y->left != nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil)
    {
        *root = y;
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
void Right_rotation(struct node **root, struct node *y)
{
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != nil)
    {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == nil)
    {
        *root = x;
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

// Insert fixup
void RB_insert_fixup(struct node **root, struct node *z)
{
    while (z->parent->col == 1)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct node *y = z->parent->parent->right;
            if (y->col == 1)
            {
                z->parent->col = 0;
                y->col = 0;
                z->parent->parent->col = 1;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    Left_rotation(root, z);
                }
                z->parent->col = 0;
                z->parent->parent->col = 1;
                Right_rotation(root, z->parent->parent);
            }
        }
        else
        {
            struct node *y = z->parent->parent->left;
            if (y->col == 1)
            {
                z->parent->col = 0;
                y->col = 0;
                z->parent->parent->col = 1;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    Right_rotation(root, z);
                }
                z->parent->col = 0;
                z->parent->parent->col = 1;
                Left_rotation(root, z->parent->parent);
            }
        }
    }
    (*root)->col = 0;
}

// Insert node
void RB_insert(struct node **root, int val)
{
    struct node *y = nil;
    struct node *x = *root;
    struct node *z = (struct node *)malloc(sizeof(struct node));
    z->data = val;
    z->left = nil;
    z->right = nil;
    z->col = 1;

    while (x != nil)
    {
        y = x;
        if (z->data < x->data)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil)
    {
        *root = z;
    }
    else if (z->data < y->data)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    RB_insert_fixup(root, z);
}

// Delete node fixup
void RB_delete_fixup(struct node **root, struct node *x)
{
    while (x != *root && x->col == 0)
    {
        if (x == x->parent->left)
        {
            struct node *w = x->parent->right;
            if (w->col == 1)
            {
                w->col = 0;
                x->parent->col = 1;
                Left_rotation(root, x->parent);
                w = x->parent->right;
            }
            if (w->left->col == 0 && w->right->col == 0)
            {
                w->col = 1;
                x = x->parent;
            }
            else
            {
                if (w->right->col == 0)
                {
                    w->left->col = 0;
                    w->col = 1;
                    Right_rotation(root, w);
                    w = x->parent->right;
                }
                w->col = x->parent->col;
                x->parent->col = 0;
                w->right->col = 0;
                Left_rotation(root, x->parent);
                x = *root;
            }
        }
        else
        {
            struct node *w = x->parent->left;
            if (w->col == 1)
            {
                w->col = 0;
                x->parent->col = 1;
                Right_rotation(root, x->parent);
                w = x->parent->left;
            }
            if (w->right->col == 0 && w->left->col == 0)
            {
                w->col = 1;
                x = x->parent;
            }
            else
            {
                if (w->left->col == 0)
                {
                    w->right->col = 0;
                    w->col = 1;
                    Left_rotation(root, w);
                    w = x->parent->left;
                }
                w->col = x->parent->col;
                x->parent->col = 0;
                w->left->col = 0;
                Right_rotation(root, x->parent);
                x = *root;
            }
        }
    }
    x->col = 0;
}

// Delete node
void RB_delete(struct node **root, int val)
{
    struct node *z = Tree_search(*root, val);
    if (z == nil)
        return;

    struct node *y = z;
    struct node *x;
    int y_ori_col = y->col;

    if (z->left == nil)
    {
        x = z->right;
        Transplant(root, z, z->right);
    }
    else if (z->right == nil)
    {
        x = z->left;
        Transplant(root, z, z->left);
    }
    else
    {
        y = Tree_minimum(z->right);
        y_ori_col = y->col;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            Transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        Transplant(root, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->col = z->col;
    }
    if (y_ori_col == 0)
    {
        RB_delete_fixup(root, x);
    }
    free(z);
}

int main()
{
    initialize_nil();
    struct node *root = nil;

    // Insert nodes into the Red-Black tree
    RB_insert(&root, 41);
    RB_insert(&root, 38);
    RB_insert(&root, 31);
    RB_insert(&root, 12);
    RB_insert(&root, 19);
    RB_insert(&root, 8);
    //    RB_insert(&root, 20);

    // Print traversals
    printf("Inorder traversal: ");
    Inorder_tree_walk(root);
    printf("\n");

    printf("Preorder traversal: ");
    Pre_order(root);
    printf("\n");

    printf("Postorder traversal: ");
    Post_order(root);
    printf("\n");

    // Search for a node
    struct node *found = Tree_search(root, 8);
    if (found != nil)
    {
        printf("Node %d found in the tree.\n", found->data);
    }
    else
    {
        printf("Node not found.\n");
    }

    // Delete a node
    RB_delete(&root, 6);
    printf("Inorder traversal after deletion: ");
    Inorder_tree_walk(root);
    printf("\n");

    free(nil);
    return 0;
}
