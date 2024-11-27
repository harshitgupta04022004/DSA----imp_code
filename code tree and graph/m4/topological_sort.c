/*
The graph must me (DAC) directed cyclic 
mark the indegree of the node, then remove the node with 0 indegree and also all edges connected to it. 
then rewrite the indegree of all the vertex and then remove the node with 0 indegree repeate the process untill no node  left 
in the graph. note there are multiple node with zero indregree remove them first in any order you want 
note a (DAC) graph has multiple topological sorting order depend upon the choce of the 
*/



#include <stdio.h>
#include <stdlib.h>
#define MAX 6

int n = 6;  // Number of vertices
int adj[MAX][MAX] = {
    {0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0}
};  // Adjacency matrix
int visited[MAX] = {0};
int stack[MAX], top = -1;

void dfs(int v) {
    visited[v] = 1;
    for (int i = 0; i < n; i++) {
        if (adj[v][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
    stack[++top] = v;
}

void topologicalSort() {
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
}

int main() {
    printf("Topological Sorting Order: ");
    topologicalSort();
    return 0;
}
