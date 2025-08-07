#include <bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 200001
int n,q,arr[maxn], st[4*maxn], a,b;
int sum(int a, int b){return a+b;}
void update(int node, int start, int end, int idx, int val){
    if(start==end){
        st[node]=val;
        arr[idx]=val;
        return;
    }
    int mid=(start+end)/2;
    if(idx<=mid) update(2*node, start, mid, idx, val);
    else update(2*node+1, mid+1, end, idx, val);
    st[node]=sum(st[2*node], st[2*node+1]);
}
 
int query(int node, int start, int end, int l, int r){
    if(start>r || end<l)return 0;
    if(l<=start && r>=end)return st[node];
    int mid=(start+end)/2;
    return sum(query(2*node, start, mid, l, r), query(2*node+1, mid+1, end,l,r));
}
 
int32_t main(){
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        update(1,1,n,i,arr[i]);    
    }
 
 
    int x;
    while (q--){
        cin>>x>>a>>b;
        if(x==1){
            update(1,1,n,a,b);
        }
        else{
            cout<<query(1,1,n,a,b)<<'\n';
        }
    }
    
}