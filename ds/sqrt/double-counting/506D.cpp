#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 

const int maxN = 1e5 + 5, blocksize = 320; 

int n, m, q; 
int A[maxN], B[maxN], color[maxN]; 

vector<int> edges[maxN]; 

struct Query {
	int u, v, qtime; 
	bool operator< (const Query &oth) {
		return make_pair(u, v) < make_pair(oth.u, oth.v); 
	}
} Q[maxN]; 

struct dsu {
	int N; 
	vector<int> p, sz; 
	dsu() {}
	dsu(int N) : N(N) {
		p.resize(N + 1), sz.resize(N + 1); 
		for(int i = 1; i <= N; i++) 
			p[i] = i, sz[i] = 1; 
	}
	int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }
	bool isSameSet(int u, int v) { return find(u) == find(v); }
	void merge(int u, int v) {
		u = find(u), v = find(v); 
		if(u != v) {
			if(sz[u] < sz[v]) swap(u, v);
			sz[u] += sz[v]; 
			p[v] = u;  
		}
	}
} Graph[2005];  

int big; 

void solveBig(int c) {
	Graph[++big] = dsu(n); 
	for(auto &id : edges[c]) {
		Graph[big].merge(A[id], B[id]); 
	}
}

struct chash { 
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};
__gnu_pbds::gp_hash_table<ll, int, chash> M({},{},{},{},{1<<16}); 

inline ll getHash(const int &i, const int &j) {
	return (ll) i * INT_MAX + j; 
}

int ans[maxN]; 
int ansSmall[maxN]; 

void solveSmall(int c) {
	vector<int> vert; 
	for(auto &id : edges[c]) {
		vert.pb(A[id]); 
		vert.pb(B[id]); 
	}
	sort(all(vert)); 
	vert.resize(unique(all(vert)) - vert.begin()); 
	int N = vert.size(); 
	dsu G(N); 
	for(auto &id : edges[c]) {
		int u = lower_bound(all(vert), A[id]) - vert.begin() + 1; 
		int v = lower_bound(all(vert), B[id]) - vert.begin() + 1; 
		G.merge(u, v); 
	}
	for(int i = 0; i < N; i++) {
		for(int j = i + 1; j < N; j++) {
			int u = vert[i], v = vert[j]; 
			if(u > v) swap(u, v); 
			auto queryIdx = M.find(getHash(u, v));  
			if(queryIdx != M.end()) {
				ansSmall[(*queryIdx).second] += G.isSameSet(i + 1, j + 1); 
			}
		}
	}
}

signed main() {
	cin >> n >> m; 
	for(int i = 1; i <= m; i++) {
		cin >> A[i] >> B[i] >> color[i]; 
		edges[color[i]].pb(i); 
	}
	vector<int> smallSet; 
	for(int c = 1; c <= m; c++) {
		if((int)edges[c].size() > blocksize) {
			solveBig(c); 
		}
		else smallSet.pb(c); 
	}
	cin >> q; 
	for(int i = 1; i <= q; i++) {
		cin >> Q[i].u >> Q[i].v; 
		if(Q[i].u > Q[i].v) swap(Q[i].u, Q[i].v); 
		Q[i].qtime = i; 
	}
	sort(Q + 1, Q + q + 1); 
	for(int i = 1; i <= q; i++) {
		ll hsh = getHash(Q[i].u, Q[i].v); 
		M[hsh] = Q[i].qtime; 
	}
	for(auto &c : smallSet) 
		solveSmall(c); 
	for(int i = 1; i <= q;) {
		int j = i; 
		while(j <= q && Q[i].u == Q[j].u && Q[i].v == Q[j].v) j++; 
		ans[Q[j - 1].qtime] += ansSmall[Q[j - 1].qtime]; 
		for(int id = 1; id <= big; id++) {
			ans[Q[j - 1].qtime] += Graph[id].isSameSet(Q[j - 1].u, Q[j - 1].v); 
		}
		while(i < j) {
			ans[Q[i].qtime] = ans[Q[j - 1].qtime]; 
			i++; 
		}
	}
	for(int i = 1; i <= q; i++)
		cout << ans[i] << '\n'; 
}