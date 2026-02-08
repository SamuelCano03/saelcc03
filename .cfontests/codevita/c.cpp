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

int tc=1,n,m,t,l;
struct clue{
  int t,x1,y1,x2,y2;
  clue(int t, int x1, int y1, int x2, int y2):t(t),x1(x1),y1(y1),x2(x2),y2(y2){}
};
bool fx(clue a, clue b){
  return a.t< b.t;
}
vector<vector<char>>v;
set<string>sans;
void check(int pos, vector<si>&pro,int idt, vi &vis){
  if(idt==t-1){
    if(find(all(vis),pos)!=vis.end())return;
    vis.push_back(pos);
    string nas = "";
    for(int e: vis){
      int i = e/n;
      int j = e%m;
      nas.pb(v[i][j]);
    }
    sans.insert(nas);
    vis.pop_back();
    return;
  }
  if(find(all(vis),pos)!=vis.end())return;
  vis.pb(pos);
  si st;
  int top = pos + m;
  int bot = pos - m;
  int lef = pos-1;
  int rih = pos+1;
  if(top<n*m){if(pro[idt+1].count(top)) check(top,pro,idt+1,vis);}
  if(bot>=0){if(pro[idt+1].count(bot)) check(bot,pro,idt+1,vis);}
  if(lef%m!=m-1){if(pro[idt+1].count(lef)) check(lef,pro,idt+1,vis);}
  if(rih%m!=0){if(pro[idt+1].count(rih)) check(rih,pro,idt+1,vis);}
  vis.pop_back();
}
void solve(int caso){
  read(n,m);
  v =   vector<vector<char>>(n,vector<char>(m,' '));
  fori(i,n)read(v[i]);
  read(t,l);
  vector<clue>cl;
  fori(i,l){
    int t,a,b,c,d;
    read(t,a,b,c,d);
    t--;a--,b--,c--,d--;
    cl.pb(clue(t,a,b,c,d));
  }
  sort(all(cl),fx);
  vector<si>pro(t);
  si st;
  fori(i,n*m)st.insert(i);
  fori(i,t)pro[i] = st;
  for(auto [th,a,b,c,d]: cl){
    for(int i=a;i<=c;i++){
      for(int j=b;j<=d;j++){
        int pos = i*m + j;
        pro[th].erase(pos);
      }
    }
    if(sz(pro[th])==0)return pr("Not enough clues");
  }
  // for(auto e: pro)dbg(e);
  if(t==1 and sz(pro[0])>1) return pr("Not enough clues");
  si ini = pro[0];
  vi vis;
  fori(i,n)fori(j,m)if(pro[0].count(i*m+j))check(i*m+j,pro,0,vis);
  // for(auto e: sans)dbg(e);
  // dbg(sz(sans));
  if(sz(sans)!=1) return pr("Not enough clues");
  string nas = *sans.begin();
  cout<<nas;
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

