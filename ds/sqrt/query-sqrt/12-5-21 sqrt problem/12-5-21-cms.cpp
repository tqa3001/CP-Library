/*
	- dsu + rollbacks. 
	- tle. in order to ac, one must use dfs. 
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef pair<int, int> ii; 

const int maxN = 1e5 + 5; // (m <= 1e5)
const int blocksize = 550; 
int subtask, n, m, q;  

int weight[maxN]; 
ii E[maxN]; 

struct Query{ 
	int type, id, w; 
};

int dsu[maxN], sz[maxN];  
int ans[maxN]; 

void initDsu(int N) { for(int i = 1; i <= N; i++) dsu[i] = i, sz[i] = 1; }

struct event {
	int u, par, oldsz; 
}; 
vector<event> undo; 

void revert(const event &e) {
	dsu[e.u] = e.par; 
	sz[e.u] = e.oldsz; 
}

int Find(int x, bool rollback) {
	if(x == dsu[x]) return x; 
	int par = Find(dsu[x], rollback); 
	if(rollback) undo.pb({x, dsu[x], sz[x]});
	return dsu[x] = par;   
}

void Merge(int u, int v, bool rollback) {
	u = Find(u, rollback), v = Find(v, rollback); 
	if(u != v) {
		if(sz[u] < sz[v]) swap(u, v); 
		if(rollback) {
			undo.pb({v, v, sz[v]}); 
			undo.pb({u, u, sz[u]}); 
		}
		dsu[v] = u; 
		sz[u] += sz[v]; 
	}
}

struct setInt {
	int x; 
	setInt(int x) : x(x) {}
	bool operator< (const setInt &oth) const {
		if(weight[x] != weight[oth.x]) return weight[x] > weight[oth.x]; 
		return x < oth.x; 
	}
};
set<setInt> s; 
typedef set<setInt>::iterator setIter; 

Query Q[maxN]; 
int queryCnt; 
int queryEdges[maxN], queryOrder[maxN], inv[maxN];
vector<int> goodEdges[maxN];  
bool changed[maxN]; 

inline char gc() {
	static char buffer[1 << 16]; 
	static size_t ptr, sz; 
	if(ptr >= sz) {
		ptr = 0; 
		sz = fread(buffer, 1, sizeof buffer, stdin); 
	}
	return buffer[ptr++]; 
}

int readInt() {
	int a, c; 
	while((a = gc()) < 40); 
	if(a == '-') return -readInt(); 
	while((c = gc()) >= 48) a = (a - 48) * 10 + c; 
	return a - 48; 
}

signed main() {
	// freopen("input.txt", "r", stdin); 
	// freopen("output.txt", "w", stdout); 
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	subtask = readInt(); n = readInt(); m = readInt(); 
	for(int i = 1; i <= m; i++) {
		E[i].fi = readInt();  
		E[i].se = readInt(); 
		weight[i] = readInt(); 
		s.insert(setInt(i)); 
	} 
	q = readInt(); 
	for(int t = 1; t <= q; t++) {
		int type = readInt(), id = readInt(), w = readInt();  
		Q[queryCnt++] = {type, id, w};
		if(type == 1) {
			s.erase(setInt(id)); 
		} 
		if(t % blocksize == 0 || t == q) {
			for(int i = 1; i <= m; i++) changed[i] = false; 
			int edgecnt = 0; 
			for(int i = 0; i < queryCnt; i++) {
				if(Q[i].type == 1) {
					changed[Q[i].id] = true; 
					queryEdges[edgecnt++] = Q[i].id; 
				}
			}
			for(int i = 0; i < queryCnt; i++) {
				goodEdges[i].clear(); 
			} 
			for(int i = 0; i < queryCnt; i++) queryOrder[i] = i; 
			sort(queryOrder, queryOrder + queryCnt, [&](const int &x, const int &y) {
				return Q[x].w > Q[y].w; 
			}); 
			for(int i = 0; i < queryCnt; i++) {
				inv[queryOrder[i]] = i; 
			}
			for(int i = 0; i < queryCnt; i++) {
				if(Q[i].type == 1) {
					weight[Q[i].id] = Q[i].w;
				}
				else {
					int pos = inv[i]; 
					for(int j = 0; j < edgecnt; j++) {
						int id = queryEdges[j];  
						if(weight[id] >= Q[i].w) {
							goodEdges[pos].pb(id); 
						}
					}
				}
			}
			initDsu(n); 
			setIter ptr = s.begin(); 
			for(int i = 0; i < queryCnt; i++) {
				int id = queryOrder[i]; 
				if(Q[id].type == 2) {
					while(ptr != s.end() && weight[(*ptr).x] >= Q[id].w) {
						int edge = (*ptr).x; 
						if(!changed[edge]) {
							Merge(E[edge].fi, E[edge].se, false); 
						}
						ptr++; 
					}
					assert(undo.empty()); 
					for(auto &edgeId : goodEdges[i]) {
						Merge(E[edgeId].fi, E[edgeId].se, true); 
					}
					ans[id] = sz[Find(Q[id].id, true)]; 
					while(!undo.empty()) {
						revert(undo.back()); 
						undo.pop_back(); 
					}
				}
			}
			for(int i = 0; i < queryCnt; i++) 
				if(Q[i].type == 2) 
					cout << ans[i] << '\n';  
			queryCnt = 0;
			for(int i = 0; i < edgecnt; i++) {
				s.insert(setInt(queryEdges[i])); 
			}
		} 
	}
}