#include <bits/stdc++.h>
#define MAXN 100
using namespace std;

int tree[MAXN + 1];

//se indexa desde 1
void init() {
    for (int i = 1; i <= MAXN; ++i) tree[i] = 0;
}

//acumlado desde A[1] hasta A[k]
int query(int k) {
    int ans = 0;
    while (k > 0) {
        ans += tree[k];
        k = k - (k & - k);
    }
    return ans;
}

void update(int k, int var) {
    while (k <= MAXN) {
        tree[k] += var;
        k = k + (k & -k);
    }
}

int main() {
    int n, x;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x;
        update(i, x);
    }
    cout << query(4) << "\n"; // acumlado de 1 a 4
    cout << query(5) - query(4) ; // respondo el 5to elem
    
}