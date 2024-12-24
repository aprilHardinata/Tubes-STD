#include "MLL.h"

void initStack(Stack &S) {
    S.top = -1;
}

bool isEmpty(Stack S) {
    return S.top == -1;
}

void push(Stack &S, adrVertex v) {
    if (S.top < MAX_STACK - 1) {
        S.data[++S.top] = v;
    }
}

adrVertex pop(Stack &S) {
    if (!isEmpty(S)) {
        return S.data[S.top--];
    }
    return NULL;
}


void createVertex(char newVertexID, adrVertex &v) {
    v = new vertex;
    v->idVertex = newVertexID;   // Mengatur ID vertex
    v->nextVertex = NULL;        // Vertex belum terhubung ke vertex lain
    v->firstEdge = NULL;         // Belum ada edge yang terhubung
}

adrVertex findVertex(graph G, char id) {
    adrVertex p = G.firstVertex;
    while (p != NULL && p->idVertex != id) {
        p = p->nextVertex;
    }
    return p;
}

adrEdge createEdge(char destId, int weight) {
    adrEdge newEdge = new edge;
    newEdge->destVertexId = destId;
    newEdge->weight = weight;
    newEdge->nextEdge = NULL;
    return newEdge;
}


void initGraph(graph &G) {
    G.firstVertex = NULL;
}

void addVertex(graph &G, char newVertexID) {
    adrVertex newVertex;
    createVertex(newVertexID, newVertex);

    if (G.firstVertex == NULL) {
        G.firstVertex = newVertex;
    } else {
        adrVertex temp = G.firstVertex;
        while (temp->nextVertex != NULL) {
            temp = temp->nextVertex;
        }
        temp->nextVertex = newVertex;
    }
}

void addEdge(adrVertex &source, adrVertex &dest, int weight) {
    adrEdge newEdge = new edge;
    newEdge->destVertexId = dest->idVertex;
    newEdge->weight = weight;
    newEdge->nextEdge = NULL;

    // Menambahkan edge ke adjacency list source
    if (source->firstEdge == NULL) {
        source->firstEdge = newEdge;
    } else {
        adrEdge temp = source->firstEdge;
        while (temp->nextEdge != NULL) {
            temp = temp->nextEdge;
        }
        temp->nextEdge = newEdge;
    }
}

void addUndirectedEdge(graph &G, char sourceID, char destID, int weight) {
    adrVertex source = G.firstVertex;
    adrVertex dest = G.firstVertex;

    while (source != NULL && source->idVertex != sourceID) {
        source = source->nextVertex;
    }
    while (dest != NULL && dest->idVertex != destID) {
        dest = dest->nextVertex;
    }

    if (source != NULL && dest != NULL) {
        addEdge(source, dest, weight);
        addEdge(dest, source, weight);
    }
}

void buildGraph(graph &G) {
    initGraph(G);

    addVertex(G, 'A'); // TUCH
    addVertex(G, 'B'); // Sport center
    addVertex(G, 'C'); // Hotel lingian
    addVertex(G, 'D'); // Rektorat
    addVertex(G, 'E'); // Fakultas ilmu terapan
    addVertex(G, 'F'); // Gedung damar(K)
    addVertex(G, 'G'); // MSU

    addUndirectedEdge(G, 'A', 'B', 3);
    addUndirectedEdge(G, 'A', 'D', 4);
    addUndirectedEdge(G, 'A', 'E', 4);
    addUndirectedEdge(G, 'B', 'C', 3);
    addUndirectedEdge(G, 'C', 'D', 1);
    addUndirectedEdge(G, 'C', 'F', 2);
    addUndirectedEdge(G, 'D', 'E', 1);
    addUndirectedEdge(G, 'D', 'F', 2);
    addUndirectedEdge(G, 'F', 'G', 2);
}

void DFS(graph G, adrVertex v) {
    Stack S;
    bool visited[100];  // Array untuk menandai apakah vertex sudah dikunjungi
    adrVertex x, w;

    // Inisialisasi stack dan array visited
    initStack(S);
    for (int i = 0; i < 100; i++) visited[i] = false;

    // Mulai DFS dengan menambahkan vertex awal ke stack
    push(S, v);
    visited[v->idVertex - 'A'] = true;  // Tandai vertex sebagai dikunjungi

    while (!isEmpty(S)) {
        x = pop(S);
        cout << x->idVertex << " ";  // Menampilkan vertex yang dikunjungi

        // Traverse semua tetangga dari vertex x
        adrEdge edge = x->firstEdge;
        while (edge != NULL) {
            w = findVertex(G, edge->destVertexId);
            if (!visited[w->idVertex - 'A']) {
                push(S, w);  // Tambahkan tetangga ke stack
                visited[w->idVertex - 'A'] = true;  // Tandai sebagai dikunjungi
            }
            edge = edge->nextEdge;
        }
    }
}


void printGraph(graph G) {
    adrVertex tempVertex = G.firstVertex;
    while (tempVertex != NULL) {
        cout << tempVertex->idVertex << " -> ";
        adrEdge tempEdge = tempVertex->firstEdge;
        while (tempEdge != NULL) {
            cout << "(" << tempEdge->destVertexId << ", " << tempEdge->weight << ") ";
            tempEdge = tempEdge->nextEdge;
        }
        cout << endl;
        tempVertex = tempVertex->nextVertex;
    }
}


