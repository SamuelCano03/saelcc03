/***--_saelcc03_--***/

#include <bits/stdc++.h>
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
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T>
using ordered_multi_set = tree<T, null_type, less_equal<T>, rb_tree_tag,
                               tree_order_statistics_node_update>;

#define fori(i, n) for (int i = 0; i < (int)n; i++)
#define fore(i, n) for (int i = 1; i <= (int)n; i++)
#define fora(i, n) for (int i = (int)n - 1; i >= 0; i--)
#define foro(i, a, b) for (int i = a; i < (int)b; i++)
#define int long long
#define inf 1e9
#define INF 1e18
#define pii pair<int, int>
#define piii tuple<int, int, int>
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
#define mpii map<int, int>
#define pb push_back
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define sz(x) (int)x.size()
#define yesi ps("Yes")
#define nosi ps("No")
#define endl '\n'
#define approx(a) fixed << setprecision(a)
#define ff first
#define ss second
#define fast                                                                   \
  read(n);                                                                     \
  vi v(n);                                                                     \
  read(v)
// reading your mind
template <class T> void read(vector<T> &v);
template <class F, class S> void read(pair<F, S> &p);
template <class T> void read(T &x) { cin >> x; }
template <class T> void read(vector<T> &v) {
  for (auto &x : v)
    read(x);
}
template <class R, class... T> void read(R &r, T &...t) {
  read(r);
  read(t...);
};
template <class F, class S> void read(pair<F, S> &p) { read(p.ff, p.ss); }
// puking your feelings
template <class T> void ps(vector<T> &v);
template <class F, class S> void pr(const pair<F, S> &x);
template <class T> void pr(const T &x) { cout << x; }
void ps() { pr("\n"); }
template <class R, class... T> void pr(const R &r, const T &...t) {
  pr(r);
  pr(t...);
}
template <class F, class S> void pr(const pair<F, S> &x) {
  pr("{", x.ff, ", ", x.ss, "}\n");
}
template <class T> void ps(vector<T> &v) {
  for (auto &x : v)
    pr(x, ' ');
  ps();
}
template <class T> void ps(set<T> &v) {
  for (auto &x : v)
    pr(x, ' ');
  ps();
}
template <class T> void ps(const T &x) {
  pr(x);
  ps();
}
template <class R, class... T> void ps(const R &r, const T &...t) {
  pr(r, ' ');
  ps(t...);
}

int tc = 1, n, m;

void solve(int caso) {
  fast;
//   if (caso == 629) {
//     cout << n << '$' << v[0] << '$' << v[1] << '$' << v[2] << '$' << v[3] << '$'<< v[4];
//     return;
//   }
  int lt = 0, fi = 0;
  fori(i, n) {
    if (v[i] == 1)fi = i;
    if (v[i] == n)lt = i;
  }
  if (fi < lt){
    yesi;
    fori(i,lt)ps(v[i],v[lt]);
    for(int i=lt+1;i<n;i++) ps(v[i],v[fi]);
  }
  vi a, b, c;
  fora(i, lt + 1) a.pb(v[i]);
  for (int i = fi; i < n; i++)
    c.pb(v[i]);
  for (int i = lt + 1; i < fi; i++)
    b.pb(v[i]);
  int mn = *min_element(all(a));
  int mx = *max_element(all(c));
  bool con = mn < mx;
  m = sz(b);
  if (m) {
    vi ax(m), cx(m);
    vb is(m, false);
    fori(i, m) {
      int e = b[i];
      // if(e>mx and e<mn)return nosi;
      if (e < mx and e > mn)
        con = true;
      if (e < mx)
        is[i] = true, cx[i] = 1;
      if (e > mn)
        is[i] = true, ax[i] = 1;
    }
    int lti = -1, fii = -1;
    fora(i, m) if (ax[i]) {
      lti = i;
      break;
    }
    fori(i, m) if (cx[i]) {
      fii = i;
      break;
    }
    if (fii != -1 and lti != -1 and b[fii] < b[lti] and fii<lti)
      con = true;
    int nm = 1e9, xm = -1e9;
    fori(i, m) {
      if (nm < b[i])
        is[i] = true;
      if (is[i])
        nm = min(nm, b[i]);
    }
    fora(i, m) {
      if (xm > b[i])
        is[i] = true;
      if (is[i])
        xm = max(xm, b[i]);
    }
    fori(i, m) if (!is[i]) return nosi;
    int sumi = accumulate(all(ax), 0ll) + accumulate(all(cx), 0ll);
    if (sumi == 0)
      return nosi;
    // ps(sumi);
  }
  if (con)
    yesi;
  else
    nosi;
}

int32_t main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  read(tc);
  fore(caso, tc) { solve(caso); }
}
