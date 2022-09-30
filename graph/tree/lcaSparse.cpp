#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxN = 2e5 + 5; 

int n; 
vector<int> adj[maxN]; 

int eulerCnt, e[maxN * 2], f[maxN]; 
int h[maxN]; 
int sp[maxN][22], Lg[maxN * 2];
 
void dfs(int u, int p) {
	e[++eulerCnt] = u; 
	f[u] = eulerCnt; 
	for(auto v : adj[u]) {
		if(v != p) {
			h[v] = h[u] + 1; 
			dfs(v, u); 
			e[++eulerCnt] = u; 
		}
	}
}

int rmq(int l, int r) {
	int Log = Lg[r - l + 1]; 
	return (h[sp[l][Log]] < h[sp[r - (1 << Log) + 1][Log]] ? sp[l][Log] : sp[r - (1 << Log) + 1][Log]); 
}

int lca(int u, int v) {
	return rmq(min(f[u], f[v]), max(f[u], f[v])); 
}

signed main() {
	cin >> n; 
	for(int i = 1; i < n; i++) {
		int u, v; 
		cin >> u >> v; 
		adj[u].pb(v); 
		adj[v].pb(u); 
	}
	dfs(1, 1);
	Lg[1] = 0;  
	for(int i = 2; i <= eulerCnt; i++) {
		Lg[i] = Lg[i / 2] + 1; 
	}
	for(int Len = 0; (1 << Len) <= eulerCnt; Len++) {
		for(int i = 1; i + (1 << Len) - 1 <= eulerCnt; i++) {
			if(!Len) sp[i][Len] = e[i]; 
			else {
				if(h[sp[i][Len - 1]] < h[sp[i + (1 << (Len - 1))][Len - 1]]) {
					sp[i][Len] = sp[i][Len - 1]; 
				}
				else sp[i][Len] = sp[i + (1 << (Len - 1))][Len - 1]; 
			} 
		}
	}
	while(1) {
		int u, v; 
		cin >> u >> v; 
		cout << lca(u, v) << '\n'; 
	}
}
