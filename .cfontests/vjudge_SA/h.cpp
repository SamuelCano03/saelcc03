/***--_saelcc03_--***/

#include <algorithm>
#include<iostream>
#include <numeric>
#include<vector>
#include<set>
using namespace std;

#ifdef LOCAL
#include ".debug.cpp"
#else
#define dbg(...)
#endif
#define fori(i,n) for(int i=0;i<(int)n;i++)
#define fore(i,n) for(int i=1;i<=(int)n;i++)
#define fora(i,n) for(int i=(int)n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<(int)b;i++)
// #define int long long
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
struct SuffixArray{
  string s;
  int n;
  vi p,c,lcp,rank,lg;
  SuffixArray(string &s):s(s){
    n = s.size();
    sa_build();
    rank=vi(n);
    fori(i,n)rank[p[i]]=i;
    lcp_build();
  }
  void sa_build(){
    s.pb(0);
    n++;
    vi cnt(max(1000002,n)); p=c=vi(n);
    int cls = 1;
    fori(i,n)cnt[s[i]]++;
    partial_sum(all(cnt),cnt.begin());
    fori(i,n)p[--cnt[s[i]]]=i;
    fore(i,n-1){
      if(s[p[i]]!=s[p[i-1]])cls++;
      c[p[i]]=cls-1;
    }// 0-th iteration. k starts 0 but is 1th iter
    for(int k=0;(1<<k)<n;k++){// so is ceil(lg(n))+1 iters
      vi pn(n),cn(n);
      fori(i,n)pn[i]=p[i]-(1<<k) + n*(p[i]<(1<<k));
      fill(cnt.begin(),cnt.begin()+cls,0);
      fori(i,n)cnt[c[pn[i]]]++;
      partial_sum(cnt.begin(),cnt.begin()+cls,cnt.begin());
      fora(i,n)p[--cnt[c[pn[i]]]]=pn[i];
      cls=1;
      fore(i,n-1){
        pii a = {c[p[i]],c[(p[i]+(1<<k))%n]};
        pii b = {c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
        if(a!=b)cls++;
        cn[p[i]]=cls-1;
      }
      c=cn;
    }
    p.erase(p.begin());
    s.pop_back(); n--;
  }
  void lcp_build(){
    lcp = vi(n-1);
    for(int i=0,k=0;i<n;i++){
      if(rank[i]==n-1){k=0;continue;}
      int j=p[rank[i]+1];
      while(i+k<n and j+k<n and s[i+k]==s[j+k])k++;
      lcp[rank[i]]=k;
      if(k)k--;
    }
  }
};


struct SparseTable{
  vvi st;
  vi lg;
  int n;
  SparseTable(vi&v){
    n=sz(v);
    lg = vi(n+1);
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    int k=lg[n]+1;
    st = vvi(n,vi(k));
    fori(i,n)st[i][0]=v[i];
    fore(j,k-1){
      for(int i=0;i+(1<<j)<=n;i++)
        st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
    }
  }
  int query(int l, int r){
    if(l>r)return 0;
    int j=lg[r-l+1];
    return min(st[l][j],st[r-(1<<j)+1][j]);
  }
};
void solve(int caso){
  read(n);
  string s; char c;
  fori(i,n)read(c),s.pb(c);
  SuffixArray sa(s);
  vi lcp = sa.lcp, p = sa.p,rank=sa.rank;
  SparseTable rmq(lcp);
  int ans = 0;
  fore(len,n){
    for(int i=1; i<=n/len;i++){
      int id1 = (i-1)*len;
      int id2 = i*len;
      if(id2>=n)continue;
      int l = min(rank[id1],rank[id2]), r = max(rank[id1],rank[id2]);
      int k = rmq.query(l,r-1);
      int rep = k/len+1;
      ans = max(ans,rep);
      if(k%len!=0){
        int ret = len - k%len;
        id1 -= ret, id2-=ret;
        if(id1<0)continue;
        l = min(rank[id1],rank[id2]), r = max(rank[id1],rank[id2]);
        k = rmq.query(l,r-1);
        rep = k/len+1;
        ans = max(ans,rep);
      }
    }
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














