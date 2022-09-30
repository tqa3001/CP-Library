#include <bits/stdc++.h>
#define pb push_back
#define ii pair<int, int> 
#define fi first
#define se second 
using namespace std;

const int maxN = 2e5 + 5; 

int n, m; 
vector<int> adj[maxN]; 
vector<ii> Bridges; 
bool Arti[maxN];  

int dfscnt; 
int num[maxN], low[maxN], parent[maxN];  
int root, rootChild; 

void dfs(int u) {
	num[u] = low[u] = ++dfscnt; 
	for(auto v : adj[u]) {
		if(!num[v]) {
			if(u == root) {
				rootChild++; 
			}
			parent[v] = u; 
			dfs(v); 
			low[u] = min(low[u], low[v]); 
			if(low[v] >= num[u]) {
				if(u != root) Arti[u] = true; 
				if(low[v] > num[u]) Bridges.pb({u, v}); 
			}
		}
		else if (v != parent[u]) low[u] = min(low[u], num[v]); 
	}
	if(u == root and rootChild > 1) Arti[u] = true; 
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v; 
		cin >> u >> v; 
		adj[u].pb(v); 
		adj[v].pb(u); 
	}
	for(int i = 1; i <= n; i++) {
		if(!num[i]) {
			root = i, rootChild = 0; 
			dfs(i); 
		}
	}
	int artiCnt = 0; 
	for(int i = 1; i <= n; i++) if(Arti[i]) artiCnt++; 
	cout << artiCnt << ' ' << (int)Bridges.size() << '\n'; 
}
