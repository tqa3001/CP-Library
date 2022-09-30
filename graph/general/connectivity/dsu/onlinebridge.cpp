#include <bits/stdc++.h>
#define pb push_back
using namespace std;

int n, q;

int dsu[50005], p[50005], sz[50005]; 
int parent[50005]; 
int color[50005]; 

int Find_com(int x) {
	return x == dsu[x] ? x : dsu[x] = Find_com(dsu[x]); 
}

void Merge_com(int u, int v) {
	u = Find_com(u), v = Find_com(v); 
	if(u == v) return; 
	dsu[v] = u; 
} 

int Find(int x) {
	return x == p[x] ? x : p[x] = Find(p[x]); 
}

void Merge(int u, int v) {
	u = Find(u), v = Find(v);
	if(u == v) return; 
	p[v] = u; 
}

void Reroot(int u) {
	int pre = u; 
	while(u) {
		int nxt = Find(parent[u]); 
		parent[u] = pre; 
		pre = u; 
		u = nxt; 
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	int test; 
	cin >> test; 
	while(test--) {
		cin >> n >> q; 
		for(int i = 1; i <= n; i++) {
			sz[i] = 1; 
			dsu[i] = p[i] = i; 
			color[i] = parent[i] = 0; 
		}
		int bridges = 0; 
		for(int i = 1; i <= q; i++) {
			int u, v; 
			cin >> u >> v; 
			u++; 
			v++; 
			u = Find(u), v = Find(v); 
			int pu = Find_com(u), pv = Find_com(v); 
			if(pu != pv) {
				if(sz[pu] < sz[pv]) {
					swap(u, v); 
					swap(pu, pv); 
				}
				Reroot(v); 
				parent[v] = u; 
				Merge_com(pu, pv); 
				bridges++; 
			}
			else {
				int cur_u = u, cur_v = v; 
				int lca; 
				while(cur_u or cur_v) {
					if(cur_u) {
						if(color[cur_u] == -i) {
							lca = cur_u;
							break; 
						}
						color[cur_u] = i; 
						cur_u = Find(parent[cur_u]); 
					}
					if(cur_v) {
						if(color[cur_v] == i) {
							lca = cur_v;
							break; 
						}
						color[cur_v] = -i; 
						cur_v = Find(parent[cur_v]); 
					}
				}
				while(u != lca) {
					int nxt = Find(parent[u]); 
					Merge(nxt, u); 
					u = nxt; 
					bridges--; 
				}
				while(v != lca) {
					int nxt = Find(parent[v]); 
					Merge(nxt, v); 
					v = nxt; 
					bridges--; 
				}
			}
			cout << bridges << '\n'; 
		}	
	}
}
