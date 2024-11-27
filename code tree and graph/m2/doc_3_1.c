// 1.	Write a C program for implementation of AVL tree creation. (1-10)
#include<stdio.h>

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

int Tree_search(struct node *root, int k)
{
    if ((root == NULL) || (k==root->data))
    {
     return k;   
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

int 




int main()
{

}