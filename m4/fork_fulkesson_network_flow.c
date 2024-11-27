


/*
Ford-Fulkerson Algorithm Steps:
Initialize the maximum flow: Set the flow in all edges to 0.
Search for an augmenting path: Use a method like Depth-First Search (DFS)  or Breadth-First Search (BFS)  to find a path from the source to the sink where the residual capacity (original capacity minus flow) of all edges along the path is greater than zero.
Compute the residual capacity of the augmenting path: Find the minimum residual capacity along the path found in step 2.
Augment flow along the path: Increase the flow along the path by the residual capacity found in step 3, and decrease the flow in the opposite direction (if applicable).Repeat: 
Repeat steps 2-4 until no augmenting path can be found.
Output the maximum flow: The maximum flow is the total flow leaving the source node.

 */


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define V 6  // Number of vertices in graph

// Returns true if there is a path from source 's' to sink 't' in
// residual graph. Also fills parent[] to store the path
bool bfs(int rGraph[V][V], int s, int t, int parent[]) {
    bool visited[V];
    memset(visited, 0, sizeof(visited));

    // Create a queue, enqueue source vertex and mark source vertex as visited
    int queue[V], front = 0, rear = 0;
    queue[rear++] = s;
    visited[s] = true;
    parent[s] = -1;

    while (front != rear) {
        int u = queue[front++];
        for (int v = 0; v < V; v++) {
            if (visited[v] == false && rGraph[u][v] > 0) {
                if (v == t) {
                    parent[v] = u;
                    return true;
                }
                queue[rear++] = v;
                visited[v] = true;
                parent[v] = u;
            }
        }
    }
    return false;
}

// Returns the maximum flow from s to t in the given graph
int fordFulkerson(int graph[V][V], int s, int t) {
    int u, v;

    // Create a residual graph and fill the residual graph with given capacities in the original graph as residual capacities
    int rGraph[V][V];
    for (u = 0; u < V; u++)
        for (v = 0; v < V; v++)
             rGraph[u][v] = graph[u][v];

    int parent[V];  // This array is filled by BFS and to store path
    int max_flow = 0;  // There is no flow initially

    // Augment the flow while there is a path from source to sink
    while (bfs(rGraph, s, t, parent)) {
        // Find minimum residual capacity of the edges along the path filled by BFS
        int path_flow = 10000000;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = path_flow < rGraph[u][v] ? path_flow : rGraph[u][v];
        }

        // update residual capacities of the edges and reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        // Add path flow to overall flow
        max_flow += path_flow;
    }

    // Return the overall flow
    return max_flow;
}

int main() {
    // Let us create a graph shown in the above example
    int graph[V][V] = { {0, 16, 13, 0, 0, 0},
                        {0, 0, 10, 12, 0, 0},
                        {0, 4, 0, 0, 14, 0},
                        {0, 0, 9, 0, 0, 20},
                        {0, 0, 0, 7, 0, 4},
                        {0, 0, 0, 0, 0, 0}
                      };
    printf("The maximum possible flow is %d\n", fordFulkerson(graph, 0, 5));
    return 0;
}
