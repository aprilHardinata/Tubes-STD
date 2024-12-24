#include <iostream>
#include "MLL.h"
#include <string>  // Untuk std::string
using namespace std;

int main() {
    graph G;
    buildGraph(G);

    // Menampilkan graph
    cout << "Struktur Graph (Adjacency List):\n";
    printGraph(G);

    adrVertex start = findVertex(G, 'G'); // Vertex awal (MSU)
    adrVertex dest = findVertex(G, 'B');  // Vertex tujuan (SPORT CENTER)

    if (start != NULL && dest != NULL) {
        int minWeight = 200;       // Inisialisasi berat minimum ke nilai maksimum
        string shortestPath = "";     // Inisialisasi jalur terpendek
        string currentPath = "";      // Jalur saat ini
        bool visited[100] = {false};  // Array visited untuk menandai vertex

        DFS(G, start, dest, minWeight, shortestPath, currentPath, 0, visited);

        if (minWeight < INT_MAX) {
            cout << "\nJalur Terpendek dari G (MSU) ke B (SPORT CENTER): " << shortestPath << endl;
            cout << "Berat Total: " << minWeight << endl;
        } else {
            cout << "\nTidak ada jalur dari G ke B!" << endl;
        }
    } else {
        cout << "\nVertex G atau B tidak ditemukan!" << endl;
    }

    findShortestPathWithoutNode(G, 'G', 'B', 'C');


    return 0;
}
