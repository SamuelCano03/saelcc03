/***--_saelcc03_--***/
// https://cses.fi/problemset/task/1685
#include<bits/stdc++.h>
using namespace std;

#define fori(i,n) for(int i=0;i<(int)n;i++)
#define fore(i,n) for(int i=1;i<=(int)n;i++)
#define fora(i,n) for(int i=(int)n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<(int)b;i++)
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
#define sz(x) (int)x.size()
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
struct SCC{
  vvi G, G1, G2;
  vi dfn, low, cmp, stk, rut, ind, oud;
  vii E;
  vb instk, vis, vis1, inmat;
  int top=0, cnt=0;
  SCC(int n, vvi G, vii E):G(G), E(E){
    dfn = low = cmp = stk = rut = vi(n+1);
    instk = vb(n+1);
    fore(u,n) if(!dfn[u]) tarjan(u);
  }
  void tarjan(int u){
    dfn[u] = low[u] = ++dfn[0];
    stk[++top] = u;
    instk[u] = true;
    for(int v: G[u]){
      if(!dfn[v]) tarjan(v);
      if(instk[v]) low[u] = min(low[u],low[v]);
    }
    if(dfn[u]==low[u]){
      rut[++cnt] = u;
      do{
        cmp[stk[top]] = cnt;
        instk[stk[top]] = false;
      } while(stk[top--]!=u);
    }
  }
  void denseGraphs(){
    G1 = G2 = vvi(cnt+1);
    ind = oud = vi(cnt+1);
    for(auto [u,v]: E){
      if(cmp[u]==cmp[v])continue;
      G1[cmp[u]].pb(cmp[v]); G2[cmp[v]].pb(cmp[u]);
      oud[cmp[u]]++; ind[cmp[v]]++;
    }
  }
};
void solve(int caso){
  read(n,m);
  vvi G(n+1);
  vii E,mat,ans;
  vi S, T;
  fore(i,m){
    int u,v; read(u,v);
    G[u].pb(v);
    E.pb({u,v});
  }
  SCC tj(n,G,E);
  if(tj.cnt==1) return ps(0);
  tj.denseGraphs();
  fore(i,tj.cnt){
    if(tj.ind[i]==0)S.pb(i);
    if(tj.oud[i]==0)T.pb(i);
  }
  vb inmat(tj.cnt+1), vis(tj.cnt+1);
  function<int(int, vvi&, vi&)> dfs = [&](int u, vvi &G, vi &deg){
    if(vis[u])return 0ll;
    vis[u] = true;
    int ret = 0;
    if(deg[u]==0 and !inmat[u]) ret=u;
    for(int v: G[u])
        if(int t = dfs(v,G,deg))ret=t;
    return ret;
  };
  for(int u: S){
    int v = dfs(u,tj.G1,tj.oud);
    if(!v) continue;
    mat.pb({u,v});
    inmat[u] = inmat[v] = true;
  }
  vis = vb(tj.cnt+1);
  for(int v: T){
    if(inmat[v])continue;
    int u = dfs(v,tj.G2,tj.ind);
    if(!u)continue;
    mat.pb({u,v});
    inmat[u] = inmat[v] = true;
  }
  fori(i,sz(mat)) ans.pb({mat[i].ss, mat[(i+1)%sz(mat)].ff});
  auto pS = S.begin(), pT = T.begin();
  while(true){
    while(pS != S.end() and inmat[*pS]) pS++;
    while(pT != T.end() and inmat[*pT]) pT++;
    if(pS == S.end() and pT == T.end()) break;
    int u = (pS == S.end() ? *S.begin() : *pS);
    int v = (pT == T.end() ? *T.begin() : *pT);
    inmat[u] = inmat[v] = true;
    ans.pb({v,u});
  }
  ps(sz(ans));
  for(auto [u,v]: ans) ps(tj.rut[u],tj.rut[v]);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  /*read(tc); */
  fore(caso, tc){
    solve(caso);
  }
}

