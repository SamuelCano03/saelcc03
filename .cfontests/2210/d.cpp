/***--_saelcc03_--***/

#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include ".debug.cpp"
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
#define gcd __gcd
void solve(int caso){
  read(n); vi a(n),b(n);
  read(a,b);
  int ans = 0;
  vi primes = {1,2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89};
  m = sz(primes);
  vvi dp(n,vi(m,-1e9));
  vi c(n);
  fori(i,n){
    int lf = i==0?  1:gcd(a[i-1],a[i]);
    int rt = i==n-1?1:gcd(a[i],a[i+1]);
    c[i] = lf*rt/gcd(lf,rt);
    if(c[i]>b[i])c[i]=a[i];
  }
  dp[0][0] = (c[0]==a[0]?0:1);
  fore(i,m-1){
    int val = c[0]*primes[i];
    if(val<=b[0] and gcd(val,c[1])==gcd(a[0],a[1]) and val!=a[0])dp[0][i]=1;
  }
  fore(i,n-1){
    fori(j,m){
      fori(k,m){
        if(j==0){// keep value unchanged 
          dp[i][j]=max(dp[i][j], dp[i-1][k] + (c[i]==a[i]?0:1));
          continue;
        }
        int val1 = c[i]*primes[j];
        int val2 = c[i-1]*primes[k];
        if(val1<=b[i] and gcd(val1,val2)==gcd(c[i-1],c[i]) and val1!=a[i]){
          if(i<n-1){
            if(gcd(val1,c[i+1])==gcd(c[i],c[i+1]))dp[i][j]=max(dp[i][j],dp[i-1][k]+1);
          }
          else dp[i][j]=max(dp[i][j],dp[i-1][k]+1);
        }
      }
    }
  }
  ps(max(0ll,*max_element(all(dp.back()))));
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}














