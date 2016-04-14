#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100000

int least;

typedef struct Queue
{
	int front, rear, size;
	unsigned capacity;
	int *array;
}front_q;

// function to create a queue of given capacity. It initializes size of 
// queue as 0
struct front_q* createQueue(unsigned capacity)
{
	front_q* queue = (front_q*) malloc(sizeof(front_q));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;  // This is important, see the enqueue
	queue->array = (int*)malloc(queue->capacity * sizeof(int));
	return queue;
}

// Queue is full when size becomes equal to the capacity 
int isFull(front_q *queue)
{
	return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(front_q *queue)
{
	return (queue->size == 0);
}

// Function to add an item to the queue.  It changes rear and size
void enqueue(front_q  *queue, int item)
{
	if (isFull(queue))
		return;
	queue->rear = (queue->rear + 1) % queue->capacity;
	queue->array[queue->rear] = item;
	queue->size = queue->size + 1;
}

// Function to remove an item from queue.  It changes front and size
int dequeue(front_q *queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	int item = queue->array[queue->front];
	queue->front = (queue->front + 1) % queue->capacity;
	queue->size = queue->size - 1;
	return item;
}

// Function to get front of queue
int front(front_q *queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->front];
}

// Function to get rear of queue
int rear(struct Queue* queue)
{
	if (isEmpty(queue))
		return INT_MIN;
	return queue->array[queue->rear];
}

typedef struct neighbour {
	int index;
	struct neighbour *next;
}neighbour;

typedef struct vertex //dany vrchol
{
	int index;
	neighbour *head;  // susedia
}vertex;

typedef struct Graph
{
	int V;
	vertex* array;
} graph;

struct neighbour* newNeighbour(int dest) // reprezentacia suseda
{
	neighbour *newNode =(neighbour*)malloc(sizeof(neighbour));
	newNode->index = dest;
	newNode->next = NULL;
	return newNode;
}

graph* createGraph(int V)
{
	graph* gr = (graph*) malloc(sizeof(graph));
	gr->V = V;

	gr->array = (vertex*) malloc(V * sizeof(vertex));

	for (int i = 0; i < V; ++i) { // init pole vrcholov, kazdy ma spajany zoznam hran
		gr->array[i].head = NULL;
		gr->array[i].index = i;
	}


	return gr;
}

void addEdge(graph *graph, int src, int dest)
{
	neighbour* newNode = newNeighbour(dest);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;

	newNode = newAdjListNode(src);
	newNode->next = graph->array[dest].head;
	graph->array[dest].head = newNode;
}

int bfs_1(graph *g){
	vertex *s = &(g->array[0]);
	vertex *act = NULL;
	neighbour *ne = NULL; //neighbour
	int i;

	insertData(s);

	while (!isEmpty()) {
		act = removeData();
		ne = act->head;
		while (ne != NULL) {
			if (g->array[ne->index].visited == 0)
				insertData(&(g->array[ne->dest]));
			ne = ne->next;
		}
		act->visited = 1;
	}
	
}

int bfs_2(int ind) {
	resetFront();
	insertData(&(g->array[ind]));
}



int main() {
	graph *g = NULL;
	int i, j, k, l, n, x, c;

	scanf("%d", &k); // pocet grafov

	for (i = 0; i < k; i++) {
		scanf("%d", &n); // pocet hran
		g = createGraph(n);
		for (j = 0; j < n; j++) {
			scanf("%d", &x); // pocet susedov
			for (k = 0; k < x; k++) {
				scanf("%d", &c);
				addEdge(g, j, c, 0);
			}
		}
	}

	return 0;
}