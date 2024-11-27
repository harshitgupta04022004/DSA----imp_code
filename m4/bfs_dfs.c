
/*
this is the shortest path algorithum starting from the fixed node.
in the implimentation of the bfs we make a queue and then , insert the first node to the queue than then explore the 
first element and write all the other not visited node connected to that node to the queue than afer exploration remove the 
that explored node from the queue and print that node 


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

// Function to print BFS traversal
void BFS(int graph[][V], int start) {
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    int queue[V], front = 0, rear = 0;

    visited[start] = true;
    queue[rear++] = start; // Enqueue

    while (front != rear) {
        int currentVertex = queue[front++]; // Dequeue

        printf("%d ", currentVertex);

        for (int i = 0; i < V; i++) {
            if (graph[currentVertex][i] && !visited[i]) {
                queue[rear++] = i; // Enqueue
                visited[i] = true;
            }
        }
    }
}

int main() {
    int graph[V][V] = {0};

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 2, 4);

    printf("BFS starting from vertex 0:\n");
    BFS(graph, 0);

    return 0;
}
