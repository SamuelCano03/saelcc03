#include<bits/stdc++.h>
#define N 1000
#define oo 1000
using namespace std;
//hii
int n, m, u, v, w;

vector<tuple <int, int, int>> edges;
int dist[100]; 

void bellman_ford(int s){
    for(int i = 0; i < n; ++i) dist[i] = oo;
    dist[s] = 0;

    for (int i = 1; i < n; ++i){
        for(auto e : edges){
            int u, v, w;
            tie(u, v, w) = e;
            if (dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
            }
        }
    }
}

bool neg_ciclo(){
    for(auto e : edges){
            int u, v, w;
            tie(u, v, w) = e;
            if (dist[v] > dist[u] + w){
                return 1;
            }
        }
    return 0;
}

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; ++i){
        cin >> u >> v >> w;
        edges.emplace_back(make_tuple(u, v, w));
    }
    bellman_ford(0);
    for (int i = 0; i < n; ++i) cout << " " << dist[i];
    cout << "\n";
    cout << neg_ciclo();
    return 0;
}