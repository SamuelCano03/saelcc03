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

vi kmp(string &s){
  int n = sz(s);
  vi pi(n);
  fore(i,n-1){
    int j= pi[i-1];
    while(j>0 and s[i]!=s[j])j=pi[j-1];
    if(s[i]==s[j])j++;
    pi[i]=j;
  }
  return pi;
}

string a,b; 
vvi match,dp; vi pi;
int comp(int ch, int k){
  int &ret = match[ch][k];
  if(ret!=-1)return ret;
  while(k>0 and b[k]-'a'!=ch){
    k=pi[k-1];
  }
  if(b[k]-'a'==ch)k++;
  return ret=k;

}
int cal(int i, int k){
  if(i==n)return 0;
  int &ret = dp[i][k];
  if(ret!=-1)return ret;
  if(a[i]!='?'){
    k=comp(a[i]-'a',k);
    if(k==m)ret = 1 + cal(i+1,pi[k-1]);
    else ret = cal(i+1,k);
  }
  else{
    fori(j,26){
      int nk = comp(j,k);
      if(nk==m)ret=max(ret,1+cal(i+1,pi[nk-1]));
      else ret = max(ret,cal(i+1,nk));
    }
  }
  return ret;
}
void solve(int caso){
  read(a,b);
  n=sz(a),m=sz(b);
  pi = kmp(b);
  dp=vvi(n,vi(m,-1)), match=vvi(26,vi(m,-1));
  ps(cal(0,0));
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}














