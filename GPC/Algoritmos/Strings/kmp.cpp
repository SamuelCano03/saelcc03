#include<bits/stdc++.h>

using namespace std;
#define fori(i,n) for(int i=0;i<n;i++)
#define fore(i,n) for(int i=1;i<=n;i++)
#define fora(i,n) for(int i=n-1;i>=0;i--)
#define foro(i,a,b) for(int i=a;i<b;i++)
#define int long long
#define limit LLONG_MAX
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
template <class T, size_t Z> void read(array<T, Z> &a);
template <class T> void read(T &x) {cin >> x;}
template <class R, class... T> void read(R& r, T&... t){read(r); read(t...);};
template <class T> void read(vector<T> &v) {for(auto& x : v) read(x);}
template <class F, class S> void read(pair<F, S> &p) {read(p.ff, p.ss);}
template <class T, size_t Z> void read(array<T, Z> &a) { for(auto &x : a) read(x); }

template <class F, class S> void pr(const pair<F, S> &x);
template <class T> void pr(const T &x) {cout << x;}
template <class R, class... T> void pr(const R& r, const T&... t) {pr(r); pr(t...);}
template <class F, class S> void pr(const pair<F, S> &x) {pr("{", x.ff, ", ", x.ss, "}\n");}
void ps() {pr("\n");}
template <class T> void ps(const T &x) {pr(x); ps();}
template <class T> void ps(vector<T> &v) {for(auto& x : v) pr(x, ' '); ps();}
template <class T, size_t Z> void ps(const array<T, Z> &a) { for(auto &x : a) pr(x, ' '); ps(); }
template <class F, class S> void ps(const pair<F, S> &x) {pr(x.ff, ' ', x.ss); ps();}
template <class R, class... T> void ps(const R& r,  const T &...t) {pr(r, ' '); ps(t...);}

//ABABD......ABABA
//00120......12343
vi prefixFunction(string &s){
  int M = s.size();
  vi pi(M);
  for(int i=1,len=0;i<M;i++){
    while(len>0 and s[len]!=s[i])len = pi[len-1];
    if(s[len]==s[i])len++;
    pi[i]=len;
  }
  return pi;
}

int tc=1,n,m,t,q;

void solve(){

}
int32_t main(){
  ios::sync_with_stdio(false); cin.tie(0);
  /*read(tc); */
  while(tc--){
    solve();
  }
}
