#include <bits/stdc++.h>
#define pb push_back
#define oo 1000
using namespace std;

vector<int> adj[100], peso[100];
int n;

struct nodo {
    int id, w;
    nodo (int _id, int _w) {
        id = _id, w = _w;
    }
    bool operator < (nodo aux) const {
        return w  > aux.w;
    }
};

//construyo mst a partis del nodo s // O(E log E)
int mst_prim(int s) {
    int ans = 0;
    priority_queue<nodo> Q;
    vector<int> dist(n, oo), used(n, 0);
    dist[s] = 0;
    Q.push(nodo(s, 0));
    
    while (!Q.empty()) {
        nodo p = Q.top();
        Q.pop();
        int u = p.id;
        if (used[u]) continue;
        ans += p.w;
        used[u] = 1;
        int sz = adj[u].size();
        for (int i = 0; i < sz; ++i) {
            int v = adj[u][i];
            int w = peso[u][i];
            int temp = w;
            if (temp < dist[v] && !used[v]) {
                dist[v] = temp;
                Q.push(nodo(v, temp));
            }
        }
    }
    return ans;
}

int main() {
    int u, v, w, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        adj[u].pb(v), peso[u].pb(w); 
        adj[v].pb(u); peso[v].pb(w);
    }
    cout << mst_prim(0);
    return 0;
}