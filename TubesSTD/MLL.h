#ifndef MLL_H_INCLUDED
#define MLL_H_INCLUDED
#include <iostream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

typedef struct vertex* adrVertex;
typedef struct edge* adrEdge;

const int MAX_STACK = 100;
struct Stack {
    adrVertex data[MAX_STACK];
    int top;
};

struct vertex {
    char idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct edge {
    char destVertexId;
    int weight;
    adrEdge nextEdge;
};

struct graph {
    adrVertex firstVertex;
};

void initStack(Stack &S);
bool isEmpty(Stack S);
void push(Stack &S, adrVertex v);
adrVertex pop(Stack &S);
void createVertex(char newVertexID, adrVertex &v);
adrVertex findVertex(graph G, char id);
adrEdge createEdge(char destId, int weight);
void initGraph(graph &G);
void addVertex(graph &G, char newVertexID);
void addEdge(graph &G, char srcId, char destId, int weight);
void addUndirectedEdge(graph &G, char sourceID, char destID, int weight);
void buildGraph(graph &G);
void DFS(graph G, adrVertex v);
void printGraph(graph G);

#endif // MLL_H_INCLUDED
