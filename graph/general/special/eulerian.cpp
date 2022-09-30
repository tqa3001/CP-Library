#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxN = 2e5 + 5; 

int n, m; 
int A[maxN], B[maxN]; 

vector<int> adj[maxN]; 
bool vis[maxN]; 

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		cin >> A[i] >> B[i]; 
		adj[A[i]].pb(i);
		adj[B[i]].pb(i); 
	}
	bool ok = true; 
	for(int i = 1; i <= n; i++) {
		if((int)adj[i].size() & 1) {
			ok = false; 
		}
	}
	if(!ok) return cout << "Cannot find an euler cycle\n", 0; 
	for(int i = 1; i <= n; i++) {
		if(adj[i].empty()) continue; 
		vector<int> s; 
		s.pb(i); 
		while(!s.empty()) {
			int u = s.back(); 
			while(!adj[u].empty() and vis[adj[u].back()]) adj[u].pop_back(); 
			if(adj[u].empty()) {
				cout << u << '\n'; 
				s.pop_back();
			}
			else {
				int id = adj[u].back(); 
				adj[u].pop_back(); 
				int v = (A[id] == u ? B[id] : A[id]); 
				vis[id] = true; 
				s.pb(v); 
			}
		}
	}
}
