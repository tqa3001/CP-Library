/*
	Simple toposort, assuming the input graph is a dag. 
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef vector<int> vi; 

const int maxN = 2e5 + 5; 
int n, m; 

vi adj[maxN], topo; 
vector<bool> vis; 
 
void dfs(int u) {
	vis[u] = true;
	for(auto v : adj[u]) 
		if(!vis[v]) 
			dfs(v); 
	topo.pb(u); 
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v; 
		adj[u].pb(v); 
	}
	vis.assign(n + 1, false); 
	for(int i = 1; i <= n; i++) 
		if(!vis[i]) 
			dfs(i);
	reverse(topo.begin(), topo.end()); 
	for(auto u : topo) cout << u << ' '; 
}
