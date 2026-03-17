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
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int l, int r){
  return uniform_int_distribution<int>(l,r)(rng);
}
struct node{
  int val, pri, siz;
  node* left,*right;
  node(int val):val(val),pri(random(0,1e9)),siz(1){
    left = right = nullptr;
  }
  void update(){
    siz = 1 + (left==nullptr?0:left->siz) + (right==nullptr?0:right->siz);
  }
};

int siz(node* t){return t?t->siz:0;}

struct treap{
  node* root=nullptr;
  node* merge(node* l, node* r){
    if(l==nullptr) return r;
    if(r==nullptr)return l;
    if(l->pri>r->pri){
      l->right = merge(l->right,r);
      l->update();
      return l;
    }else{
      r->left = merge(l,r->left); 
      r->update();
      return r;
    }
  }
  pair<node*,node*> split(node* t, int k){
    if(t==nullptr)return {nullptr,nullptr};
    if(t->val>k){
      pair<node*,node*>p = split(t->left,k);
      t->left = p.second;
      t->update();
      return {p.first,t};
    }else{
      pair<node*,node*>p = split(t->right,k);
      t->right = p.first;
      t->update();
      return {t,p.second};
    }
  }
  void insert(int val){
    pair<node*,node*>p = split(root,val);
    root = merge(p.first,new node(val));
    root = merge(root,p.second);
  }
  void remove(int val){
    pair<node*,node*>p = split(root,val);
    pair<node*,node*>p2 = split(p.first,val-1);
    root = merge(p2.first,p.second);
  }
  node* isPresent(int val){
    node* ax = root;
    while(ax!=nullptr){
      if(ax->val == val) return ax;
      if(ax->val <  val) ax = ax->right;
      else if(ax->val >  val) ax = ax->left;
    }
    return nullptr;
  }
  int countSmaller(node* ax, int val){
    if(!ax)return 0;
    if(ax->val==val)return siz(ax->left);
    if(val<ax->val)return countSmaller(ax->left, val);
    return siz(ax->left) + 1 + countSmaller(ax->right, val);
  }
  int getKthIn(node* t, int k){
    if(!t) return -1;
    int lft_sz = (t->left? t->left->siz:0);
    if(k<lft_sz) return getKthIn(t->left, k);
    else if(k==lft_sz)return t->val;
    else return getKthIn(t->right,k-lft_sz-1);
  }
  int getKth(int val){ // indexed in 1
    return getKthIn(root, val-1);
  }
};
void solve(int caso){
  treap tp;
  read(n,m);
  fori(i,m){
    char c; int val; read(c,val);
    int lo =0, hi =1e9+1;
    while(lo<hi){ // fffffvvvv
      int mi = lo+(hi-lo)/2;
      int cnt2 = tp.countSmaller(tp.root, mi+1);
      if(mi - cnt2 >=val) hi=mi;
      else lo=mi+1;
    }
    if(c=='L'){
      ps(lo);
    }
    else{
      // dbg("is",lo);
      tp.insert(lo);
    }
  }
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

