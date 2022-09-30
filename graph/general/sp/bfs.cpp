#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define ii pair<int, int> 
#define fi first
#define se second
using namespace std;

const int maxN = 2e5 + 5; 
const ll INF = 1e18;  

int n, m; 
vector<ii> adj[maxN];
ll dis[maxN];  

void bfs(int root) {
	for(int i = 1; i <= n; i++) dis[i] = INF; 
	dis[root] = 0; 
	queue<int> q; q.push(root); 
	while(!q.empty()) {
		int u = q.front(); q.pop(); 
		for(auto T : adj[u]) {
			int v = T.fi, w = T.se; 
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w; 
				q.push(v); 
			}
 		}
	} 
	for(int i = 1; i <= n; i++) cout << dis[i] << ' '; cout << '\n';  
}

void bfs01(int root) {
	for(int i = 1; i <= n; i++) dis[i] = INF; 
	dis[root] = 0; 
	deque<int> dq; dq.push_front(root); 
	while(!dq.empty()) {
		int u = dq.front(); dq.pop_front(); 
		for(auto T : adj[u]) {
			int v = T.fi, w = T.se; 
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w; 
				if(w) dq.push_back(v); 
				else dq.push_front(v); 
			}
		}
	}
	for(int i = 1; i <= n; i++) cout << dis[i] << ' '; cout << '\n';  
}

void bfsMultisource(const vector<int> &s) {
	assert(!s.empty()); 
	for(int i = 1; i <= n; i++) dis[i] = INF; 
	for(auto u : s) dis[u] = 0; 
	queue<int> q; 
	for(auto u : s) q.push(u); 
	while(!q.empty()) {
		int u = q.front(); q.pop(); 
		for(auto T : adj[u]) {
			int v = T.fi; 
			if(dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1; 
				q.push(v); 
 			}
		}
	}
	for(int i = 1; i <= n; i++) cout << dis[i] << ' '; cout << '\n'; 
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v, w; 
		cin >> u >> v >> w; 
		adj[u].pb({v, w}); 
		adj[v].pb({u, w}); 
	}
}
