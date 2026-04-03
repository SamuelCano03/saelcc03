Ford-Fulkerson
#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Estructura que representa una arista en la red de flujo
struct Edge {
    int source, destination;
    int capacity, flow;
};

// Función para agregar una arista a la red de flujo
void addEdge(vector<vector<int>>& graph, int u, int v, int capacity) {
    graph[u][v] = capacity;
}

// Función auxiliar para encontrar un camino aumentante utilizando BFS
bool bfs(vector<vector<int>>& residualGraph, vector<int>& parent, int source, int sink) {
    int V = residualGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && residualGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[sink];
}

// Algoritmo de Ford-Fulkerson para encontrar el flujo máximo
int fordFulkerson(vector<vector<int>>& graph, int source, int sink) {
    int V = graph.size();

    // Creamos una copia del grafo original para almacenar el grafo residual
    vector<vector<int>> residualGraph(V, vector<int>(V, 0));
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            residualGraph[u][v] = graph[u][v];
        }
    }

    vector<int> parent(V, -1);
    int maxFlow = 0;

    // Mientras haya un camino aumentante, encontramos el flujo máximo
    while (bfs(residualGraph, parent, source, sink)) {
        int pathFlow = numeric_limits<int>::max();

        // Encontramos la capacidad mínima restante en el camino aumentante
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, residualGraph[u][v]);
        }

        // Actualizamos los flujos en las aristas del camino aumentante
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            residualGraph[u][v] -= pathFlow;
            residualGraph[v][u] += pathFlow;
        }

        // Aumentamos el flujo máximo
        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main() {
    int V, E;
    cout << "Ingrese el número de nodos (V): ";
    cin >> V;
    cout << "Ingrese el número de aristas (E): ";
    cin >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "Ingrese las aristas en el formato (fuente destino capacidad):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, capacity;
        cin >> u >> v >> capacity;
        addEdge(graph, u, v, capacity);
    }

    int source, sink;
    cout << "Ingrese el nodo fuente: ";
    cin >> source;
    cout << "Ingrese el nodo sumidero: ";
    cin >> sink;

    int maxFlow = fordFulkerson(graph, source, sink);
    cout << "El flujo máximo es: " << maxFlow << endl;

    return 0;
}