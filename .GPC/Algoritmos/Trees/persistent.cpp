/***--_saelcc03_--***/

#include<bits/stdc++.h>
using namespace std;

#define fori(i,n) for(int i=0;i<n;i++)
#define fore(i,n) for(int i=1;i<=n;i++)
#define fora(i,n) for(int i=n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<b;i++)
#define int long long
#define inf 1e9
#define INF 1e18
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pair<int,int>>
#define viii vector<tuple<int,int,int>>
#define vvi vector<vector<int>>
#define vvii vector<vector<pair<int,int>>>
#define vviii vector<vector<tuple<int,int,int>>>
#define vvvi vector<vector<vector<int>>>
#define vb vector<bool>
#define vs vector<string>
#define si set<int>
#define mpii map<int,int>
#define pb push_back
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(x) x.size()
#define yesi cout<<"Yes"<<'\n'
#define nosi cout<<"No"<<'\n'
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
struct Node{
  Node *nl, *nr;
  int val, l, r;
  Node(int val, Node* nl, Node* nr, int l, int r): nl(nl), nr(nr),val(val),l(l),r(r){}
};
struct PersistentST{
  vi arr;
  int cte;
  vector<Node*>ver;
  // Node* root(0,nullptr,nullptr,0,n-1);  
  function<int(int,int)> fx;
  PersistentST(vi v, int cte, function<int(int,int)>fx):arr(v),cte(cte),fx(fx){
    // ver.pb(new Node(0,nullptr,nullptr,0,n-1));
    ver.pb(build(0, n-1));
  }

  Node* build(int l, int r){
    if(l==r) return new Node(arr[l],nullptr,nullptr,l,r);
    int mi = (l+r)/2;
    Node*nl = build(l,mi);
    Node*nr = build(mi+1,r);
    return new Node(fx(nl->val,nr->val),nl,nr,l,r);
  }

  Node* update(Node* root, int val, int pos){
    if(root->l==root->r)return new Node(val,nullptr,nullptr,root->l, root->r);
    Node *l, *r;
    int mi = (root->l + root->r)/2;
    if(pos<=mi){
      l = update(root->nl, val, pos);
      r = root->nr;
    }else{
      l = root->nl;
      r = update(root->nr,val, pos);
    }
    return new Node(fx(l->val,r->val),l,r,root->l,root->r);
  }
  void copy(int k){
    ver.pb(ver[k-1]);
  }
  int query(Node* root, int l, int r){
    if(root->r < l or root->l > r) return 0;
    if(l<=root->l and root->r <=r) return root->val;
    return fx(query(root->nl, l, r), query(root->nr, l, r));
  }
};
void solve(int caso){
  read(n,m);
  vi v(n); read(v);
  PersistentST pst(v,0,[](int a, int b){return a+b;});
  
  while(m--){
    int c,k,a,b,x; read(c);
    if(c==1){
      read(k,a,x);
      pst.ver[k-1] = pst.update(pst.ver[k-1],x,a-1);
    }
    if(c==2){
      read(k,a,b);
      ps(pst.query(pst.ver[k-1],a-1,b-1));
    }
    if(c==3){
      read(k);
      pst.copy(k);
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


