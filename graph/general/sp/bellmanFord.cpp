#include <bits/stdc++.h>
#define int long long
#define ii pair<int, int> 
#define fi first
#define se second
#define pb push_back
using namespace std;

const int maxN = 2e5 + 5; 
const int INF = 1e18;

int n, m, q; 
int dis[maxN], p[maxN]; 
bool vis[100005]; 

struct Edge {
	int u, v, w;  // directed 
} E[2 * maxN];

void bellmanFord(int root) {
	for(int i = 1; i <= n; i++) {
		dis[i] = INF;
		vis[i] = false;
	}
	dis[root] = 0; 
	ii last_upd = {root, 0}; 
	for(int iter = 1; iter <= n; iter++) {
		bool has_relax = false; 
		for(int i = 1; i <= m; i++) {
			int u = E[i].u, v = E[i].v, w = E[i].w; 
			if(dis[v] > dis[u] + w) {
				has_relax = true; 
				last_upd = {v, iter}; 
				dis[v] = dis[u] + w; 
				p[v] = u; 
			}
		}
		if(!has_relax) break; // significant optimization. 
	}
	if(last_upd.se == n) {
		cout << "negative cycle found! \n"; 
		vector<int> cyc; 
		int u = last_upd.fi; 
		cyc.pb(u); 
		vis[u] = true; 
		while(!vis[p[u]]) {
			cyc.pb(p[u]); 
			vis[p[u]] = true; 
			u = p[u]; 
		}
		reverse(cyc.begin(), cyc.end()); 
		while(cyc.back() != p[u]) cyc.pop_back(); 
		for(auto x : cyc) cout << x << ' '; 
		cout << '\n'; 
	}
	else {
		cout << "dis: \n"; 
		for(int i = 1; i <= n; i++) cout << dis[i] << ' '; 
		cout << '\n'; 
	}
}

signed main() {
	cin >> n >> m >> q;  
	for(int i = 1; i <= m; i++) {
		cin >> E[i].u >> E[i].v >> E[i].w; 
	}
	for(int i = 1; i <= q; i++) {
		int u; 
		cin >> u; 
		bellman_ford(u); 
	}
}
