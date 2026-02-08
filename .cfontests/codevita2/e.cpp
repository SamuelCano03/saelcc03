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
template<class R,class... T> void read(R &r,T&... t){read(r);read(t...);};
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

struct Vec3{
	int x,y,z;
	Vec3 operator+(const Vec3&o)const{return{x+o.x,y+o.y,z+o.z};}
	Vec3 operator-(const Vec3&o)const{return{x-o.x,y-o.y,z-o.z};}
	Vec3 operator-()const{return{-x,-y,-z};}
	bool operator==(const Vec3&o)const{return x==o.x&&y==o.y&&z==o.z;}
	int dot(const Vec3&o)const{return x*o.x+y*o.y+z*o.z;}
};

struct FaceFrame{
	Vec3 normal,up,right;
};

struct FaceData{
	char id;
	string chars;
	FaceFrame frame;
	bool visited=false;
};

map<char,FaceData> faces;
char gridc[4][4];

void solve(int caso){
	vector<char> order;
	fori(i,4){
		string s;read(s);
		fori(j,4){
			gridc[i][j]=s[j];
			if(s[j]!='.'){
				order.pb(s[j]);
				faces[s[j]].id=s[j];
			}
		}
	}

	string cont;read(cont);
	fori(i,sz(order)) faces[order[i]].chars=cont.substr(i*4,4);

	string q;read(q);

	int sr=-1,sc=-1;
	fori(i,4) foro(j,0,4) if(gridc[i][j]!='.'){sr=i;sc=j;break;}
	
	char st=gridc[sr][sc];
	faces[st].frame={{0,1,0},{0,0,-1},{1,0,0}};
	faces[st].visited=true;

	queue<pii>qq;
	qq.push({sr,sc});

	int dr[4]={-1,1,0,0};
	int dc[4]={0,0,-1,1};

	while(!qq.empty()){
		auto [r,c]=qq.front();qq.pop();
		char id=gridc[r][c];
		auto f=faces[id].frame;

		fori(k,4){
			int nr=r+dr[k],nc=c+dc[k];
			if(nr>=0&&nr<4&&nc>=0&&nc<4&&gridc[nr][nc]!='.'){
				char nx=gridc[nr][nc];
				if(!faces[nx].visited){
					FaceFrame nf;
					if(k==0){
						nf.normal=f.up;
						nf.up=-f.normal;
						nf.right=f.right;
					}else if(k==1){
						nf.normal=-f.up;
						nf.up=f.normal;
						nf.right=f.right;
					}else if(k==2){
						nf.normal=-f.right;
						nf.right=f.normal;
						nf.up=f.up;
					}else{
						nf.normal=f.right;
						nf.right=-f.normal;
						nf.up=f.up;
					}
					faces[nx].frame=nf;
					faces[nx].visited=true;
					qq.push({nr,nc});
				}
			}
		}
	}

	Vec3 pos={0,0,0};
	for(auto &c:q) pos=pos+faces[c].frame.normal;

	string ans="";
	for(auto &c:q){
		auto &fd=faces[c];
		int col=fd.frame.right.dot(pos)>0?1:0;
		int row=fd.frame.up.dot(pos)>0?0:1;
		int idx=row*2+col;
		ans+=fd.chars[idx];
	}

  cout<<ans;
}

int32_t main(){
	ios::sync_with_stdio(false);cin.tie(0);
	// read(tc);
	fore(caso,tc) solve(caso);
}
