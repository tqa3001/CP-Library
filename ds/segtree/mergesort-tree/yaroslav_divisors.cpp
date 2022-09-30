#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;

int n, m; 

int a[200005], pos[200005]; 
vector<int> st[800005]; 

int sz(int i) {
	return st[i].size(); 
}

void Build(int i, int l, int r) {
	if(l == r) {
		for(int j = 1; j * j <= a[l]; j++) {
			if(a[l] % j == 0) {
				st[i].pb(pos[j]); 
				if(j * j != a[l]) st[i].pb(pos[a[l] / j]); 
			}
		}
		sort(all(st[i])); 
		return; 
	}
	int mid = (l + r) >> 1; 
	Build(i << 1, l, mid); 
	Build(i << 1 | 1, mid + 1, r); 
	st[i].resize(sz(i << 1) + sz(i << 1 | 1)); 
	merge(all(st[i << 1]), all(st[i << 1 | 1]), st[i].begin()); 
//	merge(all(st[i << 1]), all(st[i << 1 | 1]), back_inserter(st[i]));       less memory-efficient 
}

int atMost(int i, int l, int r, int L, int R, int val) {
	if(R < l or r < L or L > R) return 0; 
	if(L <= l and r <= R) {
		return (upper_bound(all(st[i]), val) - st[i].begin()); 
	}
	int mid = (l + r) >> 1; 
	return atMost(i << 1, l, mid, L, R, val) + atMost(i << 1 | 1, mid + 1, r, L, R, val); 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	cin >> n >> m; 
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; pos[a[i]] = i; 
	}
	Build(1, 1, n); 
	for(int i = 1; i <= m; i++) {
		int l, r; 
		cin >> l >> r; 
		cout << atMost(1, 1, n, l, r, r) - atMost(1, 1, n, l, r, l - 1) << '\n'; 
	}
}

