/***--_saelcc03_--***/

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
#define vvii vector<vector<pair<int,int>>>
#define vvvi vector<vector<vector<int>>>
#define vb vector<bool>
#define vs vector<string>
#define si set<int>
#define mpii map<int,int>
#define pb push_back
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(x) x.size()
#define yesi cout<<"YES"<<'\n'
#define nosi cout<<"NO"<<'\n'
#define endl '\n'
#define approx(a) fixed << setprecision(a)
#define ff first
#define ss second
#define fast read(n); vi v(n); read(v)
template <class T> void read(vector<T> &v);
template <class F, class S> void read(pair<F, S> &p);
template <class T> void read(T &x) {cin >> x;}
template <class T> void read(vector<T> &v) {for(auto& x : v) read(x);}
template <class R, class... T> void read(R& r, T&... t){read(r); read(t...);};
template <class F, class S> void read(pair<F, S> &p) {read(p.ff, p.ss);}

template <class T> void ps(vector<T> &v);
template <class F, class S> void pr(const pair<F, S> &x);
template <class T> void pr(const T &x) {cout << x;}
void ps() {pr("\n");}
template <class R, class... T> void pr(const R& r, const T&... t) {pr(r); pr(t...);}
template <class F, class S> void pr(const pair<F, S> &x) {pr("{", x.ff, ", ", x.ss, "}\n");}
template <class T> void ps(vector<T> &v) {for(auto& x : v) pr(x, ' '); ps();}
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

void solve(){
  vi v = {3,2,4,1};
  SegmentTree seg(v,1e9,[](int a, int b){return min(a,b);});
  int q;
  cin>>q;
  while(q--){
    int a,b,c;
    cin>>a>>b>>c;
    if(a%2)seg.update(b,c);
    else cout<<seg.query(b,c)<<endl;
  }
}
int32_t main(){
  solve();
}
