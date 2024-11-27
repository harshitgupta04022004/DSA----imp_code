#include <stdio.h>
#include <stdlib.h>

/*
Disjoint Set (Union-Find) AlgorithmA disjoint-set, also known as a union-find data structure, is used to manage a collection of disjoint (non-overlapping) sets. It provides two primary operations:
Find: Determine which set a particular element belongs to. This operation can also be used for checking if two elements are in the same set.
Union: Merge two sets into a single set.
The efficiency of these operations is improved by two techniques:
Union by Rank: Attach the smaller tree under the root of the larger tree.   create a rank array and a parent array and use the unit and find and update the rank and the parand array
Path Compression: Flatten the structure of the tree whenever Find is used on it.    create the size and the parent array use the union and the find method for the update the both the array.



*/









typedef struct {
    int *parent;
    int *rank;
    int n;
} DisjointSet;

// Create a new Disjoint Set
DisjointSet* createSet(int n) {
    DisjointSet *set = (DisjointSet *)malloc(sizeof(DisjointSet));
    set->parent = (int *)malloc(n * sizeof(int));
    set->rank = (int *)malloc(n * sizeof(int));
    set->n = n;

    for (int i = 0; i < n; i++) {
        set->parent[i] = i;
        set->rank[i] = 0;
    }

    return set;
}

// Find the parent of a node (with path compression)
int find(DisjointSet *set, int i) {
    if (set->parent[i] != i)
        set->parent[i] = find(set, set->parent[i]);
    return set->parent[i];
}

// Union of two sets
void unionSet(DisjointSet *set, int x, int y) {
    int xroot = find(set, x);
    int yroot = find(set, y);

    if (xroot != yroot) {
        if (set->rank[xroot] < set->rank[yroot])
            set->parent[xroot] = yroot;
        else if (set->rank[xroot] > set->rank[yroot])
            set->parent[yroot] = xroot;
        else {
            set->parent[yroot] = xroot;
            set->rank[xroot] = set->rank[xroot] + 1;
        }
    }
}

// Main function to demonstrate the algorithm
int main() {
    int n = 5;
    DisjointSet *set = createSet(n);

    unionSet(set, 0, 2);
    unionSet(set, 4, 2);
    unionSet(set, 3, 1);

    if (find(set, 4) == find(set, 3))
        printf("Yes\n");
    else
        printf("No\n");

    if (find(set, 1) == find(set, 0))
        printf("No\n");
    else
        printf("Yes\n");

    return 0;
}
