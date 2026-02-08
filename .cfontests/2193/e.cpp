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
vi primes;
vb isPrime(1e6,true);
vi spf(1e6);
void criba(){
  fori(i,1e6)spf[i]=i;
  isPrime[0]=isPrime[1]=false;
  for(int i=2;i<1e6;i++){
    if(!isPrime[i])continue;
    primes.pb(i);
    for(int j=2*i;j<1e6;j+=i){
      isPrime[j]=false;
      if(spf[j]==j)spf[j]=i;
    }
  }
}

int tc=1,n,m;
vi fact(int x){
  vi ret;
  while(x>1)ret.pb(spf[x]), x/=spf[x];
  return ret;
}
int fx(int tg, vi&is, vi &v){
  vi f = fact(tg);

  return 0;
}
void solve(int caso){
  fast;
  si ts; vi st;
  for(int e: v)if(e!=1)ts.insert(e);
  for(int e: ts)st.pb(e);
  vi dis(n+1,-1);
  dis[1]=0;
  queue<int>q;
  q.push(1);
  while(q.size()){
    int u = q.front();
    q.pop();
    for(int e: st){
      int num = u*e;
      if(num>n)break;
      if(dis[num]!=-1)continue;
      dis[num] = dis[u]+1;
      q.push(num);
    }
  }
  if(find(all(v),1)!=v.end())dis[1]=1;
  else dis[1]=-1;
  fore(i,n)cout<<dis[i]<<' ';ps();
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

