#include <bits/stdc++.h>
#define ll long long
#define ii pair<int, int> 
#define fi first
#define se second
#define pb push_back
using namespace std;

const int maxN = 2e5 + 5; 
const ll INF = 1e18; 

int n, m, test; 
vector<ii> adj[maxN]; 

ll dis[maxN]; 

void dijkstra(int root) {
	for(int i = 1; i <= n; i++) {
		dis[i] = INF; 
	}
	dis[root] = 0; 
	priority_queue<ii, vector<ii>, greater<ii> > pq; 
	pq.push({0, root}); 
	while(!pq.empty()) {
		ii T = pq.top(); 
		pq.pop(); 
		int d = T.fi, u = T.se; 
		if(d > dis[u]) continue; 
		for(auto tmp : adj[u]) {
			int v = tmp.fi, w = tmp.se; 
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w; 
				pq.push({dis[v], v}); 
			}
		}
	}
	for(int i = 1; i <= n; i++) cout << dis[i] << ' '; 
	cout << '\n'; 
}

int cntRelax[maxN]; 
bool inq[maxN]; 

void spfa(int root) {
	for(int i = 1; i <= n; i++) dis[i] = INF, cntRelax[i] = 0; 
	queue<int> q;  
	dis[root] = 0; 
	q.push(root); 
	inq[root] = true; 
	while(!q.empty()) {
		int u = q.front(); q.pop(); 
		inq[u] = false; 
		for(auto T : adj[u]) {
			int v = T.fi, w = T.se; 
			if(dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w; 
				if(!inq[v]) {
					cntRelax[v]++; 
					inq[v] = true; 
					q.push(v); 
					if(cntRelax[v] == n) { 
						cout << "negative cycle found\n"; 
						return; 
					}
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) cout << dis[i] << ' '; 
	cout << '\n'; 
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v, w; 
		cin >> u >> v >> w; 
		adj[u].pb({v, w}); 
		adj[v].pb({u, w}); 
	}
	for(int i = 1; i <= n; i++) {
		cout << "root: " << i << '\n'; 
		dijkstra(i); 
		spfa(i); 
	}
}

