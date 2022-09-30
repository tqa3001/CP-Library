#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxN = 2e5 + 5; 

int n; 
vector<int> adj[maxN]; 

int dfsCnt; 
int in[maxN], out[maxN]; 
int jump[maxN][22]; 
int h[maxN]; 

void dfs(int u, int p) {
	in[u] = dfsCnt++; 
	jump[u][0] = p; 
	for(int i = 1; i < 20; i++) jump[u][i] = jump[jump[u][i - 1]][i - 1]; 
	for(auto v : adj[u]) {
		if(v != p) {
			h[v] = h[u] + 1; 
			dfs(v, u); 
		}
	}
	out[u] = dfsCnt - 1; 
}

inline bool isanc(int u, int v) {
	return in[u] <= in[v] and out[v] <= out[u]; 
}

inline int lca(int u, int v) {
	if(isanc(u, v)) return u; 
	if(isanc(v, u)) return v; 
	for(int i = 19; i >= 0; i--) {
		if(!isanc(jump[u][i], v)) u = jump[u][i]; 
	}
	return jump[u][0]; 
}

inline int dist(int u, int v) {
	return h[u] + h[v] - 2 * h[lca(u, v)]; 	
}

inline int kthAnc(int u, int k) {
	int pu = u; 
	for(int i = 19; i >= 0; i--) {
		if(h[u] - h[jump[pu][i]] <= k) pu = jump[pu][i]; 
	}
	return pu; 
}

signed main() {
	cin >> n; 
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v; 
		adj[u].pb(v); 
		adj[v].pb(u); 
	}
	dfs(1, 1); 
	while(1) {
		int type, u, v; 
		cin >> type >> u >> v; 
		if(!type) cout << lca(u, v) << ' ' << dist(u, v) << '\n'; 
		else cout << kthAnc(u, v) << '\n'; 
	}
}
/*
15
1 2
1 3
1 4
2 5
2 6
3 7
4 8
4 9
6 10
6 11
7 12
8 13
8 14
8 15
*/
