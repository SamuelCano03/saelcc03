#include <bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 100 //cnt de nodos del problema
int n,m,q,t;
int pd[maxn], rnk[maxn];
struct edge{
    int u,v,w;
    edge(int _u, int _v, int _w){
        u=_u; v=_v;w=_w;
    }
    bool operator < (edge aux) const{
        return w< aux.w;
    }
};
void init(int n){
    for (int i = 0; i < n; i++) {
        pd[i]=i;
        rnk[i]=0;
    }
}
int find(int u){
    if(pd[u]==u)return u;
    return pd[u]=find(pd[u]);
}
void unionSets(int u, int v){
    u=find(u); v=find(v);
    if(u==v)return;
    if(rnk[u]<rnk[v])swap(u,v); // para que siempre el rank de u sea mayor que v
    pd[v]=u;
    if(rnk[u]==rnk[v])rnk[u]++;
}
int32_t main() {
    int u,v,w;
    vector<edge>E;
    cin>>n>>m;
    init(n);
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        u--,v--;
        E.push_back(edge(u,v,w));
    }
    sort(E.begin(), E.end());
    int mst=0;
    for(int i=0;i<m;i++){
        u=E[i].u, v=E[i].v, w=E[i].w;
        if(find(u)!=find(v)){
            unionSets(u,v);
            mst+=w;
        }
    }
	cout<<mst<<endl;

	return 0;
}
//hi
