#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int INF = numeric_limits<int>::max() / 2; 

int n, m;
int tot; 
int posSeg[100005], idinSeg[5005], inv[100005]; 

vector<int> target[5005], vert[5005]; 
bool omg[5005], byOmg[5005];  

struct Dinitz {
	struct Edge {
		int u, v, f; 
	};
	vector<Edge> E;  
	vector<int> adj[100005]; 
	int dis[100005], ptr[100005]; 
	int S, T, Nodes; 
	void add(int u, int v, int w) {
		E.pb({u, v, w}); 
		E.pb({v, u, 0}); 
		adj[u].pb((int)E.size() - 2); 
		adj[v].pb((int)E.size() - 1); 
	}
	bool bfs() {
		for(int i = 0; i <= Nodes; i++) dis[i] = INF; 
		dis[S] = 0; 
		queue<int> q; 
		q.push(S); 
		while(!q.empty()) {
			int u = q.front(); q.pop(); 
			for(auto id : adj[u]) {
				int v = E[id].v, f = E[id].f; 
				if(f && dis[v] > dis[u] + 1) {
					dis[v] = dis[u] + 1; 
					q.push(v); 
				}
			}
		}
		return dis[T] < INF; 
	}
	int dfs(int u, int flow) {
		if(u == T || !flow) return flow; 
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
	int traverse(int u) {
		for(auto id : adj[u]) {
			if(E[id].v != T && E[id].v > u && E[id ^ 1].f) {
				E[id ^ 1].f--; 
				return traverse(E[id].v); 
			}
		} 
		return u; 
	}
} Flow;

void build(int i, int l, int r) {
	posSeg[i] = ++tot; 
	if(l == r) {
		idinSeg[l] = i;  
		inv[posSeg[i]] = l; 
		return; 
	}
	int mid = (l + r) >> 1; 
	build(i << 1, l, mid); 
	build(i << 1 | 1, mid + 1, r); 
	Flow.add(posSeg[i], posSeg[i << 1], INF); 
	Flow.add(posSeg[i], posSeg[i << 1 | 1], INF); 
}

void addSeg(int i, int l, int r, int id, int L, int R) {
	if(R < l || r < L || L > R) return; 
	if(L <= l && r <= R) {
		Flow.add(id, posSeg[i], INF); 
		return; 
	}
	int mid = (l + r) >> 1; 
	addSeg(i << 1, l, mid, id, L, R); 
	addSeg(i << 1 | 1, mid + 1, r, id, L, R); 
}

void addSeg(int id, int L, int R) {
	addSeg(1, 1, m, id, L, R); 
}

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); 
	cin >> n >> m; 
	tot = n; 
	build(1, 1, m); 
	Flow.S = 0; 
	Flow.T = Flow.Nodes = ++tot;  
	for(int i = 1; i <= m; i++) {
		Flow.add(posSeg[idinSeg[i]], Flow.T, 1); 
	}
	for(int i = 1; i <= n; i++) {
		int type; 
		cin >> type; 
		Flow.add(0, i, (type == 2 ? 2 : 1)); 
		if(type == 2) {
			omg[i] = true; 
		}
		if(!type) {
			int sz; 
			cin >> sz; 
			for(int j = 1; j <= sz; j++) {
				int id; cin >> id; 
				addSeg(i, id, id); 
			}
		}
		else if(type == 1) {
			int l, r; 
			cin >> l >> r; 
			addSeg(i, l, r); 
		}
		else {
			for(int j = 0; j < 3; j++) {
				int id; cin >> id;  
				addSeg(i, id, id); 
				vert[i].push_back(id); 	
			}
		}
	}
	int ans = Flow.maxflow();
	for(int i = 1, id; i <= n; i++) {
		while((id = Flow.traverse(i)) != i) target[i].pb(inv[id]); 
		if(omg[i]) for(auto x : target[i]) byOmg[x] = true;  
	}
	for(int i = 1; i <= n; i++) {
		if(omg[i] && (int)target[i].size() == 1) {
			for(auto x : vert[i]) {
				if(!byOmg[x]) {
					byOmg[x] = true; 
					target[i].push_back(x); 
					break; 
				}
			}
		}
	}
	cout << ans << '\n'; 
	for(int i = 1; i <= n; i++) {
		for(auto id : target[i]) {
			if(!omg[i] && byOmg[id]) continue; 
			cout << i << ' ' << id << '\n'; 
		}
	}
}
