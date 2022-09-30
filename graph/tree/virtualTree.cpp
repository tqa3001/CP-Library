#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end() 
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

bool isanc(int u, int v) {
	return in[u] <= in[v] && out[v] <= out[u]; 
}

int lca(int u, int v) {
	if(isanc(u, v)) return u; 
	if(isanc(v, u)) return v; 
	for(int i = 19; i >= 0; i--) {
		if(!isanc(jump[u][i], v)) u = jump[u][i]; 
	}
	return jump[u][0]; 
}

vector<int> vert, vt[maxN]; 

void virtualTree(const vector<int> &S) {
	for(auto u : vert) vt[u].clear(); 
	vert = S; 
	auto cmp = [&](const int &u, const int &v) {
		return in[u] < in[v]; 
	}; 
	sort(all(vert), cmp); 
	for(int i = 0, sz = vert.size(); i < sz - 1; i++) {
		vert.pb(lca(vert[i], vert[i + 1])); 
	}
	sort(all(vert), cmp); 
	vert.resize(unique(all(vert)) - vert.begin()); 
	stack<int, vector<int> > s; 
	for(auto u : vert) {
		if(s.empty()) s.push(u); 
		else {
			while(!isanc(s.top(), u)) s.pop(); 
			vt[s.top()].pb(u); 
			vt[u].pb(s.top()); 
			s.push(u); 
		}
	}
} 

signed main() {
	cin >> n; 
	for(int i = 1; i < n; i++) {
		int u, v; cin >> u >> v; 
		adj[u].pb(v);
		adj[v].pb(u); 
	}	
	dfs(1, 1);
	vector<int> S; 
	int setSize; cin >> setSize;  
	for(int i = 0; i < setSize; i++) {
		int u; cin >> u; 
		S.pb(u); 
	}
	virtualTree(S); 
	cout << "vertices in VT: \n"; 
	for(auto &u : vert) {
		cout << "vertex: " << u << '\n';
		for(auto &v : vt[u]) {
			cout << v << ' '; 
		}
		cout << '\n'; 
	}
}
