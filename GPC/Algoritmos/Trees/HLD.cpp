#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
#define fori(i,n) for(int i=0;i<n;i++)
#define fore(i,n) for(int i=1;i<=n;i++)
#define fora(i,n) for(int i=n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<b;i++)
#define int long long
#define limit LLONG_MAX
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vii vector<pair<int,int>>
#define vb vector<bool>
#define vs vector<string>
#define si set<int>
#define mpii map<int,int>
#define pb push_back
#define all(v) v.begin(),v.end()
#define sz(x) x.size()
#define yesi cout<<"Yes"<<'\n'
#define nosi cout<<"No"<<'\n'
#define endl '\n'
#define approx(a) fixed << setprecision(a)
#define ff first
#define ss second
#define fast read(n); vi v(n); read(v)
template <class T> void read(vector<T> &v);
template <class F, class S> void read(pair<F, S> &p);
template <class T, size_t Z> void read(array<T, Z> &a);
template <class T> void read(T &x) {cin >> x;}
template <class R, class... T> void read(R& r, T&... t){read(r); read(t...);};
template <class T> void read(vector<T> &v) {for(auto& x : v) read(x);}
template <class F, class S> void read(pair<F, S> &p) {read(p.ff, p.ss);}
template <class T, size_t Z> void read(array<T, Z> &a) { for(auto &x : a) read(x); }

template <class F, class S> void pr(const pair<F, S> &x);
template <class T> void pr(const T &x) {cout << x;}
template <class R, class... T> void pr(const R& r, const T&... t) {pr(r); pr(t...);}
template <class F, class S> void pr(const pair<F, S> &x) {pr("{", x.ff, ", ", x.ss, "}\n");}
void ps() {pr("\n");}
template <class T> void ps(const T &x) {pr(x); ps();}
template <class T> void ps(vector<T> &v) {for(auto& x : v) pr(x, ' '); ps();}
template <class T, size_t Z> void ps(const array<T, Z> &a) { for(auto &x : a) pr(x, ' '); ps(); }
template <class F, class S> void ps(const pair<F, S> &x) {pr(x.ff, ' ', x.ss); ps();}
template <class R, class... T> void ps(const R& r,  const T &...t) {pr(r, ' '); ps(t...);}

int tc=1,n,m,t,q, curpos;
vi st, ar, parent, head, heavy, depth, pos;
vvi adj;

// Segment tree operations
int fx(int a, int b){return a+b;}

void update(int id, int val){
  int node = id + n;
  for(st[node]=val; node>1; node>>=1)st[node>>1] = fx(st[node], st[node^1]);
}

int query(int l, int r){
  int ret = 0;
  for(l+=n, r+=n+1; l<r; l>>=1, r>>=1){
    if(l%2) ret = fx(ret, st[l++]);
    if(r%2) ret = fx(ret, st[--r]);
  }
  return ret;
}

// HLD functions
int dfs_sz(int u){
  int sz = 1, mx_sz = 0, cur_sz;
  for(int v: adj[u]){
    if(parent[u]==v) continue;
    parent[v] = u;
    depth[v] = depth[u] + 1;
    cur_sz = dfs_sz(v);
    sz += cur_sz;
    if(mx_sz < cur_sz){mx_sz = cur_sz; heavy[u] = v;}
  }
  return sz;
}
void dfs_hld(int u, int h){
  head[u] = h;
  pos[u] = curpos++;
  update(pos[u], ar[u]);
  if(heavy[u]!=-1) dfs_hld(heavy[u],h);
  for(int v: adj[u]){
    if(parent[u]!=v and heavy[u]!=v) dfs_hld(v, v);
  }
}

int query_hld(int a, int b){
  int ret = 0;
  for(;head[a]!=head[b]; b=parent[head[b]]){
    if(depth[head[a]]>depth[head[b]])swap(a,b);
    ret = fx(ret, query(pos[head[b]], pos[b]));
  }
  if(depth[a]>depth[b])swap(a,b);
  return fx(ret, query(pos[a],pos[b]));
}
void init(){
  curpos = 0;
  parent=head=depth=pos=vi(n);
  heavy = vi(n,-1);
  st = vi(2*n);
  dfs_sz(0);
  dfs_hld(0,0);
}

void solve(){
  read(n,q);
  ar = vi(n);
  adj = vvi(n);
  read(ar);
  fori(i,n-1){
    int a,b; read(a,b); a--; b--;
    adj[a].pb(b); adj[b].pb(a);
  }
  init();
  int a,b,c;
  while(q--){
    read(a);
    if(a==1){
      read(b,c);
      update(pos[b-1],c);
      continue;
    }
    read(b);
    ps(query_hld(0,b-1));
  }
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  /*read(tc); */
  while(tc--){
    solve();
  }
}
