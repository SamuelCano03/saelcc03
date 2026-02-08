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
#define piii tuple<int,int,char>
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

void solve(int caso){
  string e;
  int hmax = 0;
  int sumw= 0;
  viii v;
  while(cin>>e){
    char d = e.back();
    int i = e.find('x') ;
    int w = stoll(e.substr(0,i));
    int h = stoll(e.substr(i+1));
    hmax =  max(h+w/2,hmax);
    sumw+= w;
    v.pb({w,h,d});
  }
  vs ans(hmax,string(sumw,' '));
  int tow = 0;
  for(auto [w,h,d]: v){
    int roof = w/2;
    vs ax(h+roof);
    string spaces = (w%2?" ":"");
    string sp = string(w/2-1,' ');
    fori(i,roof){
      ax[i]=(d=='U' or d=='D'?sp+"\\"+spaces+"/"+sp:sp+"/"+spaces+"\\"+sp);
      spaces += "  ";
      if(sp.size()>0)sp.pop_back();
    }
    int walls = h-1;
    spaces = "";
    fori(i,w-2)spaces+=" ";
    for(int i=roof;i<roof+walls;i++) ax[i]=(d=='L' or d=='R'?"&"+spaces+"@":"@"+spaces+"&");
    fori(i,w)ax.back().pb('#');
    if(d=='U' or d=='D'){
      fori(i,sz(ax)/2) swap(ax[i],ax[sz(ax)-i-1]);
    }
    // for(auto e: ax)ps(e);
    int pos = hmax - ax.size();
    
    for(int i=pos;i<hmax;i++){
      for(int j=tow;j<tow+w;j++)ans[i][j]=ax[i-pos][j-tow];
    }
    tow += w;
  }
  for(auto e: ans)ps(e);
}


int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  // read(tc); 
  fore(caso, tc){
    solve(caso);
  }
}

