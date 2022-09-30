#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int INF = 1e9; 

struct Dinitz {
	struct Edge {
		int u, v, f; 
	};
	vector<Edge> E; 
	vector<int> adj[2005]; 
	int S, T, Nodes; 
	int dis[2005], ptr[2005]; 
	void add(int u, int v, int w) {
		E.pb({u, v, w}); 
		E.pb({v, u, 0}); 
		adj[u].pb((int)E.size() - 2); 
		adj[v].pb((int)E.size() - 1); 
	}
	bool bfs() {
		for(int i = 0; i <= Nodes; i++) dis[i] = INF; 
		dis[S] = 0; 
		queue<int> q; q.push(S); 
		while(!q.empty()) {
			int u = q.front(); q.pop(); 
			for(auto id : adj[u]) {
				int v = E[id].v, f = E[id].f; 
				if(f and dis[v] > dis[u] + 1) {
					dis[v] = dis[u] + 1; 
					q.push(v); 
				}
			}
		}
		return dis[T] < INF; 
	}
	int dfs(int u, int flow) {
		if(u == T or !flow) return flow; 
		for(int &i = ptr[u]; i < (int)adj[u].size(); i++) {
			int id = adj[u][i]; 
			int v = E[id].v, f = E[id].f; 
			if(dis[v] == dis[u] + 1) {
				int newflow = dfs(v, min(flow, f)); 
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
		while(bfs()) {
			for(int i = 0; i <= Nodes; i++) ptr[i] = 0; 
			while(int flow = dfs(S, INF)) ret += flow; 
		}
		return ret; 
	}
};

signed main() {
	
}
