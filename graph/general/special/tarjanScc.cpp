#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxN = 2e5 + 5; 

int n, m; 
vector<int> adj[maxN]; 

int dfscnt, scc; 
int num[maxN], low[maxN], comp[maxN]; 
bool inS[maxN]; 
stack<int, vector<int> > S; 

void dfs(int u) {
	num[u] = low[u] = ++dfscnt; 
	inS[u] = true; 
	S.push(u); 
	for(auto v : adj[u]) {
		if(!num[v]) {
			dfs(v); 
			low[u] = min(low[u], low[v]); 
		}
		else if(inS[v]) {
			low[u] = min(low[u], num[v]); 
		}
	}
	if(low[u] == num[u]) {
		scc++; 
		while(1) {
			int v = S.top(); S.pop(); 
			comp[v] = scc; 
			inS[v] = false; 
			if(v == u) break; 
		}
	}
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v; 
		adj[u].pb(v); 
	}
	for(int i = 1; i <= n; i++) {
		if(!num[i]) {
			dfs(i); 
		}
	}
	cout << scc << '\n';
	for(int i = 1; i <= n; i++) {
		cout << comp[i] << ' '; 
	} 
}
