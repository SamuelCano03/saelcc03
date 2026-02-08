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
template<class T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multi_set=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

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
#define rall(v) v.rbegin(),v.rend()
#define sz(x) (int)x.size()
#define yesi ps("Yes")
#define nosi ps("No")
#define endl '\n'
#define approx(a) fixed<<setprecision(a)
#define ff first
#define ss second
#define fast read(n);vi v(n);read(v)

template<class T> void read(vector<T> &v);
template<class F,class S> void read(pair<F,S> &p);
template<class T> void read(T &x){cin>>x;}
template<class T> void read(vector<T> &v){for(auto &x:v) read(x);}
template<class R,class... T> void read(R &r,T&... t){read(r);read(t...);}
template<class F,class S> void read(pair<F,S> &p){read(p.ff,p.ss);}

template<class T> void ps(vector<T> &v);
template<class F,class S> void pr(const pair<F,S> &x);
template<class T> void pr(const T &x){cout<<x;}
void ps(){pr("\n");}
template<class R,class... T> void pr(const R &r,const T&... t){pr(r);pr(t...);}
template<class F,class S> void pr(const pair<F,S> &x){pr("{",x.ff,", ",x.ss,"}\n");}
template<class T> void ps(vector<T> &v){for(auto &x:v) pr(x,' ');ps();}
template<class T> void ps(set<T> &v){for(auto &x:v) pr(x,' ');ps();}
template<class T> void ps(const T &x){pr(x);ps();}
template<class R,class... T> void ps(const R &r,const T &... t){pr(r,' ');ps(t...);}

int tc=1,n,m;

int calc(int deg,int dir,int t1,int t2){
  if(deg==0) return 0;
  int a=min(deg,90ll)*t1;
  int b=max(0LL,deg-90)*t2;
  return dir*(a+b);
}

void solve(int caso){
  string s; if(!(cin>>s)) return;
  size_t pos=s.find(':');
  int H=0,M=0;
  H=stoll(s.substr(0,pos));
  M=stoll(s.substr(pos+1));
  int q; read(q);
  int A,B,P,Q,X,Y;
  read(A,B);
  read(P,Q);
  read(X,Y);
  vi v(q); read(v);
  int ch=(H%12)*30;
  int cm=M*6;
  int tot=0;
  for(auto ang:v){
    int best=INF,bh=-1,bm=-1;
    fori(hs,12){
      int hdeg=hs*30;
      int nh=(ch+hdeg)%360;
      int costh=calc(hdeg,A,P,Q);
      int a1=(nh+ang)%360;
      int a2=(nh-ang+360)%360;
      int arr[2]={a1,a2};
      fori(t,2){
        int tm=arr[t];
        int mdeg=(cm-tm+360)%360;
        int costm=calc(mdeg,B,X,Y);
        if(costh+costm<best){best=costh+costm;bh=nh;bm=tm;}
      }
    }
    fori(hs,12){
      int hdeg=hs*30;
      int nh=(ch-hdeg+360)%360;
      int costh=calc(hdeg,B,P,Q);
      int a1=(nh+ang)%360;
      int a2=(nh-ang+360)%360;
      int arr[2]={a1,a2};
      fori(t,2){
        int tm=arr[t];
        int mdeg=(tm-cm+360)%360;
        int costm=calc(mdeg,A,X,Y);
        if(costh+costm<best){best=costh+costm;bh=nh;bm=tm;}
      }
    }
    tot+=best;
    ch=bh;cm=bm;
  }
  ps(tot);
}

int32_t main(){
  ios::sync_with_stdio(false);cin.tie(0);
  tc=1;
  fore(caso,tc) solve(caso);
}
