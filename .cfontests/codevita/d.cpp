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

int tc=1,n,m,k;
vii getCorners(int x, int y, int w, int h){
  return {{x,y},{x+w,y}, {x,y-h}, {x+w,y-h}};
}
bool inside(pii p, pii a, pii b){
  // return (a.ff<=p.ff and p.ff<=b.ff and a.ss<=p.ss and p.ss<=b.ss);
  return (a.ff<=p.ff and p.ff<=b.ff and b.ss<=p.ss and p.ss<=a.ss);
}
bool overlap(int a, int b, int c, int d, map<pii,pii>&mp){
  vii cur = getCorners(a, b, c, d);
  for(auto [key,val]: mp){
    vii cor = getCorners(key.ff, key.ss, val.ff, val.ss);
    for(pii p: cor){
      if(inside(p,cur[0],cur[3]))return true;
    }
    for(pii p: cur){
      if(inside(p,cor[0],cor[3]))return true;
    }
  }
  return false;
}
string com; int a,b,c,d;
int ans = 0;
bool valid = true;
map<pii,pii>mp;
void draw(){
  if(mp.count({a,b})) valid = false;
  if(overlap(a,b,c,d,mp)) valid= false;
  if(valid)mp[{a,b}] = {c,d},ans++;
}
void remove(){
  if(!mp.count({a,b}))valid=false;
  if(valid){
    if(mp[{a,b}].ff!=c or mp[{a,b}].ss!=d)valid=false;
  }
  if(valid)mp.erase({a,b}),ans--;
}
void extend(){
  if(!mp.count({a,b}))valid=false;
  if(valid){
    if(!(mp[{a,b}].ff<=c and mp[{a,b}].ss<=d))valid=false;
  }
  if(valid){
    auto axVal = mp[{a,b}];
    mp.erase({a,b});
    if(overlap(a,b,c,d,mp))valid=false;
    mp[{a,b}] = axVal;
  }
  if(valid){
    mp[{a,b}] = {c,d};
  }
}
void shrink(){
  if(!mp.count({a,b}))valid=false;
  if(valid){
    if(!(mp[{a,b}].ff>=c and mp[{a,b}].ss>=d))valid=false;
  }
  if(valid){
    mp[{a,b}] = {c,d};
  }
}
void solve(int caso){
  read(m,n,k);
  while(k--){
    valid = true;
    read(com,a,b,c,d);
    if(a<0 or a+c>n or b>m or b-d<0) valid = false;
    if(valid){
      if(com=="draw") draw();
      if(com=="remove")remove();
      if(com=="extend")extend();
      if(com=="shrink")shrink();
      // dbg(valid);
    }
    if(!valid)cout<<com<<' '<<a<<' '<<b<<' '<<c<<' '<<d<<endl;
    // dbg(ans);
  }
  cout<<ans;
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

