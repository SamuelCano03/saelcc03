#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fore(i,a,b) for(int i=a;i<b;i++)
typedef vector<int> vi;

vector<vi> adj;
vector<int> disc, low, scc;
stack<int> stk;
vector<bool> inStack;
int timer, sccCount;

void tarjanDFS(int u) {
    disc[u] = low[u] = timer++;
    stk.push(u);
    inStack[u] = true;

    for (int v : adj[u]) {
        if (disc[v] == -1) { // Si aún no ha sido visitado
            tarjanDFS(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) { // Si está en la pila, actualizamos low
            low[u] = min(low[u], disc[v]);
        }
    }

    // Si `u` es la raíz de una SCC
    if (low[u] == disc[u]) {
        while (true) {
            int v = stk.top(); stk.pop();
            inStack[v] = false;
            scc[v] = sccCount;
            if (v == u) break;
        }
        sccCount++;
    }
}

void tarjanSCC(int n) {
    disc.assign(n, -1);
    low.assign(n, -1);
    scc.assign(n, -1);
    inStack.assign(n, false);
    timer = sccCount = 0;

    fore(i, 0, n) if (disc[i] == -1) tarjanDFS(i);
}

int main() {
    int n, m;
    cin >> n >> m;
    adj.assign(n, vi());

    fore(i, 0, m) {
        int u, v;
        cin >> u >> v;
        adj[u - 1].pb(v - 1); // Convertimos a índice 0
    }

    tarjanSCC(n);

    cout << "Componentes Fuertemente Conexas:\n";
    fore(i, 0, n) cout << "Nodo " << i + 1 << " está en la SCC " << scc[i] << "\n";

    return 0;
}

