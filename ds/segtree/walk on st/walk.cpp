//https://cses.fi/problemset/task/1143
#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 5; 

int n, m; 
int st[4 * maxN], a[maxN]; 

void Build(int i, int l, int r) {
	if(l == r) {
		st[i] = a[l];
		return; 
	}
	int mid = (l + r) >> 1; 
	Build(i << 1, l, mid); 
	Build(i << 1 | 1, mid + 1, r); 
	st[i] = max(st[i << 1], st[i << 1 | 1]); 
}

void Update(int i, int l, int r, int id, int val) {
	if(l == r) {
		st[i] -= val; 
		return; 
	}
	int mid = (l + r) >> 1; 
	(id <= mid ? Update(i << 1, l, mid, id, val) : Update(i << 1 | 1, mid + 1, r, id, val)); 
	st[i] = max(st[i << 1], st[i << 1 | 1]); 
}

int firstGreater(int i, int l, int r, int L, int R, int val) { // pardon me for naming the function so ambiguously, as it actually finds the nearest element >= val, not > val. 
	if(R < l || r < L || L > R) return 0;
	if(L <= l && r <= R) {
		if(l == r) {
			return (st[i] >= val ? l : 0);  
		}
		int mid = (l + r) >> 1; 
		if(st[i << 1] >= val) return firstGreater(i << 1, l, mid, L, R, val); 
		if(st[i << 1 | 1] >= val) return firstGreater(i << 1 | 1, mid + 1, r, L, R, val); 
		return 0; 
	}
	int mid = (l + r) >> 1; 
	int ret = firstGreater(i << 1, l, mid, L, R, val); 
	if(!ret) ret = firstGreater(i << 1 | 1, mid + 1, r, L, R, val); 
	return ret; 
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= n; i++) cin >> a[i]; 	
	Build(1, 1, n); 
	for(int i = 1; i <= m; i++) {
		int val, pos; 
		cin >> val; 
		cout << (pos = firstGreater(1, 1, n, 1, n, val)) << ' '; 
		if(pos) Update(1, 1, n, pos, val); 
	}
}
