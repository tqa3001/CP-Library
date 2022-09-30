#include <bits/stdc++.h>
#define pb push_back
#define ii pair<int, int> 
#define fi first
#define se second
using namespace std;

const int maxN = 2e5 + 5; 

int n, m; 
int A[maxN], B[maxN]; 
vector<int> adj[maxN], g[maxN]; 

int p[maxN]; 

int Find(int x) {
	return (x == p[x] ? x : p[x] = Find(p[x])); 
}

void Merge(int u, int v) {
	u = Find(u), v = Find(v); 
	if(u == v) return; 
	p[v] = u; 
}

bool in_tree[maxN]; 
bool vis[maxN]; 
int h[maxN], parent[maxN]; 

void dfs(int u) {
	vis[u] = true; 
	for(auto id : adj[u]) {
		int v = (A[id] == u ? B[id] : A[id]); 
		if(!vis[v]) {
			h[v] = h[u] + 1; 
			parent[v] = u; 
			in_tree[id] = true; 
			dfs(v); 
		}
	}
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= n; i++) {
		p[i] = i; 
	}
	for(int i = 1; i <= m; i++) {
		cin >> A[i] >> B[i]; 
		adj[A[i]].pb(i); 
		adj[B[i]].pb(i); 
	}
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			dfs(i); 
		}
	}
	for(int i = 1; i <= m; i++) {
		int u = A[i], v = B[i]; 
		if(in_tree[i]) continue; 
 		u = Find(u); 
		v = Find(v); 
		if(h[u] > h[v]) swap(u, v); 
		while(u != v) {
			int nxt = Find(parent[v]); 
			Merge(nxt, v); 
			v = nxt; 
		}
	}
	for(int i = 1; i <= m; i++) {
		int u = A[i], v = B[i]; 
		u = Find(u), v = Find(v); 
		if(u != v) {
			g[u].pb(v); 
			g[v].pb(u); 
		}
	}
	cout << "condensed graph: \n"; 
	for(int i = 1; i <= n; i++) {
		cout << i << ": "; 
		for(auto j : g[i]) {
			cout << j << ' '; 
		}
		cout << '\n'; 
	}
}
