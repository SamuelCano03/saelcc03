#include <bits/stdc++.h>
using namespace std;

#define MAXN 100005
#define LOGN 20

vector<int> tree[MAXN];
vector<int> euler;        // euler tour de nodos
vector<int> depthEuler;   // profundidad de los nodos en el tour
int first[MAXN];          // primera aparición de cada nodo en el euler tour
int depth[MAXN];          // profundidad real del nodo en el árbol

int st[2 * MAXN][LOGN];   // sparse table sobre índices de euler

// DFS para llenar el euler tour
void dfs(int u, int p, int d) {
    depth[u] = d;
    first[u] = euler.size();
    euler.push_back(u);
    depthEuler.push_back(d);

    for (int v : tree[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
        // regresar al nodo u
        euler.push_back(u);
        depthEuler.push_back(d);
    }
}

// Sparse Table sobre depthEuler (para RMQ)
void buildST() {
    int n = depthEuler.size();
    for (int i = 0; i < n; ++i)
        st[i][0] = i; // guardar el índice

    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 0; i + (1 << j) <= n; ++i) {
            int left = st[i][j - 1];
            int right = st[i + (1 << (j - 1))][j - 1];
            st[i][j] = (depthEuler[left] < depthEuler[right]) ? left : right;
        }
}

// RMQ para obtener índice con menor profundidad
int rmq(int l, int r) {
    if (l > r) swap(l, r);
    int len = r - l + 1;
    int k = 31 - __builtin_clz(len); // floor(log2(len))
    int left = st[l][k];
    int right = st[r - (1 << k) + 1][k];
    return (depthEuler[left] < depthEuler[right]) ? left : right;
}

// Obtener LCA en O(1)
int lca(int u, int v) {
    int l = first[u];
    int r = first[v];
    int idx = rmq(l, r);
    return euler[idx];
}

