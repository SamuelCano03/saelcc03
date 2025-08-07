/***--_saelcc03_--***/

#include <algorithm>
#include<bits/stdc++.h>
using namespace std;

#define fori(i,n) for(int i=0;i<n;i++)
#define fore(i,n) for(int i=1;i<=n;i++)
#define fora(i,n) for(int i=n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<b;i++)
#define int long long
#define inf 1e9
#define INF 1e18
#define pii pair<int,int>
#define piii tuple<int,int,int>
#define vi vector<int>
#define vii vector<pii>
#define viii vector<piii>
#define vvi vector<vi>
#define vvii vector<vii>
#define vviii vector<viii>
#define vvvi vector<vvi>
#define vb vector<bool>
#define vs vector<string>
#define si set<int>
#define mpii map<int,int>
#define pb push_back
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(x) x.size()
#define yesi cout<<"Yes"<<'\n'
#define nosi cout<<"No"<<'\n'
#define endl '\n'
#define approx(a) fixed << setprecision(a)
#define ff first
#define ss second
#define fast read(n); vi v(n); read(v)
// reading your mind
template <class T> void read(vector<T> &v);
template <class F, class S> void read(pair<F, S> &p);
template <class T> void read(T &x) {cin >> x;}
template <class T> void read(vector<T> &v) {for(auto& x : v) read(x);}
template <class R, class... T> void read(R& r, T&... t){read(r); read(t...);};
template <class F, class S> void read(pair<F, S> &p) {read(p.ff, p.ss);}
// puking your feelings
template <class T> void ps(vector<T> &v);
template <class F, class S> void pr(const pair<F, S> &x);
template <class T> void pr(const T &x) {cout << x;}
void ps() {pr("\n");}
template <class R, class... T> void pr(const R& r, const T&... t) {pr(r); pr(t...);}
template <class F, class S> void pr(const pair<F, S> &x) {pr("{", x.ff, ", ", x.ss, "}\n");}
template <class T> void ps(vector<T> &v) {for(auto& x : v) pr(x, ' '); ps();}
template <class T> void ps(set<T> &v) {for(auto& x : v) pr(x, ' '); ps();}
template <class T> void ps(const T &x) {pr(x); ps();}
template <class R, class... T> void ps(const R& r,  const T &...t) {pr(r, ' '); ps(t...);}

int tc=1,n,m;
void dfs(int u, vvi & adj, vi & order, vb & vis){
  vis[u] = true;
  for(int v: adj[u]){
    if(!vis[v])dfs(v,adj,order,vis);
  }
  order.pb(u);
}
void scc(vvi & adj, vvi & comp, vvi & cond, vi & roots){
  vvi jda(n);
  fori(u,n)for(int v: adj[u])jda[v].pb(u);
  vi order; // vertices order by exit time (topo sort)
  vb vis(n);
  fori(i,n)
    if(!vis[i])dfs(i,adj,order,vis);
  reverse(all(order));
  vis = vb(n);
  for(int u: order){
    if(vis[u])continue;
    vi out;
    dfs(u,jda,out,vis);
    comp.pb(out);
    int root = *min_element(all(out)); // can change
    for(int v: out)roots[v] = root;
  }
  fori(u,n)
    for(int v: adj[u])
      if(roots[u]!=roots[v])cond[roots[u]].pb(roots[v]);
}
void solve(int caso){
  read(n,m);
  vi roots(n);
  vvi adj(n),comp,cond(n);
  fori(i,m){
    int u,v; read(u,v);
    u--;v--;
    adj[u].pb(v);
  }
  scc(adj,comp,cond,roots);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  /*read(tc); */
  fore(caso, tc){
    solve(caso);
  }
}

