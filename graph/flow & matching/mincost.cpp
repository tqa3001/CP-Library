#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int INF = 1e9; 

struct MCMF {
	struct Edge { int u, v, w, f; };
	vector<Edge> E; 
	vector<int> adj[2005]; 
	int S, T, Nodes; 
	int dis[2005], parent[2005]; 
	bool inq[2005]; 
	void add(int u, int v, int w, int f) {
		E.pb({u, v, w, f}); 
		E.pb({v, u, -w, 0}); 
		adj[u].pb((int)E.size() - 2); 
		adj[v].pb((int)E.size() - 1); 
	}
	bool spfa() {
		for(int i = 0; i <= Nodes; i++) dis[i] = INF; 
		dis[S] = 0; 
		queue<int> q; q.push(S); inq[S] = true; 
		while(!q.empty()) {
			int u = q.front(); q.pop(); 
			inq[u] = false; 
			for(auto id : adj[u]) {
				int v = E[id].v, w = E[id].w, f = E[id].f; 
				if(f and dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w; 
					parent[v] = id; // an easy-to-overlook bug: put parent[v] inside if...
					if(!inq[v]) {
						q.push(v); 
						inq[v] = true; 
					}
				} 
			}
		}
		return dis[T] < INF; 
	}
	int minCostFlow(int k) {
		int ret = 0, flow = 0; 
		while(flow < k) {
			if(!spfa()) return -1; 
			int f = k - flow, cur = T; 
			while(cur != S) {
				f = min(f, E[parent[cur]].f);
				cur = E[parent[cur]].u;  
			}
			ret += f * dis[T]; 
			flow += f; 
			cur = T; 
			while(cur != S) {
				E[parent[cur]].f -= f; 
				E[parent[cur] ^ 1].f += f; 
				cur = E[parent[cur]].u; 
			} 
		}
		return ret; 
	}
} Flow;

int n, m, k, s, t; 

signed main() {
	cin >> n >> m >> k >> s >> t; 
	Flow.S = s, Flow.T = t, Flow.Nodes = n; 
	for(int i = 1; i <= m; i++) {
		int u, v, w, f; cin >> u >> v >> w >> f; 
		Flow.add(u, v, w, f); 
		Flow.add(v, u, w, f); 
	}
	cout << Flow.minCostFlow(k); 
}
