#include <bits/stdc++.h>
using namespace std;
#define int long long 
vector<int>z;
void Z(const string &s){
    int n=s.size();
    int l=0, r=0;
    z.resize(n, 0);
    for(int i=1;i<n;i++){
        if(i>r){
            l=r=i;
            while(r<n and s[r-l]==s[r])r++;
            z[i]=r-l;
            r--;
        }
        else{
            int k=i-l;
            if(z[k]<r-i+1)z[i]=z[k];
            else{
                l=i;
                while(r<n and s[r-l]==s[r])r++;
                z[i]=r-l;
                r--;
            }
        }
    }
}
int32_t main(){
    string pat, text;
    cin>>text>>pat;
    Z(pat+"#"+text);
    for(int i=0;i<z.size();i++){
        cout<<z[i]<<' ';
        
    }
}