#include <iostream>
#include "MLL.h"
using namespace std;

int main() {
    graph G;

    // Membangun graph berdasarkan gambar
    buildGraph(G);

    // Menampilkan graph
    cout << "Struktur Graph (Adjacency List):\n";
    printGraph(G);

    adrVertex v = G.firstVertex;
    while (v != NULL) {
        if (v->idVertex == 'G') {  // Cek apakah idVertex sama dengan 'G'
            break;  // Keluar dari loop jika ditemukan
        }
        v = v->nextVertex;
    }


    cout << "hasil DFS dari Node G (MSU) : ";
    if (v != NULL) {
        DFS(G, v);
    } else {
        cout << "Vertex G tidak ditemukan!" << endl;
    }

    return 0;
}
