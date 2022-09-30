#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxN = 2e5 + 5; 

int n, q; 
int a[maxN]; 

int st[4 * maxN], lazy[4 * maxN]; 

void Push(int i, int l, int r) {
	st[i] += lazy[i]; 
	if(l < r) {
		lazy[i << 1] += lazy[i]; 
		lazy[i << 1 | 1] += lazy[i]; 
	}
	lazy[i] = 0; 
}

void Update(int i, int l, int r, int L, int R, int val) {
	Push(i, l, r);
	if(R < l || r < L || L > R) return;  
	if(L <= l && r <= R) {
		lazy[i] += val; 
		Push(i, l, r); 
		return; 
	}
	int mid = (l + r) >> 1; 
	Update(i << 1, l, mid, L, R, val); 
	Update(i << 1 | 1, mid + 1, r, L, R, val); 
	st[i] = max(st[i << 1], st[i << 1 | 1]); 
}

int Query(int i, int l, int r, int L, int R) {
	Push(i, l, r); 
	if(R < l || r < L || L > R) return -(int)1e9;  
	if(L <= l && r <= R) {
		return st[i]; 
	}
	int mid = (l + r) >> 1; 
	return max(Query(i << 1, l, mid, L, R), Query(i << 1 | 1, mid + 1, r, L, R)); 
}

void Add(int i, int val) {
	Update(1, 1, n, i, i, val); 
	Update(1, 1, n, i + 1, n, -val); 
}

int firstPos(int i, int l, int r, int L, int R) {
	Push(i, l, r); 
	if(R < l || r < L || L > R) return -1; 
	if(L <= l && r <= R) {
		if(l == r) {
			if(st[i] < 0) return -1; 
			if(!st[i]) return l + maxN; 
			return l; 
		}
		int mid = (l + r) >> 1;
		Push(i << 1, l, mid); Push(i << 1 | 1, mid + 1, r);  
		if(st[i << 1] >= 0) return firstPos(i << 1, l, mid, L, R); 
		if(st[i << 1 | 1] >= 0) return firstPos(i << 1 | 1, mid + 1, r, L, R); 
		return -1; 
	} 
	int mid = (l + r) >> 1; 
	int ret = firstPos(i << 1, l, mid, L, R); 
	if(ret == -1) ret = firstPos(i << 1 | 1, mid + 1, r, L, R); 
	return ret; 
}

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); 
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; 
		Add(i, a[i]); 
	} 
	for(int i = 1; i <= q; i++) {
		int pos, val;   
		cin >> pos >> val; 
		Add(pos, -a[pos]);
		Add(pos, val); 
		a[pos] = val; 
		int L = 1;
		while(1) {
			if(L > n) {
				cout << -1 << '\n'; 
				break;  
			}
			int nearest = firstPos(1, 1, n, L, n); 
			if(nearest == -1) {
				cout << -1 << '\n'; 
				break; 
			}
			if(nearest > maxN) {
				cout << nearest - maxN << '\n'; 
				break; 
			}
			L = nearest + 1; 
		}
	}
}

