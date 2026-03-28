/***--_saelcc03_--***/

#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include ".debug.cpp"
#else
#define dbg(...)
#endif

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
const int mxn = 100001;
int trie[mxn][26];
int cnt[mxn],kmp[mxn],chr[mxn], stp[mxn],dct[mxn];
int nodos = 1;
void add(string &s){
  chr[0]=-1;
  int cur = 0;
  for(char c: s){
    int e= c-'a';
    if(!trie[cur][e])trie[cur][e]=nodos++;
    cur = trie[cur][e];
    cnt[cur]++;
    chr[cur]=e;
  }
  stp[cur]=1;
}
void tkmp(){
  queue<int>q; 
  fori(i,26)if(trie[0][i])q.push(trie[0][i]);
  while(q.size()){
    int u = q.front(); q.pop();
    fori(i,26){
      if(!trie[u][i])continue;
      int v = trie[u][i];
      int len = kmp[u];
      while(len>0 and !trie[len][i])len=kmp[len];
      len = trie[len][i]; //instead of len++ 
      kmp[v]=len;
      dct[v] = stp[len]?len:dct[len];
      q.push(v);
    }
  }
}
void pt(int node){
  int cur=0;

}
void solve(int caso){
  string s;
  read(n,s);
  vs v(n); read(v);
  for(string &e: v)add(e);
  tkmp();
  int cur = 0,ans=0;
  si st;
  for(char c: s){
    int e =c-'a';
    while(cur>0 and !trie[cur][e])cur = kmp[cur];
    cur = trie[cur][e];
    int ax = cur;
    while(ax){
      ans+=stp[ax];
      if(stp[ax])st.insert(ax);
      ax=dct[ax];
    }
  }
  ps(ans);
  ps(sz(st));
  dbg(st);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}














