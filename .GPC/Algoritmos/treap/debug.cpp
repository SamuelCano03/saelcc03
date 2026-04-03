#include <bits/stdc++.h>
using namespace std;

// Helpers para imprimir cualquier tipo
template <class T> void dpr(const T &x) { cerr << x; }

// Pairs
template <class F, class S> void dpr(const pair<F, S> &p) {
    cerr << "{"; dpr(p.first); cerr << ", "; dpr(p.second); cerr << "}";
}

// Tuples
template<typename T1, typename T2, typename T3> void dpr(const tuple<T1,T2,T3>& t) {
    cerr << "{"; dpr(get<0>(t)); cerr << ", "; dpr(get<1>(t)); cerr << ", "; dpr(get<2>(t)); cerr << "}";
}

// Containers (except strings)
template <class T> void dpr(const vector<T> &v) {
    cerr << "[";
    bool first = true;
    for (const auto &x : v) {
        if (!first) cerr << ", ";
        dpr(x);
        first = false;
    }
    cerr << "]";
}

template <class T> void dpr(const set<T> &s) {
    cerr << "{";
    bool first = true;
    for (const auto &x : s) {
        if (!first) cerr << ", ";
        dpr(x);
        first = false;
    }
    cerr << "}";
}

template <class K, class V> void dpr(const map<K, V> &m) {
    cerr << "{";
    bool first = true;
    for (const auto &[k, v] : m) {
        if (!first) cerr << ", ";
        dpr(k); cerr << ": "; dpr(v);
        first = false;
    }
    cerr << "}";
}

// Variadic dbg
void dbgr() { cerr << '\n'; }

template<typename T, typename... Args>
void dbgr(const T &x, const Args&... args) {
    dpr(x); 
    if (sizeof...(args)) cerr << " ";
    dbgr(args...);
}

#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: ", dbgr(__VA_ARGS__)
