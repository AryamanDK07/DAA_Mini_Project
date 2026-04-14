#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

// --- Graph (Adjacency List) ---

struct Edge {
    int to, weight;
    struct Edge* next;
};

struct Graph {
    int V;
    struct Edge** list;
};

struct Graph* createGraph(int V) {
    struct Graph* g = malloc(sizeof(struct Graph));
    g->V = V;
    g->list = malloc(V * sizeof(struct Edge*));
    for (int i = 0; i < V; i++)
        g->list[i] = NULL;
    return g;
}

void addEdge(struct Graph* g, int u, int v, int w) {
    struct Edge* e = malloc(sizeof(struct Edge));
    e->to = v;
    e->weight = w;
    e->next = g->list[u];
    g->list[u] = e;
}

void freeGraph(struct Graph* g) {
    for (int i = 0; i < g->V; i++) {
        struct Edge* e = g->list[i];
        while (e) {
            struct Edge* tmp = e->next;
            free(e);
            e = tmp;
        }
    }
    free(g->list);
    free(g);
}

// --- Min Heap (Priority Queue) ---
// pos[v] stores where vertex v sits in the heap array
// so we can update its distance in O(log V) directly

struct HeapNode {
    int vertex, dist;
};

struct MinHeap {
    int size;
    int* pos;
    struct HeapNode* array;
};

struct MinHeap* createHeap(int cap) {
    struct MinHeap* h = malloc(sizeof(struct MinHeap));
    h->size  = 0;
    h->pos   = malloc(cap * sizeof(int));
    h->array = malloc(cap * sizeof(struct HeapNode));
    return h;
}

void swap(struct MinHeap* h, int i, int j) {
    h->pos[h->array[i].vertex] = j;
    h->pos[h->array[j].vertex] = i;
    struct HeapNode tmp = h->array[i];
    h->array[i] = h->array[j];
    h->array[j] = tmp;
}

void bubbleUp(struct MinHeap* h, int i) {
    int p = (i - 1) / 2;
    while (i > 0 && h->array[p].dist > h->array[i].dist) {
        swap(h, p, i);
        i = p;
        p = (i - 1) / 2;
    }
}

void bubbleDown(struct MinHeap* h, int i) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < h->size && h->array[left].dist  < h->array[smallest].dist) smallest = left;
    if (right < h->size && h->array[right].dist < h->array[smallest].dist) smallest = right;
    if (smallest != i) {
        swap(h, i, smallest);
        bubbleDown(h, smallest);
    }
}

void insert(struct MinHeap* h, int vertex, int dist) {
    int i = h->size++;
    h->array[i].vertex = vertex;
    h->array[i].dist   = dist;
    h->pos[vertex]     = i;
    bubbleUp(h, i);
}

struct HeapNode extractMin(struct MinHeap* h) {
    struct HeapNode min = h->array[0];
    h->size--;
    if (h->size > 0) {
        h->array[0] = h->array[h->size];
        h->pos[h->array[0].vertex] = 0;
        bubbleDown(h, 0);
    }
    h->pos[min.vertex] = -1; // -1 means finalized, out of heap
    return min;
}

void decreaseKey(struct MinHeap* h, int vertex, int newDist) {
    int i = h->pos[vertex];
    h->array[i].dist = newDist;
    bubbleUp(h, i);
}

bool inHeap(struct MinHeap* h, int vertex) {
    return h->pos[vertex] != -1;
}

void freeHeap(struct MinHeap* h) {
    free(h->pos);
    free(h->array);
    free(h);
}

// --- Path Printing ---
// Recurse to src first, then print on the way back

void printPath(int* prev, int src, int dest) {
    if (dest == src) { printf("%d", src); return; }
    if (prev[dest] == -1) { printf("no path"); return; }
    printPath(prev, src, prev[dest]);
    printf(" -> %d", dest);
}

// --- Dijkstra ---
// Time: O((V + E) log V)

void dijkstra(struct Graph* g, int src) {
    int V = g->V;
    int* dist = malloc(V * sizeof(int));
    int* prev = malloc(V * sizeof(int));
    struct MinHeap* heap = createHeap(V);

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        insert(heap, i, INT_MAX);
    }
    dist[src] = 0;
    decreaseKey(heap, src, 0);

    while (heap->size > 0) {
        struct HeapNode u = extractMin(heap); // pick nearest vertex
        if (u.dist == INT_MAX) break;         // rest are unreachable

        struct Edge* e = g->list[u.vertex];
        while (e) {
            int v = e->to;
            int newDist = dist[u.vertex] + e->weight;
            if (inHeap(heap, v) && newDist < dist[v]) {
                dist[v] = newDist;
                prev[v] = u.vertex;
                decreaseKey(heap, v, newDist);
            }
            e = e->next;
        }
    }

    printf("\nShortest paths from vertex %d:\n\n", src);
    printf("%-8s %-12s %s\n", "Dest", "Distance", "Path");
    printf("----------------------------------------\n");
    for (int i = 0; i < V; i++) {
        printf("%-8d ", i);
        if (dist[i] == INT_MAX)
            printf("%-12s no path\n", "INF");
        else {
            printf("%-12d ", dist[i]);
            printPath(prev, src, i);
            printf("\n");
        }
    }

    free(dist);
    free(prev);
    freeHeap(heap);
}

// --- Main ---

int main() {
    int V = 5;
    struct Graph* g = createGraph(V);

    addEdge(g, 0, 1, 10);
    addEdge(g, 0, 4,  5);
    addEdge(g, 1, 2,  1);
    addEdge(g, 1, 4,  2);
    addEdge(g, 2, 3,  4);
    addEdge(g, 3, 0,  7);
    addEdge(g, 3, 2,  6);
    addEdge(g, 4, 1,  3);
    addEdge(g, 4, 2,  9);
    addEdge(g, 4, 3,  2);

    dijkstra(g, 0);
    freeGraph(g);
    return 0;
}