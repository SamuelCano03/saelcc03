#include <bits/stdc++.h>
using namespace std;
#define int long long
template<typename T>
struct Node{
    T val;
    Node(){}
};
template<typename T>
struct ST{
    private:
        vector<Node<T>>tree; vector<T>arr; int sz;
        int ln(int node){return 2*node+1;}
        int rn(int node){return 2*node+2;}
        function <T(T,T)> fx;
        void updateTree(int node, int start, int end, int id, T val){
            if(start==end){
                tree[node].val=val; arr[id]=val; return;
            }
            int mid=(start+end)/2;
            if(id<=mid) updateTree(ln(node), start, mid, id, val);
            else        updateTree(rn(node), mid+1, end, id, val);
            tree[node].val=fx(tree[ln(node)].val,tree[rn(node)].val);
        }
        T queryTree(int node, int start, int end, int l, int r){
            if(r<start or end<l) return 0;
            if(l<=start and end<=r)return tree[node].val;
            int mid=(start+end)/2;
            return fx(queryTree(ln(node),start,mid,l,r),queryTree(rn(node),mid+1,end,l,r));
        }
    public:
        ST(const vector<T>&a, const function<T(T, T)>& fxi){
            fx = fxi;
            arr=a;
            sz=arr.size();
            tree.resize(4*sz);
            for(int i=0;i<sz;i++)
                modify(i, arr[i]);
        }
        void update(int id, T val){
            updateTree(0, 0, sz-1, id, fx(val,arr[id]));
        }
        void modify(int id, T val){
            updateTree(0, 0, sz-1, id, val);
        }
        T query(int l, int r){
            return queryTree(0, 0, sz-1, l, r);
        }
        vector<T> getArr(){return arr;}
};

int n, t=1, q;
void solve()
{
    vector<int>w={3,2,4,5,1};
    ST<int> st(w, [](int a, int b){return a+b;});
    cout<<st.query(1,3)<<'\n';
    st.update(2,3);
    cout<<st.query(1,3)<<'\n';
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
