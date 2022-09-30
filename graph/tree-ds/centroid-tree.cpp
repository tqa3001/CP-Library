/*
	centroid tree. 
	Solution for SPOJ QTree4. 
*/
#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef pair<int, int> ii; 
typedef vector<int> vi; 
typedef vector<ii> vii; 

const int maxN = 2e5 + 5; 
int n; 
vii adj[maxN];

int dfsCnt; 
int h[maxN]; 
int in[maxN], out[maxN]; 
int jump[maxN][22]; 

void dfs(int u, int p) {
	in[u] = dfsCnt++; 
	jump[u][0] = p; 
	for(int i = 1; i < 20; i++) jump[u][i] = jump[jump[u][i - 1]][i - 1]; 
	for(auto T : adj[u]) {
		int v = T.fi, w = T.se; 
		if(v != p) {
			h[v] = h[u] + w; 
			dfs(v, u); 
		}
	}
	out[u] = dfsCnt - 1; 
}

inline bool isanc(int u, int v) { return in[u] <= in[v] && out[v] <= out[u]; }

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

int sz[maxN];  
bool vis[maxN]; 
int cpar[maxN], idx[maxN]; 
 
vector<set<ii> > childSet[maxN]; 
set<ii> bestSet[maxN]; 

void getSz(int u, int p) {
	sz[u] = 1; 
	for(auto T : adj[u]) {
		int v = T.fi; 
		if(v != p && !vis[v]) {
			getSz(v, u); 
			sz[u] += sz[v]; 
		}
	}
}

int centroid(int u, int p, int root) {
	for(auto T : adj[u]) {
		int v = T.fi; 
		if(v != p && !vis[v] && 2 * sz[v] > sz[root]) {
			return centroid(v, u, root); 
		}
	}
	return u; 
}

vector<int> subtree; 

void getSubtree(int u, int p) {
	subtree.pb(u); 
	for(auto T : adj[u]) {
		int v = T.fi; 
		if(v != p && !vis[v]) {
			getSubtree(v, u); 
		}
	}
}

int buildCT(int root) {
	getSz(root, root); 
	root = centroid(root, root, root); 
	vis[root] = true; 
	for(int i = 0; i < (int)adj[root].size(); i++) {
		int u = adj[root][i].fi; 
		if(!vis[u]) {
			subtree.clear(); 
			getSubtree(u, root); 
			set<ii> tmpSet; 
			for(auto v : subtree) {
				tmpSet.insert({dist(v, root), v}); 
			}
			childSet[root].pb(tmpSet); 	
			bestSet[root].insert(*(tmpSet.rbegin())); 
		}
	}
	bestSet[root].insert({0, root}); 
	int child = 0; 
	for(int i = 0; i < (int)adj[root].size(); i++) {
		int u = adj[root][i].fi; 
		if(!vis[u]) {
			int centroid_u = buildCT(u); 
			cpar[centroid_u] = root; 
			idx[centroid_u] = child++; 
		}
	}
	return root; 
}

int ST[4 * maxN]; 

void Update(int i, int l, int r, int id, int val) {
	if(l == r) {
		ST[i] = val; 
		return; 
	}	
	int mid = (l + r) >> 1; 
	if(id <= mid) Update(i << 1, l, mid, id, val); 
	else {
		Update(i << 1 | 1, mid + 1, r, id, val); 
	}
	ST[i] = max(ST[i << 1], ST[i << 1 | 1]); 
} 

int color[maxN]; 

void updateNode(int u) {
	int mx = -1; 
	if(!bestSet[u].empty()) {
		mx = 0; 
		if((int)bestSet[u].size() > 1) {
			set<ii>::reverse_iterator x = bestSet[u].rbegin(); 
			mx = max(mx, (*(x++)).fi + (*x).fi); 
		}
	}
	Update(1, 1, n, u, mx); 
}

void add(int u) {
	int cur = u; 
	bestSet[u].insert({0, u}); 
	updateNode(u); 
	while(cpar[cur]) {
		int nxt = cpar[cur]; 
		if(!childSet[nxt][idx[cur]].empty()) {
			bestSet[nxt].erase(*(childSet[nxt][idx[cur]].rbegin())); 
		}
		childSet[nxt][idx[cur]].insert({dist(u, nxt), u}); 
		bestSet[nxt].insert(*(childSet[nxt][idx[cur]].rbegin())); 
		updateNode(nxt); 
		cur = nxt; 
	}
}

void del(int u) {
	int cur = u; 
	bestSet[u].erase({0, u});
	updateNode(u); 
	while(cpar[cur]) {
		int nxt = cpar[cur]; 
		bestSet[nxt].erase(*(childSet[nxt][idx[cur]].rbegin())); 
		childSet[nxt][idx[cur]].erase({dist(u, nxt), u});
		if(!childSet[nxt][idx[cur]].empty()) {		
			bestSet[nxt].insert(*(childSet[nxt][idx[cur]].rbegin())); 
		} 
		updateNode(nxt); 
		cur = nxt; 
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	cin >> n; 
	for(int i = 1; i < n; i++) {
		int u, v, w; 
		cin >> u >> v >> w; 
		adj[u].pb({v, w}); 
		adj[v].pb({u, w}); 
	}	
	dfs(1, 1); 
	buildCT(1); 
	for(int i = 1; i <= n; i++) updateNode(i); 
	int q; 
	cin >> q; 
	for(int i = 1; i <= q; i++) {
		char type; 
		cin >> type; 
		if(type == 'C') {
			int u; cin >> u; 
			(!color[u] ? del(u) : add(u)); 
			color[u] ^= 1; 
		}
		else {
			if(ST[1] == -1) cout << "They have disappeared.\n"; 
			else cout << ST[1] << '\n'; 
		}
	}
}
