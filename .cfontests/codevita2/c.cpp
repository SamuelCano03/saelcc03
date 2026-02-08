/***--_saelcc03_--***/

#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.cpp"
#else
#define dbg(...)
#endif

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multi_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

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
#define yesi ps("Yes")
#define nosi ps("No")
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

void solve(int caso){
  read(n,m);
  vvi mat(n,vi(m));
  fori(i,n){
    fori(j,m)read(mat[i][j]);
  }
  int tg;read(tg);
  vii c;
  fori(i,n)fori(j,m){
    if(mat[i][j]==tg)c.pb({i,j});
  }
  int ans = 0;
  string pos = "up";
  //  up 
  bool fg = true;
  si st;
  for(auto [i,j]: c) if(i>0 and mat[i-1][j]!=tg)st.insert(mat[i-1][j]);
  si ax=st;
  while(true){
    fori(i,n)fori(j,m){
      if(st.find(mat[i][j])!=st.end()){
        if(i>0 and mat[i-1][j]!=tg)ax.insert(mat[i-1][j]);
      }
    }
    if(ax==st)break;
    st = ax;
  }
  ans = accumulate(all(st),0ll);
  //  down
  st = si();
  for(auto [i,j]: c) if(i+1<n and mat[i+1][j]!=tg)st.insert(mat[i+1][j]);
  ax = st;
  while(true){
    fori(i,n)fori(j,m){
      if(st.find(mat[i][j])!=st.end()){
        if(i+1<n and mat[i+1][j]!=tg)ax.insert(mat[i+1][j]);
      }
    }
    if(ax==st)break;
    st = ax;
  }
  if(ans>accumulate(all(st),0ll)) {
    ans = accumulate(all(st),0ll);
    pos = "down";
  }
  //  left
  st = si();
  for(auto [i,j]: c) if(j>0 and mat[i][j-1]!=tg)st.insert(mat[i][j-1]);
  ax = st;
  while(true){
    fori(i,n)fori(j,m){
      if(st.find(mat[i][j])!=st.end()){
        if(j>0 and mat[i][j-1]!=tg)ax.insert(mat[i][j-1]);
        if(i>0 and mat[i-1][j]!=tg)ax.insert(mat[i-1][j]);
      }
    }
    if(ax==st)break;
    st = ax;
  }
  if(ans>accumulate(all(st),0ll)) {
    ans = accumulate(all(st),0ll);
    pos = "left";
  }
  //  right
  st = si();
  for(auto [i,j]: c) if(j>0 and mat[i][j-1]!=tg)st.insert(mat[i][j-1]);
  ax = st;
  while(true){
    fori(i,n)fori(j,m){
      if(st.find(mat[i][j])!=st.end()){
        if(j+1<m and mat[i][j+1]!=tg)ax.insert(mat[i][j+1]);
        if(i>0 and mat[i-1][j]!=tg)ax.insert(mat[i-1][j]);
      }
    }
    if(ax==st)break;
    st = ax;
  }
  if(ans>accumulate(all(st),0ll)) {
    ans = accumulate(all(st),0ll);
    pos = "right";
  }
  cout<<ans<<" via "<<pos;
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

