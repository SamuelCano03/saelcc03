#include<bits/stdc++.h>
using namespace std;

// Treap implícito

const int inf = 1e9 + 10;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int random(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

struct mydata {
	int prefix;
	int suffix;
	int ans;
	int sum;
	
	mydata() {
		prefix = suffix = sum = 0;
		ans = INT_MIN;
	}
	
	mydata(int x) {
		ans = prefix = suffix = sum = x;
	}
	
	mydata operator + (const mydata &rhs) const {
		mydata q(0);
		q.ans = max(ans, max(rhs.ans, suffix + rhs.prefix));
		q.prefix = max(prefix, sum + rhs.prefix);
		q.suffix = max(rhs.suffix, rhs.sum + suffix);
		q.sum = sum + rhs.sum;
		return q;
	}
};

struct node {
	int sz;
	int x;
	mydata value;
	mydata value_subtree;
	int priority;
	node* left;
	node* right;
	node() {
		left = right = nullptr;
	}
	
	node(int value) : value(mydata(value)), value_subtree(mydata(value)), x(value), priority(random(0, 1e9)), sz(1) {
		left = right = nullptr;
	}
};

int sz(node* t) {
	return t ? t -> sz : 0;
}

mydata value_subtree(node* t) {
	return t ? t -> value_subtree : mydata();
}

void update(node* t) {
	if(t) {
		t -> sz = sz(t -> left) + sz(t -> right) + 1;
		t -> value_subtree = value_subtree(t -> left) + t -> value + value_subtree(t -> right);
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

node* remove(node* T, int pos) {
	pair<node*, node*> p = split(T, pos);
	pair<node*, node*> p2 = split(p.first, pos - 1);
	T = merge(p2.first, p.second);
	return T;
}

node* insert(node* T, int pos, int x) {
	pair<node*, node*> p = split(T, pos - 1);
	T = merge(p.first, new node(x));
	T = merge(T, p.second);
	return T;
}

void DFS(node* T) {
	if(T == nullptr) return;
	DFS(T -> left);
	cout << T -> x << " ";
	DFS(T -> right);
}

int solve(node* T, int l, int r) {
	pair<node*, node*> p = split(T, r);
	pair<node*, node*> p2 = split(p.first, l - 1);
	mydata cur = value_subtree(p2.second);
	int res = value_subtree(p2.second).ans;
	T = merge(p2.first, p2.second);
	T = merge(T, p.second);
	return res;
}

int main() {
	cin.tie(0) -> sync_with_stdio(false);
	int n;
	cin >> n;
	node* T = nullptr;
	for(int i = 1; i <= n; i++) {
		int x;
		cin >> x;
		T = insert(T, i, x);
	}
	int q;
	cin >> q;
	while(q--) {
		char op;
		cin >> op;
		if(op == 'I') {
			int x, y;
			cin >> x >> y;
			T = insert(T, x, y);
		}
		else if(op == 'D') {
			int x;
			cin >> x;
			T = remove(T, x);
		}
		else if(op == 'R') {
			int x, y;
			cin >> x >> y;
			T = remove(T, x);
			T = insert(T, x, y);
		}
		else {
			int l, r;
			cin >> l >> r;
			cout << solve(T, l, r) << '\n';
		}
	}
	return 0;
}
