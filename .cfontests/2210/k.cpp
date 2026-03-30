
/***--_saelcc03_--***/

#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.cpp"
#else
#define dbg(...)
#endif

#define fori(i,n) for(int i=0;i<(int)n;i++)
#define fore(i,n) for(int i=1;i<=(int)n;i++)
#define fora(i,n) for(int i=(int)n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<(int)b;i++)
// #define int long long
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
const int mxn = 1e6*30;
int trie[mxn][2];
int cnt[mxn];
int nodos = 1;
void add(int e){
  int cur = 0;
  fora(i,30){
    int bit = (e>>i) & 1;
    if(!trie[cur][bit]) trie[cur][bit]=nodos++;
    cur = trie[cur][bit];
    cnt[cur]++;
  }
}
void solve(int caso){
  // memset(trie,0,sizeof trie);
  // memset(cnt,0,sizeof cnt);
  read(n,m);
  vi v(n); read(v);
  vi w = v;
  fore(i,n-1)w[i] ^= w[i-1];
  add(0);
  long long ans = 0;
  m--;
  // dbg(n,m,v);
  for(int e: w){
    int cur = 0;
    fora(i,30){
      int bit = (e>>i) & 1;
      int bitk =(m>>i) & 1;
      if(bitk==0){
        if(trie[cur][bit^1]) ans += cnt[trie[cur][bit^1]];
        if(!trie[cur][bit])break;
        cur = trie[cur][bit];
      } 
      else{
        if(!trie[cur][bit^1])break;
        cur = trie[cur][bit^1];
      }
    }
    add(e);
  }
  ps(ans);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

