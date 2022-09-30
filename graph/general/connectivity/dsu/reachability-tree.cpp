/*
	https://codeforces.com/blog/entry/85714
	status: tested with 1416D. 
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef pair<int, int> ii; 

const int maxN = 1e5 + 5, maxM = 2e5 + 5, maxTree = 3e5 + 5;  
int n, m; 

vector<pair<ii, int> > E; 

int dsu[maxTree]; 

void initDsu(int N) { for(int i = 1; i <= N; i++) dsu[i] = i; }
int Find(int x) { return x == dsu[x] ? x : dsu[x] = Find(dsu[x]); }

int RTNodes; 
int RTw[maxTree]; 
vector<int> RT[maxTree];

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		int u, v, w; 
		cin >> u >> v >> w; 
		E.pb({{u, v}, w}); 
	}
	sort(all(E), [&](const pair<ii, int> &x, const pair<ii, int> &y) {
		return x.se < y.se; 
	});
	initDsu(n + m); 
	RTNodes = n; 
	for(auto &T : E) {
		int u = T.fi.fi, v = T.fi.se, w = T.se; 
		RTNodes++;
		u = Find(u), v = Find(v); 
		dsu[u] = dsu[v] = RTNodes; 
		RT[RTNodes].pb(u); 
		if(u != v) 
			RT[RTNodes].pb(v); 	
		RTw[RTNodes] = w; 
	}
}
