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
struct mydata{
  int pre, suf, ans, sum;
  mydata(){
    pre =  suf = sum = 0;
    ans = INT_MIN;
  }
  mydata(int x){
    ans=pre=suf=sum=x;
  }
  mydata operator+(const mydata&rhs) const {
    mydata q(0);
    q.ans = max({ans,rhs.ans, suf + rhs.pre});
    q.pre = max(pre,sum+rhs.pre);
    q.suf = max(rhs.suf, rhs.sum+suf);
    q.sum = sum + rhs.sum;
    return q;
  }
};

struct node{
  int val,pri,siz,sum,max;
  node*l,*r;
  mydata value, value_subtree;
  bool lazy=false;
  node(){l=r=nullptr;}
  node(int val):val(val),siz(1),sum(val),max(val),pri(random(1,1e9)),value(mydata(val)), value_subtree(mydata(val)){
    l=r=nullptr;
  }
};
int siz(node*t){return t?t->siz:0;}
int max(node*t){return t?t->max:0;}
int sum(node*t){return t?t->sum:0;}
mydata value_subtree(node* t){ return t?t->value_subtree: mydata();}

void sync(node*t){
  if(!t)return;
  t->siz = siz(t->l) + 1 + siz(t->r);
  t->max = max({max(t->l),t->val,max(t->r)});
  t->sum = sum(t->l) + t->val + sum(t->r);
  t->value_subtree= value_subtree(t->l) + t->value + value_subtree(t->r);
}
void push(node*t){
  if(!t)return;
  if(!t->lazy)return;
  swap(t->l,t->r);
  if(t->l) t->l->lazy ^= 1;
  if(t->r) t->r->lazy ^= 1;
  sync(t);
  t->lazy = false;
}
struct treap{
  node* root=nullptr;
  pair<node*,node*> split(node* t, int pos){ // {nodes < pos-th, nodes >= pos-th}
    if(!t) return {nullptr, nullptr};
    push(t);
    if(siz(t->l)<pos){
      auto p = split(t->r,pos - siz(t->l) - 1);
      t->r = p.first; sync(t);
      return {t,p.second};
    }
    else{
      auto p = split(t->l,pos);
      t->l = p.second; sync(t);
      return {p.first,t};
    }
  }
  node* merge(node *l, node* r){
    if(!l or !r) return (l?l:r);
    push(l); push(r);
    if(l->pri>r->pri){
      l->r = merge(l->r,r);
      sync(l);
      return l;
    }else{
      r->l = merge(l,r->l);
      sync(r);
      return r;
    }
  }
  void insert(int pos, int val){
    auto a = split(root,pos);
    root = merge(a.first,new node(val));
    root = merge(root,a.second);
  }
  void remove(int pos){
    auto a = split(root,pos+1);
    auto b = split(a.first,pos);
    root = merge(b.first,a.second);
  }
  void reverse(int l, int r){
    if(l>=r)return;
    pair<node*,node*> p = split(root,r+1);
    pair<node*,node*> q = split(p.first,l);
    q.second->lazy=true;
    push(q.second);
    root = merge(q.first,q.second);
    root = merge(root,p.second);
  }
  int getSum(int l, int r){
    if(l>r)return 0ll;
    pair<node*,node*>p = split(root,r+1);
    pair<node*,node*>q = split(p.first,l);
    int res = sum(q.second);
    root = merge(q.first,q.second);
    root = merge(root,p.second);
    return res;
  }
  void query(int l, int r){ // max contiguous non empty sum in interval [l,r] 0-idx (SPOJ - GSS6)
    pair<node*,node*> a = split(root,r+1);
    pair<node*,node*> b = split(a.first,l);
    int res = value_subtree(b.second).ans;
    root = merge(b.first,b.second);
    root = merge(root,a.second);
    ps(res);
  }
  int kth(int k){
    node * res = kth(root,k);
    return res?res->val:-1;
  }
  void DFS(){
    DFS(root);
  }
private:
  node* kth(node *t, int k){
    if(!t) return nullptr;
    if(k<siz(t->l)) return kth(t->l,k);
    else if(siz(t->l) == k) return t;
    else return kth(t->r,k-siz(t->l)-1);
  }
  void DFS(node *t){
    if(!t)return;
    DFS(t->l);
    ps(t->val,t->l?t->l->val:-1,t->r?t->r->val:-1);
    // pr(t->val,' ');
    DFS(t->r);
  }
};
void solve(int caso){
  read(n,m);
  treap tp;
  fori(i,n){
    int x; read(x);
    tp.insert(i, x);
  }
  while(m--){
    int x,l,r;
    read(x,l,r);
    // l--,r--;
    if(!x) tp.reverse(l, r-1);
    else ps(tp.getSum(l, r-1));
  }
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

