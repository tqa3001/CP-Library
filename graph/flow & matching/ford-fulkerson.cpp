/*
	Unbounded complexity O(E * f) can be useful. 
	Some potential improvements: 
	+ dfs in random order (added)
	+ scaling
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef vector<int> vi; 

const int maxN = 1005; 
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

struct ff {
	int N, S, T; 
	vector<vi> adj; 
	vector<bool> vis; 
	ff(int n, int s, int t) : N(n), S(s), T(t) { adj.resize(N + 1), vis.assign(N + 1, false); }  
	struct Edge {
		int u, v, f; 
	};
	vector<Edge> E; 
	inline void add(int u, int v, int cap) {
		E.pb({u, v, cap}); 
		E.pb({v, u, 0}); 
		adj[u].pb((int)E.size() - 2);
		adj[v].pb((int)E.size() - 1); 
	}
	int dfs(int u, int flow) {
		if(!flow or u == T) return flow; 
		vis[u] = true; 
		for(auto id : adj[u]) {
			if(!vis[E[id].v]) {
				int newflow = dfs(E[id].v, min(flow, E[id].f)); 
				if(newflow) {
					E[id].f -= newflow; 
					E[id ^ 1].f += newflow; 
					return newflow; 
				}
			}
			
		}
		return 0; 
	}
	int maxflow() {
		int ret = 0;
		for(int i = 0; i <= N; i++) shuffle(adj[i].begin(), adj[i].end(), rng); 
		while(int flow = dfs(S, (int)1e9)) {
			ret += flow; 
			vis.assign(N + 1, false); 
		}
		return ret; 
	}
}; 

int n, m, s, t; 

signed main() {
	cin >> n >> m >> s >> t; 
	ff Flow(n, s, t); 
	for(int i = 1; i <= m; i++) {
		int u, v, c; 
		cin >> u >> v >> c; 
		Flow.add(u, v, c); 
	}
	cout << Flow.maxflow(); 
}
