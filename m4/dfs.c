


/*
in the dfs implimentation, insert the first element and put that in the stack 
and also in the visited list and put any one not visited node in the stack and also in the visited list 
continue the process till no node remain left to visited from that node than back track and check the if any 
node is note visited if yes put that in the stack and also in the visited list than again backtrack the stack/ graph 
and repeate the process untill you reach the starting node.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

// Function to create an adjacency matrix
void addEdge(int graph[][V], int src, int dest) {
    graph[src][dest] = 1;
    graph[dest][src] = 1;
}

// DFS function
void DFSUtil(int graph[][V], int v, bool visited[]) {
    visited[v] = true;
    printf("%d ", v);

    for (int i = 0; i < V; i++) {
        if (graph[v][i] && !visited[i]) {
            DFSUtil(graph, i, visited);
        }
    }
}

void DFS(int graph[][V], int start) {
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    DFSUtil(graph, start, visited);
}

int main() {
    int graph[V][V] = {0};

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 2, 4);

    printf("DFS starting from vertex 0:\n");
    DFS(graph, 0);

    return 0;
}
