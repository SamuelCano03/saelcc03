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

struct ordered_multiset { // multiset supporting duplicating values in set
  int len = 0;
  const int ADD = 1000010;
  const int MAXVAL = 1000000010;
  unordered_map<int, int> mp; // hash = 96814
  tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> T;

  ordered_multiset() { len = 0; T.clear(), mp.clear(); }

  inline void insert(int x){
    len++, x += MAXVAL;
    int c = mp[x]++;
    T.insert((x * ADD) + c); }

  inline void erase(int x){
    x += MAXVAL;
    int c = mp[x];
    if(c) {
      c--, mp[x]--, len--;
      T.erase((x*ADD) + c); } }

  inline int kth(int k){        // 1-based index,  returns the
    if(k<1 || k>len) return -1;     // K'th element in the treap,
    auto it = T.find_by_order(--k); // -1 if none exists
    return ((*it)/ADD) - MAXVAL; } 

  inline int lower_bound(int x){      // Count of value <x in treap
    x += MAXVAL;
    int c = mp[x];
    return (T.order_of_key((x*ADD)+c)); }

  inline int upper_bound(int x){      // Count of value <=x in treap
    x += MAXVAL;
    int c = mp[x];
    return (T.order_of_key((x*ADD)+c)); }

  inline int size() { return len; }   // Number of elements in treap
};
int tc=1,n,m;

void solve(int caso){
  read(n,m);
  vi a(n);
  vii b(m),c,d,e;
  read(a);
  fori(i,m)read(b[i].ff);
  fori(i,m)read(b[i].ss);
  fori(i,m){
    if(b[i].ss==0)d.pb(b[i]);
    else if(b[i].ff<=b[i].ss)c.pb(b[i]);
    else e.pb(b[i]);
  }
  ordered_multi_set<int> st;
  for(int e: a)st.insert(e);
  sort(all(c),[](pii a, pii b){if(a.ff==b.ff){return a.ss>b.ss;} return a.ff<b.ff; });
  sort(all(e),[](pii a, pii b){if(a.ff==b.ff){return a.ss>b.ss;} return a.ff<b.ff; });
  int ans=0;
  // dbg(c);
  // dbg(e);
  // dbg(d);
  for(auto [x,y]: c){
    int k = st.order_of_key(x);
    auto it = st.find_by_order(k);
    if(it==st.end())continue;
    // dbg(k,*it,x,y);
    int val = *it;
    st.erase(it);
    st.insert(max(y,val));
    ans++;
  }
  for(auto [x,y]: e){
    int k = st.order_of_key(x);
    auto it = st.find_by_order(k);
    if(it==st.end())continue;
    // dbg(k,*it,x,y);
    int val = *it;
    st.erase(it);
    st.insert(max(y,val));
    ans++;
  }

  for(auto [x,y]: d){
    int k = st.order_of_key(x);
    auto it = st.find_by_order(k);
    if(it==st.end())continue;
    // dbg(k,*it,x,y);
    st.erase(it);
    st.insert(y);
    ans++;
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

