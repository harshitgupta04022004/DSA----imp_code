#include <stdio.h>
#include <stdlib.h>


// does not start with a fixed node. chose the node as per the basis of the edge weight of the edge smallest weight edge is selected first if it does not form the cycle in the mst

/*
Kruskal's Algorithm Steps:
Sort all the edges from the graph in non-decreasing order of their weight.
Initialize a forest as a set of trees, where each vertex in the graph is a separate tree.
Initialize the MST as empty.
For each edge in the sorted list:
                    If the edge connects two different trees, then add it to the MST and union the two trees into a single tree.
                    If the edge connects two vertices in the same tree, skip it as it would form a [cycle]).                   
Repeat step 4 until there are ( V-1 ) edges in the MST, where ( V ) is the number of vertices in the graph.



    10
  0----1
  |  / |
6 | 5  | 15
  | /  |
  2----3
    4


Sorted Edges by Weight:
Edge 2-3 with weight 4
Edge 0-3 with weight 5
Edge 0-2 with weight 6
Edge 0-1 with weight 10
Edge 1-3 with weight 15
Building the MST:
Step 1: Choose edge 2-3 (weight 4). MST now has edges {2-3}.
Step 2: Choose edge 0-3 (weight 5). MST now has edges {2-3, 0-3}.
Step 3: Choose edge 0-2 (weight 6). MST now has edges {2-3, 0-3, 0-2}.
Step 4: Next edge 0-1 (weight 10) connects two vertices already in MST, skip it to avoid cycle.
Step 5: Choose edge 1-3 (weight 15) would form a cycle with 0-1-3, skip it.
The final MST consists of edges {2-3, 0-3, 0-2} with total weight 15.



*/



/*
select the edge min edge weight and not form a cycle every time next min is selected and the same condiction is checked 

*/




// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent a graph
struct Graph {
    int V, E;
    struct Edge* edge;
};

// Structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// Function prototypes
struct Graph* createGraph(int V, int E);
int myComp(const void* a, const void* b);
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
void KruskalMST(struct Graph* graph);

int main() {
    /* Let's create the following weighted graph
         10
       0----1
       |  / |
      6| 5  |15
       | /  |
       2----3
         4       */
    int V = 4;  // Number of vertices in graph
    int E = 5;  // Number of edges in graph
    struct Graph* graph = createGraph(V, E);

    // add edge 0-1
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // add edge 0-2
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // add edge 0-3
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // add edge 1-3
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // add edge 2-3
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    KruskalMST(graph);

    return 0;
}

struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge));
    return graph;
}

int myComp(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];  // This will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges

    // Step 1:  Sort all the edges in non-decreasing order of their weight
    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    // Allocate memory for creating V subsets
    struct subset *subsets = (struct subset*) malloc(V * sizeof(struct subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < graph->E) {
        // Step 2: Pick the smallest edge. And increment the index for next iteration
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does't cause cycle, include it in result
        // and increment the index of result for next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    // print the contents of result[] to display the built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    return;
}
