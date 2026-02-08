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
#define yesi ps("YES")
#define nosi ps("NO")
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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int l, int r){
  return uniform_int_distribution<int>(l,r)(rng);
}
struct node{
  int val,pri,siz,id;
  node* l,*r,*par;
  node(int val):val(val),pri(random(1,1e9)){
    l=r=par=nullptr; siz=1;
  }
  node(int val, int pri, int id): val(val), pri(pri), id(id){
    l=r=par=nullptr; siz=1;
  }
  void update(){
    siz = 1 + (l?l->siz:0) + (r?r->siz:0);
  }
  void inOrd(vector<node*>& v, node* e){
    if(!e)return;
    inOrd(v,e->l);
    v.pb(e);
    inOrd(v,e->r);
  }
};
int siz(node* t){
  return (t?t->siz:0);
}
void solve(int caso){
  read(n);
  viii v(n); 
  fori(i,n){
    int val,key; read(val,key);
    v[i] = {val,key,i};
  }
  sort(all(v));
  vector<node*>u;
  for(auto [val,key,i]: v)u.pb(new node(val,key,i));
  node *t = nullptr;
  deque<node*>st;
  for(node* cur: u){
    node* last = nullptr;
    while(!st.empty() and st.back()->pri > cur->pri){
      last = st.back(); st.pop_back();
    }
    if(!st.empty()){
      st.back()->r = cur;
      cur->par = st.back();
    }
    if(last){
      cur->l = last;
      last->par = cur;
    }
    st.push_back(cur);
  }
  vector<node*> ax; st.front()->inOrd(ax, st.front());
  fori(i,n){
    if(ax[i]->val!=get<0>(v[i]))return nosi;
  }
  yesi;
  viii ans(n);
  for(node* e: ax){
    ans[e->id] = {(e->par?e->par->id+1:0), (e->l?e->l->id+1:0), (e->r?e->r->id+1:0)};
  }
  for(auto [a,b,c]: ans) ps(a,b,c);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

