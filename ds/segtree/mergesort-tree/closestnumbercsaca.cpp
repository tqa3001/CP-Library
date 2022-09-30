#include <bits/stdc++.h>
#define ii pair<int, int> 
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;

const int maxN = 5e4 + 5, INF = 1e9 + 9;  
int n, q; 
int a[maxN]; 

int smallLeft[maxN], largeLeft[maxN], smallRight[maxN], largeRight[maxN]; 
int current;  

struct segtree {
	vector<ii> v[4 * maxN];
	vector<int> preMin[4 * maxN], sufMin[4 * maxN]; 
	void build(int i, int l, int r) {
		if(l == r) {
			if(current == 0) v[i].pb({smallLeft[l], a[l] - a[smallLeft[l]]}); 
			if(current == 1) v[i].pb({largeLeft[l], a[largeLeft[l]] - a[l]}); 
			if(current == 2) v[i].pb({smallRight[l], a[l] - a[smallRight[l]]}); 
			if(current == 3) v[i].pb({largeRight[l], a[largeRight[l]] - a[l]});
			preMin[i].pb(v[i].front().se); 
			sufMin[i].pb(v[i].front().se); 
			return; 
		}
		int mid = (l + r) >> 1; 
		build(i << 1, l, mid); 
		build(i << 1 | 1, mid + 1, r); 
		merge(all(v[i << 1]), all(v[i << 1 | 1]), back_inserter(v[i])); 
		for(int j = 0, curMin = INF; j < (int)v[i].size(); j++) {
			curMin = min(curMin, v[i][j].se); 
			preMin[i].pb(curMin); 
		}
		for(int j = (int)v[i].size() - 1, curMin = INF; j >= 0; j--) {
			curMin = min(curMin, v[i][j].se); 
			sufMin[i].pb(curMin); 
		}
		reverse(all(sufMin[i])); 
	}
	
	int queryPre(int i, int l, int r, int L, int R, int id) { // all nearest <= id
		if(R < l or r < L or L > R) return INF;
		if(L <= l and r <= R) {
			ii tmp = {id, INF}; 
			int index = upper_bound(all(v[i]), tmp) - v[i].begin() - 1;
			if(index < 0) return INF; 
			return preMin[i][index];  
		}
		int mid = (l + r) >> 1; 
		return min(queryPre(i << 1, l, mid, L, R, id), queryPre(i << 1 | 1, mid + 1, r, L, R, id));  
	}
	
	int querySuf(int i, int l, int r, int L, int R, int id) { // all nearest >= id
		if(R < l or r < L or L > R) return INF; 
		if(L <= l and r <= R) {
			ii tmp = {id, -INF}; 
			int index = lower_bound(all(v[i]), tmp) - v[i].begin(); 
			if(index >= (int)v[i].size()) return INF;  
			return sufMin[i][index]; 
		}
		int mid = (l + r) >> 1; 
		return min(querySuf(i << 1, l, mid, L, R, id), querySuf(i << 1 | 1, mid + 1, r, L, R, id)); 
	}
} st[4];

map<int, int> M; 
int eqLeft[maxN]; 
int sp[maxN][20], Lg[maxN]; 

int getMax(int l, int r) {
	int Log = Lg[r - l + 1]; 
	return max(sp[l][Log], sp[r - (1 << Log) + 1][Log]); 
}

signed main() {
//	freopen("test.inp", "r", stdin); 
//	freopen("out.out", "w", stdout); 
// lol thuat sai 
// should have drafted
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) {
		cin >> a[i];
		eqLeft[i] = M[a[i]]; 
		M[a[i]] = i;  
	}
	Lg[1] = 0; 
	for(int i = 2; i <= n; i++) Lg[i] = Lg[i >> 1] + 1; 
	for(int len = 0; (1 << len) <= n; len++) {
		for(int i = 1; i + (1 << len) - 1 <= n; i++) {
			if(!len) sp[i][len] = eqLeft[i]; 
			else sp[i][len] = max(sp[i][len - 1], sp[i + (1 << (len - 1))][len - 1]); 
		}
	}
	for(int i = 1; i <= n; i++) {
		smallRight[i] = largeRight[i] = n + 1; 
	}
	stack<int, vector<int> > Smin, Smax; 
	for(int i = 1; i <= n; i++) {
		while(!Smin.empty() and a[Smin.top()] > a[i]) Smin.pop(); 
		if(!Smin.empty()) smallLeft[i] = Smin.top(); 
		Smin.push(i);
		while(!Smax.empty() and a[Smax.top()] < a[i]) Smax.pop(); 
		if(!Smax.empty()) largeLeft[i] = Smax.top(); 
		Smax.push(i); 
	}
	while(!Smin.empty()) Smin.pop(); 
	while(!Smax.empty()) Smax.pop(); 
	for(int i = n; i; i--) {
		while(!Smin.empty() and a[Smin.top()] > a[i]) Smin.pop(); 
		if(!Smin.empty()) smallRight[i] = Smin.top(); 
		Smin.push(i);
		while(!Smax.empty() and a[Smax.top()] < a[i]) Smax.pop(); 
		if(!Smax.empty()) largeRight[i] = Smax.top(); 
		Smax.push(i); 
	}
//	cout << "nearest: \n"; 
//	for(int i = 1; i <= n; i++) {
//		cout << i << '\t' << smallLeft[i] << ' ' << largeLeft[i] << ' ' << smallRight[i] << ' ' << largeRight[i] << '\n'; 
//	}
//	cout << '\n'; 
	for(int i = 0; i < 4; i++) {
		current = i; 
		st[i].build(1, 1, n); 
	}
	int last = 0; 
	for(int i = 1; i <= q; i++) {
		int l, r; 
		cin >> l >> r; 
		l = 1 + (l + last) % n; 
		r = 1 + (r + last) % n; 
		if(l > r) swap(l, r); 
		int mn = INF; 
		for(int type = 0; type < 2; type++) {
			mn = min(mn, st[type].querySuf(1, 1, n, l, r, l));
		}
		for(int type = 2; type < 4; type++) {
			mn = min(mn, st[type].queryPre(1, 1, n, l, r, r)); 
		}
		if(getMax(l, r) >= l) mn = 0; 
		cout << "l, r: " << l << ' ' << r << '\n'; 
		cout << mn << '\n'; 
		last = mn;
	}
}
