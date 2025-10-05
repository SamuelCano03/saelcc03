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
  int val,pri,siz;
  node*l,*r;
  node(int val):val(val),siz(1),pri(random(1,1e9)){
    l=r=nullptr;
  }
  void update(){
    siz = 1 + (l?l->siz:0) + (r?r->siz:0);
  }
};
struct treap{
  node* root=nullptr;
  pair<node*,node*> split(node* t, int val){
    if(!t) return {nullptr, nullptr};
    if(t->val<=val){
      auto p = split(t->r,val);
      t->r = p.first; t->update();
      return {t,p.second};
    }else{
      auto p = split(t->l,val);
      t->l = p.second; t->update();
      return {p.first,t};
    }
  }
  node* merge(node *l, node* r){
    if(!l or !r) return (l?l:r);
    if(l->pri>r->pri){
      l->r = merge(l->r,r);
      l->update();
      return l;
    }else{
      r->l = merge(l,r->l);
      r->update();
      return r;
    }
  }
  void insert(int val){
    auto a = split(root,val);
    root = merge(a.first,new node(val));
    root = merge(root,a.second);
  }
  void remove(int val){
    auto a = split(root,val);
    auto b = split(a.first,val-1);
    root = merge(b.first,a.second);
  }
  int countLess(int val){
    return countLess(root,val);
  }
  int kth(int k){
    node * res = kth(root,k);
    return res?res->val:-1;
  }
  bool exists(int val){
    return countLess(val+1) - countLess(val) > 0;
  }
  int lower_bound(int val){
    return kth(countLess(val));
  }
private:
  node* kth(node *t, int k){
    if(!t) return nullptr;
    int lft_sz = (t->l?t->l->siz:0);
    if(k<lft_sz) return kth(t->l,k);
    else if(lft_sz == k) return t;
    else return kth(t->r,k-lft_sz-1);
  }
  int countLess(node *t,int val){
    if(!t) return 0;
    if(t->val<val) return 1+(t->l?t->l->siz:0) + countLess(t->r, val);
    else return countLess(t->l, val);
  }
};
void solve(int caso){

}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

