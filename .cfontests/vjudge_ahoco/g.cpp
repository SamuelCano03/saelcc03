/***--_saelcc03_--***/

// #include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<set>
#include<queue>
#include<stdio.h>
#include<string.h>
using namespace std;


#define fori(i,n) for(int i=0;i<(int)n;i++)
#define fore(i,n) for(int i=1;i<=(int)n;i++)
#define fora(i,n) for(int i=(int)n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<(int)b;i++)
#define int long long
#define inf 1e9
#define INF 1e18
#define vi vector<int>
#define vs vector<string>
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
const int mxn = 1000001;
const int abc = 27;
int trie[mxn][abc];
int cnt[mxn],kmp[mxn],chr[mxn], stp[mxn],dct[mxn],par[mxn];
int nodos = 1;
char inic = 'a';
int add(string &s){
  chr[0]=-1;
  int cur = 0;
  for(char c: s){
    int e= c-inic;
    if(!trie[cur][e])trie[cur][e]=nodos++;
    par[trie[cur][e]]=cur;
    cur = trie[cur][e];
    cnt[cur]++;
    chr[cur]=e;
  }
  stp[cur]=1;
  return cur;
}
void tkmp(){
  queue<int>q; 
  fori(i,abc)if(trie[0][i])q.push(trie[0][i]);
  while(q.size()){
    int u = q.front(); q.pop();
    fori(i,abc){
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
int dfs(int u, vi& dp){
    if(dp[u]!=-1)return dp[u];
    return dp[u] = stp[u] + max(dfs(par[u],dp),dfs(dct[u],dp));
}
#define mem(e) memset(e,0,sizeof e)
void solve(int caso){
  while(cin>>n){
    if(n==0)break;
    // mem(trie);mem(cnt);mem(kmp);mem(chr);mem(stp);mem(dct);mem(par);
    nodos = 1;
    vs v(n); read(v);
    for(string &s: v)add(s);
    tkmp();
    vi dp(nodos,-1);
    dp[0]=0;
    for(int i=1;i<nodos;i++){
        // if(!stp[i])continue;
        if(dp[i]!=-1)continue;
        dp[i] = dfs(i,dp);        
    }
    int mx = 0;
    for(int i=1;i<nodos;i++)mx =max(dp[i],mx);
    ps(mx);
    fori(i,nodos+1){
        cnt[i]=kmp[i]=chr[i]=stp[i]=dct[i]=par[i]=0;
        fori(j,abc)trie[i][j]=0;
    }
  }
  
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
//   read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}














