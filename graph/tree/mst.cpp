#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxN = 2e5 + 5; 
int n, m; 

struct Edge {
	int u, v, w;
	bool operator < (const Edge &oth) {
		return w < oth.w; 
	} 
} E[maxN];

vector<int> adj[maxN]; 
int p[maxN]; 

void init() {
	for(int i = 1; i <= n; i++) p[i] = i; 
}

int Find(int x) {
	return x == p[x] ? x : p[x] = Find(p[x]); 
}

bool Merge(int u, int v) {
	u = Find(u), v = Find(v); 
	if(u == v) return false; 
	p[u] = v; 
	return true; 
}

void kruskal() {
	sort(E + 1, E + m + 1); 
	init(); 
	int mst = 0; 
	for(int i = 1; i <= m; i++) {
		if(Merge(E[i].u, E[i].v)) {
			mst += E[i].w; 
		}
	}
	cout << "kruskal mst: " << mst << '\n'; 
}

int mnEdge[maxN]; 

void boruvka() {
	int mst = 0;
	init(); 
	for(int it = 1; it <= 20; it++) {
		for(int i = 1; i <= n; i++) {
			mnEdge[i] = -1; 
		}
		for(int i = 1; i <= m; i++) {
			int u = E[i].u, v = E[i].v, w = E[i].w; 
			u = Find(u), v = Find(v); 
			if(u != v) {
				if(mnEdge[u] == -1 or E[mnEdge[u]].w > w) mnEdge[u] = i; 
				if(mnEdge[v] == -1 or E[mnEdge[v]].w > w) mnEdge[v] = i; 
			}
		}
		for(int i = 1; i <= n; i++) {
			if(mnEdge[i] != -1 and Merge(E[mnEdge[i]].u, E[mnEdge[i]].v)) {
				mst += E[mnEdge[i]].w; 
			}
		}
	}
	cout << "boruvka mst: " << mst << '\n'; 
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		cin >> E[i].u >> E[i].v >> E[i].w; 
	}
	kruskal(); 
	boruvka(); 
}
