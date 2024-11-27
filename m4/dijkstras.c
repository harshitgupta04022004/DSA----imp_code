#include <stdio.h>
#include <limits.h>

#define V 5  // Number of vertices in the graph




/*
initalize the source vertex to 0 and other with inf
then take the smallest distance from the source to the next node (mean cost to reach the next node is minimum) then from that node select the node with minimun cost and the node is also not visited before
continue the process untill no node left to vidit from that node then backtrack the path and reach the privious node then check if any node is note visited if yes continue from that node if not the angain go 
to the privious node and do the same until you reach the starting node 

if afer that if any node ramain unvisited then visit them insililar manner 
and write them in first or the last 

*/

/*
Dijkstra's Algorithm Steps:
Initialization: Set the distance to the source vertex to 0 and to all other vertices as infinity. Mark all vertices as unvisited.
For each vertex in the graph:
    Select the unvisited vertex with the smallest distance (call this vertex U).
    Mark vertex U as visited.For each adjacent vertex V of U, check if there is a shorter path to V through U.
    If so, update the shortest distance of V.
Repeat the process until all vertices are visited.
*/




// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src) {
    int dist[V];  // The output array. dist[i] will hold the shortest distance from src to i
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}

int main() {
    /* Let's create the following graph
          10
       (0)-----(1)
        |       |
      6 |       | 15
        |       |
       (2)-----(3)
          4       */
    int graph[V][V] = {{0, 10, 0, 0, 0},
                       {10, 0, 0, 15, 0},
                       {0, 0, 0, 4, 0},
                       {0, 15, 4, 0, 0},
                       {0, 0, 0, 0, 0}};

    dijkstra(graph, 0);

    return 0;
}
