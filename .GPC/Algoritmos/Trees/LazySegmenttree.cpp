#include <bits/stdc++.h>
using namespace std;
#define int long long
struct Node{
    int lazy=0, val=0;
    Node(){}
};
struct LazyST{
    private:
        vector<Node>tree; vector<int>arr; int sz;
        int ln(int node){return 2*node+1;}
        int rn(int node){return 2*node+2;}
        
        void propLazy(int node, int start, int end){
            if(tree[node].lazy!=0){
                tree[node].val+=(end-start+1)*tree[node].lazy;
                if(start!=end){
                    tree[ln(node)].lazy+=tree[node].lazy;
                    tree[rn(node)].lazy+=tree[node].lazy;
                }
                tree[node].lazy=0;
            }
        }
        void updateTree(int node, int start, int end, int l, int r, int val){
            propLazy(node, start, end);
            if(r<start or end<l)return;
            if(l<=start and end<=r){
                tree[node].lazy+=val;
                propLazy(node, start, end);
                if(start==end)arr[l]=tree[node].val;
                return;
            }
            int mid=(start+end)/2;
            updateTree(ln(node), start, mid, l, r, val);
            updateTree(rn(node), mid+1, end, l, r, val);
            tree[node].val=tree[ln(node)].val+tree[rn(node)].val;
        }
        int queryTree(int node, int start, int end, int l, int r){
            propLazy(node, start, end);
            if(r<start or end<l)return 0;
            if(l<=start and end<=r)return tree[node].val;
            int mid=(start+end)/2;
            return queryTree(ln(node), start, mid, l, r)+queryTree(rn(node), mid+1, end,l,r);
        }
    public:
        LazyST(const vector<int>&a){
            arr=a;
            sz=arr.size();
            tree.resize(4*sz);
            for(int i=0;i<sz;i++)
                update(i, i, arr[i]);
        }
        void update(int l, int r, int val){
            updateTree(0, 0, sz-1, l, r, val);
        }
        
        int query(int l, int r){
            return queryTree(0, 0, sz-1, l, r);
        }
        vector<int> getArr(){
            for (int i=0; i<sz; i++) {
                update(i,i,0);
            }
            return arr;
        }
};

int n, t=1, q;
void solve()
{
    LazyST st({3,2,4,5,1});
    cout<<st.query(1,3)<<endl;
    st.update(1,3,3);
    cout<<st.query(1,3)<<endl;
    vector<int>v=st.getArr();
    for(int e: v)cout<<e<<' ';

}

int32_t main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> t;
    while (t--){
        solve();
    }
}
