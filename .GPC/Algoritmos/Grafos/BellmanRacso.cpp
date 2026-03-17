#include <bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;

int n;
int m;
int D[N]; // D[u] : Minima distancia de src a u usando <= k aristas en la k-ésima iteración
bool vis[N]; // vis[u] : El nodo se ha vuelto alcanzable por src
vector<tuple<int, int, int>> edges;

bool bellman_ford(int src) {
	for(int i = 0; i < n; i++) {
		D[i] = -1;
		vis[i] = false;
	}
	D[src] = 0;
	vis[src] = true;
	for(int i = 1; i < n; i++) {
		for(auto e : edges) {
			int u, v, w;
			tie(u, v, w) = e;
			if(!vis[u]) continue;
			if(!vis[v] or D[v] > D[u] + w) {
				D[v] = D[u] + w;
				vis[v] = true;
			}
		}
	}
	for(auto e : edges){
		int u, v, w;
		tie(u, v, w) = e;
		if(not vis[u]) continue;
		if(not vis[v] or D[v] > D[u] + w) {
			return false; // Ciclo negativo alcanzable por src
		}
	}
	return true;
}

int main() {
	int s;
	scanf("%d %d %d", &n, &m, &s);
	for(int i = 0; i < m; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges.emplace_back(u, v, w);
	}
	if(not bellman_ford(s)) {
		puts("NEGATIVE CYCLE");
		return 0;
	}
	for(int i = 0; i < n; i++) {
		if(not vis[i]) puts("INF");
		else printf("%d\n", D[i]);
	}
	return 0;
}