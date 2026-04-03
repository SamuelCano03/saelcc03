Floyd-Warshall
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Función para encontrar los caminos más cortos entre todos los pares de nodos
void floydWarshall(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> dist(V, vector<int>(V, 0));

    // Inicializar la matriz de distancias
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
        }
    }

    // Calcular los caminos más cortos
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != numeric_limits<int>::max() && dist[k][j] != numeric_limits<int>::max() && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Mostrar los caminos más cortos
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == numeric_limits<int>::max()) {
                cout << "Inf ";
            } else {
                cout << dist[i][j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int V;
    cout << "Ingrese el número de nodos: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "Ingrese la matriz de adyacencia del grafo (use 'Inf' para representar la ausencia de aristas):" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string input;
            cin >> input;
            if (input == "Inf") {
                graph[i][j] = numeric_limits<int>::max();
            } else {
                graph[i][j] = stoi(input);
            }
        }
    }

    floydWarshall(graph);

    return 0;
}

/* Ingrese el número de nodos: 4
Ingrese la matriz de adyacencia del grafo (use 'Inf' para representar la ausencia de aristas):
0 3 Inf 7
8 0 2 Inf
5 Inf 0 1
2 Inf Inf 0
 */