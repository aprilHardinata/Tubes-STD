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

void DFS(graph G, adrVertex start, adrVertex dest, int &minWeight, string &shortestPath, string currentPath, int currentWeight, bool visited[]) {
    visited[start->idVertex - 'A'] = true;
    currentPath += start->idVertex;

    if (start == dest) {
        if (currentWeight < minWeight) {
            minWeight = currentWeight;
            shortestPath = currentPath;
        }
    } else {
        adrEdge edge = start->firstEdge;
        while (edge != NULL) {
            adrVertex nextVertex = findVertex(G, edge->destVertexId);
            if (!visited[nextVertex->idVertex - 'A']) {
                DFS(G, nextVertex, dest, minWeight, shortestPath, currentPath, currentWeight + edge->weight, visited);
            }
            edge = edge->nextEdge;
        }
    }

    visited[start->idVertex - 'A'] = false;
}

void DFSWithoutNode(graph G, adrVertex start, adrVertex dest, int &minWeight, string &shortestPath, string currentPath, int currentWeight, bool visited[], char excludedNode) {
    visited[start->idVertex - 'A'] = true;
    currentPath += start->idVertex;

    if (start == dest) {
        if (currentWeight < minWeight) {
            minWeight = currentWeight;
            shortestPath = currentPath;
        }
    } else {
        adrEdge edge = start->firstEdge;
        while (edge != NULL) {
            adrVertex nextVertex = findVertex(G, edge->destVertexId);

            // Hanya lanjutkan jika vertex belum dikunjungi dan bukan vertex yang dilarang
            if (nextVertex->idVertex != excludedNode && !visited[nextVertex->idVertex - 'A']) {
                DFSWithoutNode(G, nextVertex, dest, minWeight, shortestPath, currentPath, currentWeight + edge->weight, visited, excludedNode);
            }
            edge = edge->nextEdge;
        }
    }

    // Kembalikan status kunjungan untuk backtracking
    visited[start->idVertex - 'A'] = false;
}

void findShortestPathWithoutNode(graph G, char startId, char destId, char excludedNode) {
    adrVertex start = findVertex(G, startId);
    adrVertex dest = findVertex(G, destId);

    if (start == NULL || dest == NULL) {
        cout << "Start or destination vertex not found!\n";
        return;
    }

    int minWeight = INT_MAX;
    string shortestPath = "";
    string currentPath = "";
    bool visited[26] = {false};

    DFSWithoutNode(G, start, dest, minWeight, shortestPath, currentPath, 0, visited, excludedNode);

    if (shortestPath.empty()) {
        cout << "No path found excluding node " << excludedNode << "!\n";
    } else {
        cout << "Jalan tercepat dari " << startId << " (MSU) "<< " ke " << destId << " (SPORT CENTER)"<< " Tanpa node " << excludedNode << ": " << shortestPath << endl << "Berat total :" << minWeight << "\n";
    }
}

void printGraph(graph G) {
    adrVertex tempVertex = G.firstVertex;
    while (tempVertex != NULL) {
        cout << tempVertex->idVertex;

        // Menambahkan deskripsi vertex
        switch (tempVertex->idVertex) {
            case 'A': cout << " = TUCH"; break;
            case 'B': cout << " = SPORT CENTER"; break;
            case 'C': cout << " = HOTEL LINGGIAN"; break;
            case 'D': cout << " = REKTORAT"; break;
            case 'E': cout << " = FAKULTAS ILMU TERAPAN"; break;
            case 'F': cout << " = GEDUNG DAMAR(K)"; break;
            case 'G': cout << " = MSU"; break;
        }

        cout << " -> ";
        adrEdge tempEdge = tempVertex->firstEdge;
        while (tempEdge != NULL) {
            cout << "(" << tempEdge->destVertexId << ", " << tempEdge->weight << ") ";
            tempEdge = tempEdge->nextEdge;
        }
        cout << endl;
        tempVertex = tempVertex->nextVertex;
    }
}


