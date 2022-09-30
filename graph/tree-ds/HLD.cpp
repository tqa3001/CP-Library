/*
	HLD: Add to path + find max. 
	status: too lazy to stress test but i guess it's correct lol
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll; 
typedef vector<int> vi; 

const int maxN = 2e5 + 5; 
const ll INF = numeric_limits<ll>::max() / 2; 

int n, q;
vi adj[maxN];  

int hldCnt; 
int h[maxN], sz[maxN]; 
int head[maxN], heavy[maxN], id[maxN], parent[maxN]; 

void dfs(int u, int p) {
	sz[u] = 1; 
	for(auto v : adj[u]) {
		if(v != p) {
			h[v] = h[u] + 1; 
			parent[v] = u; 
			dfs(v, u); 
			sz[u] += sz[v]; 
			if(sz[v] > sz[heavy[u]]) {
				heavy[u] = v; 
			}
 		}
	}
}

void buildHLD(int u, int p, int root) {
	head[u] = root; 
	id[u] = ++hldCnt; 
	if(heavy[u]) {
		buildHLD(heavy[u], u, root); 
	}
	for(auto v : adj[u]) {
		if(v != p && v != heavy[u]) {
			buildHLD(v, u, v); 
		}	
	} 
}

ll st[4 * maxN], lazy[4 * maxN]; 

void Push(int i, int l, int r) {
	if(lazy[i]) {
		st[i] += lazy[i];
		if(l < r) {
			lazy[i << 1] += lazy[i]; 
			lazy[i << 1 | 1] += lazy[i]; 
		}  
		lazy[i] = 0; 
	}
} 

void Update(int i, int l, int r, int L, int R, int val) {
	Push(i, l, r); 
	if(R < l or r < L or L > R) return; 
	if(L <= l and r <= R) {
		lazy[i] += val; 
		Push(i, l, r); 
		return; 
	}
	int mid = (l + r) >> 1; 
	Update(i << 1, l, mid, L, R, val); 
	Update(i << 1 | 1, mid + 1, r, L, R, val); 
	st[i] = max(st[i << 1], st[i << 1 | 1]); 
}

ll getMax(int i, int l, int r, int L, int R) {
	Push(i, l, r); 
	if(R < l or r < L or L > R) return -INF; 
	if(L <= l and r <= R) {
		return st[i]; 
	}
	int mid = (l + r) >> 1; 
	return max(getMax(i << 1, l, mid, L, R), getMax(i << 1 | 1, mid + 1, r, L, R)); 
}

inline void addPath(int u, int v, int val) {
	while(head[u] != head[v]) {
		if(h[head[u]] < h[head[v]]) swap(u, v); 
		Update(1, 1, n, id[head[u]], id[u], val); 
		u = parent[head[u]]; 
	}
	if(id[u] + 1 > id[v]) swap(u, v); 
	Update(1, 1, n, id[u] + 1, id[v], val); 
}

inline ll maxPath(int u, int v) {
	ll ret = -INF; 
	while(head[u] != head[v]) {
		if(h[head[u]] < h[head[v]]) swap(u, v); 
		ret = max(ret, getMax(1, 1, n, id[head[u]], id[u])); 
		u = parent[head[u]]; 
	}
	if(id[u] + 1 > id[v]) swap(u, v); 
	ret = max(ret, getMax(1, 1, n, id[u] + 1, id[v])); 
	return ret;  
}

signed main() {
	cin >> n; 
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v; 
		adj[u].pb(v);
		adj[v].pb(u); 
	}
	dfs(1, 1); 
	buildHLD(1, 1, 1); 
	cin >> q; 
	for(int i = 1; i <= q; i++) {
		int type; cin >> type; 
		if(!type) {
			int u, v, val;  
			cin >> u >> v >> val; 
			addPath(u, v, val); 
		}
		else {
			int u, v; cin >> u >> v; 
			cout << maxPath(u, v) << '\n'; 
		}
	}
}
