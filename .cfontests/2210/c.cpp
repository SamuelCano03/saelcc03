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
#define inf 1e10
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

struct SegmentTree{
  int n,cte;
  function<int(int,int)> fx;
  vi v,st;
  SegmentTree(vi &v, int cte, function<int(int,int)> fx):v(v),cte(cte),fx(fx){
    n = v.size();
    st=vi(2*n+1,cte);
    fori(i,n)update(i,v[i]);
  }
  void update(int id, int vl){
    int node = id + n;
    for(st[node]=vl,v[id]=vl;node>1;node>>=1) st[node>>1] = fx(st[node],st[node^1]);
  }
  int query(int l, int r){
    int res = cte;
    for(l+=n,r+=n+1;l<r;l>>=1,r>>=1){
      if(l%2) res=fx(res,st[l++]);
      if(r%2) res=fx(res,st[--r]);
    }
    return res;
  }
};
void solve(int caso){
  read(n); vi a(n),b(n);
  read(a,b);
  SegmentTree seg(a,0,[](int a, int b){return __gcd(a,b);});
  int ans = 0;
  fori(i,n){
    int left = i>0?seg.query(i-1,i):1e10;
    int rigt = i+1<n?seg.query(i,i+1):1e10;
    // dbg(i,a[i],left,rigt);
    int cmp = 0;
    if(left==1e10)cmp = rigt;
    else if(rigt==1e10)cmp=left;
    else cmp = lcm(left,rigt);
    if(cmp!=a[i])ans++,a[i]=cmp;
  }
  ps(ans);
}

int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}














