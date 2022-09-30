/*
	Kuhn's algorithm for maximum bipartite matching with some heuristics
	https://codeforces.com/blog/entry/17023
	Status: AC-ed https://codeforces.com/group/FLVn1Sc504/contest/274710/problem/F
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef vector<int> vi; 

const int maxN = 5e4 + 5; 

int lside, rside, m; 
vi g[maxN], match, paired;
vector<bool> vis; 

bool tryKuhn(int u) {
	if(vis[u]) return false; 
	vis[u] = true; 
	for(auto v : g[u]) {
		if(!match[v] || tryKuhn(match[v])) {
			match[v] = u; 
			return true; 
		} 
	}	
	return false; 
}

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0); 
	cin >> lside >> rside >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v; cin >> u >> v; 
		g[u].pb(v); 
	}
	match.assign(rside + 1, 0); 
	vis.assign(lside + 1, false); 
	paired.assign(lside + 1, false); 
	bool hasPath = true; 
	while(hasPath) {
		hasPath = false; 
		vis.assign(lside + 1, false); 
		for(int i = 1; i <= lside; i++) {
			if(!paired[i] && tryKuhn(i)) {
				hasPath = true; 
				paired[i] = true; 
			}
 		}
	}
	int matching = 0; 
	for(int i = 1; i <= rside; i++) 
		if(match[i]) 
			matching++; 
	cout << matching; 
}
