#include<bits/stdc++.h>
using namespace std;

// Treap implícito

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

struct node {
	int sz;
	int maxi;
	int value;
	int priority;
	node* left;
	node* right;
	node() {
		left = right = nullptr;
	}
	
	node(int value) : value(value), maxi(value), priority(random(0, 1e9)), sz(1) {
		left = right = nullptr;
	}
};

int sz(node* t) {
	return t ? t -> sz : 0;
}

int maxi(node* t) {
	return t ? t -> maxi : 0;
}

void update(node* t) {
	if(t) {
		t -> sz = sz(t -> left) + sz(t -> right) + 1;
		t -> maxi = max(maxi(t -> left), max(maxi(t -> right), t -> value));
	}
}

pair<node*, node*> split(node* t, int k, int lt = 0) {
	if(t == nullptr) return {nullptr, nullptr};
	int cur_key = lt + sz(t -> left) + 1;
	if(cur_key <= k) {
		pair<node*, node*> p = split(t -> right, k, cur_key);
		t -> right = p.first;
		update(t);
		return {t, p.second};
	}
	else {
		pair<node*, node*> p = split(t -> left, k, lt);
		t -> left = p.second;
		update(t);
		return {p.first, t};
	}
}

node* merge(node* l, node* r) {
	if(l == nullptr) return r;
	if(r == nullptr) return l;
	if(l -> priority > r -> priority) {
		l -> right = merge(l -> right, r);
		update(l);
		return l;
	}
	else {
		r -> left = merge(l, r -> left);
		update(r);
		return r;
	}
}

node* insert(node* T, int pos, int x) {
	pair<node*, node*> p = split(T, pos);
	T = merge(p.first, new node(x));
	T = merge(T, p.second);
	return T;
}

node* shift(node* T, int x) {
	if(x == 0) return T;
	pair<node*, node*> p = split(T, x);
	T = merge(p.second, p.first);
	return T;
}

node* get_max(node* T, int l, int r, int &res) {
	pair<node*, node*> p = split(T, r);
	pair<node*, node*> p2 = split(p.first, l - 1);
	res = maxi(p2.second);
	T = merge(p2.first, p2.second);
	T = merge(T, p.second);
	return T;
}

void DFS(node* t) {
	if(t == nullptr) return;
	DFS(t -> left);
	cout << t -> value << " ";
	DFS(t -> right);
}

int main() {
	cin.tie(0) -> sync_with_stdio(false);
	int n;
	cin >> n;
	node* T = nullptr;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		T = insert(T, i - 1, x);
	}
	DFS(T);
	cout << endl;
	int q;
	cin >> q;
	while(q--) {
		int op;
		cin >> op;
		if(op == 1) {
			int d;
			cin >> d;
			d %= n;
			if(d < 0) d += n;
			T = shift(T, d);
			DFS(T);
			cout << endl;
		}
		else {
			int l, r;
			cin >> l >> r;
			int res;
			T = get_max(T, l, r, res);
			cout << res << '\n';
		}
	}
	return 0;
}
