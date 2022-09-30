/*
	Dynamic segtree solution for cf periodic rmq. 
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxN = 1e5 + 5; 
const int INF = numeric_limits<int>::max() / 2; 

int n, k, q; 
int b[maxN], sp[maxN][22], Lg[maxN]; 

int getMin(int l, int r) {
	int Log = Lg[r - l + 1]; 
	return min(sp[l][Log], sp[r - (1 << Log) + 1][Log]); 
}

struct Node {
	int l, r, mn, lazy; 
	int lid, rid; 

	Node(int l, int r) : l(l), r(r) { 
		lazy = 0;
		lid = rid = -1;   
		if(r - l + 1 >= n) {
			mn = getMin(1, n); 
		}
		else {
			int _l = (l - 1) % n + 1, _r = (r - 1) % n + 1; 
			if(_l <= _r) mn = getMin(_l, _r); 
			else {
				mn = min(getMin(_l, n), getMin(1, _r)); 
			}
		}
	};
};

vector<Node> st; 

void reCal(int i) {
	int lid = st[i].lid, rid = st[i].rid; 
	st[i].mn = min(st[lid].mn, st[rid].mn); 
}

void updFromLazy(int i) {
	if(st[i].lazy) st[i].mn = st[i].lazy; 
}

void Push(int i) {
//	cout << "push: " << i << '\n'; 
	if(st[i].l != st[i].r) {		
		int mid = (st[i].l + st[i].r) >> 1; 
		if(st[i].lid == -1) {
			st[i].lid = st.size(); 
			st.pb(Node(st[i].l, mid)); 
		}
		if(st[i].rid == -1) {
			st[i].rid = st.size(); 
			st.pb(Node(mid + 1, st[i].r)); 
		}
	}
	if(st[i].lazy) {
		if(st[i].l != st[i].r) {
			int lid = st[i].lid, rid = st[i].rid; 
			st[lid].lazy = st[i].lazy, st[rid].lazy = st[i].lazy;
		}
		st[i].lazy = 0; 
	}
}

bool bad(int l, int r, int L, int R) {
	return R < l || r < L || L > R;
}

void Update(int i, int L, int R, int val) {
//	cout << i << ' ' << st[i].l << ' ' << st[i].r << '\n'; 
	updFromLazy(i);  
	if(bad(st[i].l, st[i].r, L, R)) return; 
	if(L <= st[i].l && st[i].r <= R) {
 		st[i].lazy = val; 
 		updFromLazy(i); 
		return; 
	} 
	Push(i);
	int lid = st[i].lid, rid = st[i].rid; 
	Update(lid, L, R, val); 
	Update(rid, L, R, val); 
	reCal(i); 
}

int Query(int i, int L, int R) {
	updFromLazy(i); 
	if(L <= st[i].l && st[i].r <= R) {
		return st[i].mn; 
	}
	Push(i);
	int ret = INF, lid = st[i].lid, rid = st[i].rid; 
	if(!bad(st[lid].l, st[lid].r, L, R)) ret = min(ret, Query(lid, L, R)); 
	if(!bad(st[rid].l, st[rid].r, L, R)) ret = min(ret, Query(rid, L, R));
	return ret; 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> k; 
	for(int i = 1; i <= n; i++) cin >> b[i]; 
	Lg[1] = 0; 
	for(int i = 2; i <= n; i++) {
		Lg[i] = Lg[i / 2] + 1;
	}
	for(int Len = 0; (1 << Len) <= n; Len++) {
		for(int i = 1; i + (1 << Len) - 1 <= n; i++) {
			if(!Len) sp[i][Len] = b[i]; 
			else {
				sp[i][Len] = min(sp[i][Len - 1], sp[i + (1 << (Len - 1))][Len - 1]); 
			}
		}
	}
	st.pb(Node(1, n * k));  
	cin >> q; 
	for(int i = 1; i <= q; i++) {
		int type, l, r; 
		cin >> type >> l >> r; 
		if(type == 1) {
			int val; 
			cin >> val; 
			Update(0, l, r, val); 
		}
		else {
			cout << Query(0, l, r) << '\n'; 
		}
	}
}
