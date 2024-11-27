#include <stdio.h>
#include <stdlib.h>


/*
Segment Tree AlgorithmA 
segment tree is a data structure that allows answering range queries over an array effectively, while still being flexible enough to allow modifying the array. This includes operations like finding the minimum, maximum, sum, or greatest common divisor of array elements between two given indices.
Here are the key operations of a segment tree:
Build: Construct the segment tree from a given array.Update: 
Modify an element of the array and reflect this change in the segment tree.
Query: Calculate a range query (like sum, min, or max) between two indices.

the leaf node in the tree is the original node or the input array 
the layer above the leaf node is the sum of two nodes repeat the process untill you reach the node with single sum. that is the sum of whole array,
the sum quary takes Olog(n) time and the update quary takes Olog(n) time beacause it need to update the whole branch of the tree as the value 
of the node change the sum of the parent the also change so update of the paraent value also needed.

for building a tree with array:
here is the example 


*/

int a[1000],tree[4000];
void bulid(int node, int st, int en )
{
    if (st==en)
    {
        tree[node]=a[st];
        return;
    }
    int mid =(st+en)/2;
    bulid(2*node, st,mid);
    bulid(2*node+1, mid+1,en);
    tree[node]= tree[2*node]+tree[2*node+1];
}










// Function to build the segment tree
void buildTree(int *arr, int *tree, int start, int end, int treeNode) {
    if (start == end) {
        tree[treeNode] = arr[start];
        return;
    }

    int mid = (start + end) / 2;
    buildTree(arr, tree, start, mid, 2 * treeNode);
    buildTree(arr, tree, mid + 1, end, 2 * treeNode + 1);
    tree[treeNode] = tree[2 * treeNode] + tree[2 * treeNode + 1];
}

// Function to update a single element in the segment tree
void updateTree(int *arr, int *tree, int start, int end, int treeNode, int idx, int value) {
    if (start == end) {
        arr[idx] = value;
        tree[treeNode] = value;
        return;
    }

    int mid = (start + end) / 2;
    if (idx > mid) {
        updateTree(arr, tree, mid + 1, end, 2 * treeNode + 1, idx, value);
    } else {
        updateTree(arr, tree, start, mid, 2 * treeNode, idx, value);
    }
    tree[treeNode] = tree[2 * treeNode] + tree[2 * treeNode + 1];
}

// Function to get the sum of elements within a given range
int queryTree(int *tree, int start, int end, int treeNode, int left, int right) {
    // Completely outside the given range
    if (start > right || end < left) {
        return 0;
    }
    // Completely inside the given range
    if (start >= left && end <= right) {
        return tree[treeNode];
    }
    // Partially inside and partially outside
    int mid = (start + end) / 2;
    int leftChild = queryTree(tree, start, mid, 2 * treeNode, left, right);
    int rightChild = queryTree(tree, mid + 1, end, 2 * treeNode + 1, left, right);
    return leftChild + rightChild;
}

int main() {
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *tree = (int *)malloc(4 * n * sizeof(int));

    buildTree(arr, tree, 0, n - 1, 1);
    printf("Sum of values in range [1, 3]: %d\n", queryTree(tree, 0, n - 1, 1, 1, 3));
    updateTree(arr, tree, 0, n - 1, 1, 2, 10);
    printf("Updated sum of values in range [1, 3]: %d\n", queryTree(tree, 0, n - 1, 1, 1, 3));

    free(tree);
    return 0;
}
