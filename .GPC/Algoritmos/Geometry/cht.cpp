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
#define INF 1e9
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
#define yesi cout<<"Yes"<<'\n'
#define nosi cout<<"No"<<'\n'
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
template <class T> void ps(set<T> &v) {for(auto& x : v) pr(x, ' '); ps();}
template <class T> void ps(const T &x) {pr(x); ps();}
template <class R, class... T> void ps(const R& r,  const T &...t) {pr(r, ' '); ps(t...);}

struct line{
  int m,c;
  int eval(int x){return m*x+c;}
  double intersect(line l){return (double) (c-l.c)/(l.m-m);}
};
struct rect{
  int p,q,a;
};
int tc=1,n,m;

void solve(int caso){
  read(n);
  vector<rect>v(n);
  fori(i,n)read(v[i].p,v[i].q,v[i].a);
  sort(all(v),[](rect a, rect b){return a.p<b.p;});
  deque<line> dq;
  dq.push_front({0,0});
  int ans = 0;
  fori(i,n){
    while(dq.size()>=2 and dq.back().eval(v[i].q)<=dq[dq.size()-2].eval(v[i].q))//eliminamos lineas del C.H. a la derecha cuyo max este en >qi
      dq.pop_back();
    //ahora al evaluar en qi, dp.back() es el que tiene el max
    int f = v[i].p*v[i].q-v[i].a + dq.back().eval(v[i].q); // dq.back().eval(v[i].q) is the max in max(-Pj*Qj + f(i)) for 1<=j<i
    ans = max(ans,f);
    line cur = {-v[i].p,f};
    //evaluamos las intersecciones del front y su next con la linea que vamos a inserta
    while(dq.size()>=2 and cur.intersect(dq[0])>=dq[0].intersect(dq[1]))
      dq.pop_front();
    dq.push_front(cur);
  }
  ps(ans);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  /*read(tc); */
  fore(caso, tc){
    solve(caso);
  }
}

