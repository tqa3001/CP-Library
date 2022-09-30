#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization("unroll-loops, no-stack-protector")
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef pair<int, int> ii; 

constexpr int maxN = 1e5 + 5; // (m <= 1e5)
constexpr int blocksize = 750; 
int subtask, n, m, q;  

int weight[maxN]; 
ii E[maxN]; 

struct Query{ int type, id, w; };

int dsu[maxN], sz[maxN];  
int ans[maxN]; 

void initDsu(int N) { for(int i = 0; i < N; i++) dsu[i] = i, sz[i] = 1; }
int Find(int x) { return x == dsu[x] ? x : dsu[x] = Find(dsu[x]); }
void Merge(int u, int v) {
	u = Find(u), v = Find(v); 
	if(u != v) {
		if(sz[u] < sz[v]) swap(u, v); 
		dsu[v] = u; 
		sz[u] += sz[v]; 
	}
}

struct setInt {
	int x; 
	setInt(int x) : x(x) {}
	inline bool operator< (const setInt &oth) const {
		if(weight[x] != weight[oth.x]) return weight[x] > weight[oth.x]; 
		return x < oth.x; 
	}
};
set<setInt> s; 
typedef set<setInt>::iterator setIter; 

Query Q[maxN]; 
int queryCnt; 
int queryEdges[maxN], queryOrder[maxN];  
int tmp_w[maxN]; 
bool changed[maxN], vis[maxN]; 

// fwd-star
constexpr int MX = 5005;  
int fwdCnt; 
int last[maxN], to[MX], nxt[MX]; 
int edge[MX]; 

inline void addEdge(int u, int v, int i) {
	nxt[++fwdCnt] = last[u]; 
	last[u] = fwdCnt; 
	to[fwdCnt] = v; edge[fwdCnt] = i; 
}

// checked output with modal sol -> correct -> ub ??
// must remember debugging technique for query sqrt: variate the blocksize -> FORGOT TO RESET ANS. ALWAYS scan every vector / array
// to check if resetting is required. 

inline char gc() {
	static char buffer[1 << 16]; 
	static size_t ptr, sz; 
	if(ptr >= sz) {
		ptr = 0; 
		sz = fread(buffer, 1, sizeof buffer, stdin); 
	}
	return buffer[ptr++]; 
}

inline int readInt() {
	int a, c; 
	while((a = gc()) < 40); 
	if(a == '-') return -readInt(); 
	while((c = gc()) >= 48) a = (a - 48) * 10 + c; 
	return a - 48; 
}

signed main() {  
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
//	cin >> subtask >> n >> m; 
	subtask = readInt(), n = readInt(), m = readInt(); 
	for(int i = 0; i < m; i++) { // code involves a lotta vectors -> 0-indexed -> MAKE EVERYTHING 0-indexed. 
//		cin >> E[i].fi >> E[i].se >> weight[i];  
		E[i].fi = readInt(), E[i].se = readInt(), weight[i] = readInt();
		--E[i].fi, --E[i].se; 
		s.insert(setInt(i)); 
	} 
//	cin >> q; 
	q = readInt();
	for(int t = 0; t < q; t++) { // dude i overlapped variables so many times in this code !!!
		int qtype, qid, qw; // cin >> qtype >> qid >> qw; 
		qtype  = readInt(), qid = readInt(), qw = readInt(); 
		--qid;  
		Q[queryCnt++] = {qtype, qid, qw}; 
		if(queryCnt == blocksize || t == q - 1) { 
			for(int i = 0; i < m; i++) changed[i] = 0;  
			for(int i = 0; i < n; i++) last[i] = vis[i] = 0; 
			for(int i = 0; i < queryCnt; i++) ans[i] = 0; 
			int edgeCnt = 0; 
			for(int i = 0; i < queryCnt; i++) {
				if(Q[i].type == 1 && !changed[Q[i].id]) { // cleverly handling duplicate edges. 
					s.erase(setInt(Q[i].id)); 
					changed[Q[i].id] = true; 
					queryEdges[edgeCnt++] = Q[i].id; 
				}
			} 
			for(int i = 0; i < queryCnt; i++) queryOrder[i] = i; 
			sort(queryOrder, queryOrder + queryCnt, [&](const int &x, const int &y) {
				return Q[x].w > Q[y].w; 
			}); 
			initDsu(n);
			setIter ptr = s.begin(); 
			for(int qry = 0; qry < queryCnt; qry++) { // note: loops that exist just to serve the purpose of enumerating -> use vars that isn't i, j, k. 
				int Eid = queryOrder[qry]; 
				if(Q[Eid].type == 1) continue;  
				if(!s.empty()) { // cost me so much time debugging !!
					while(ptr != s.end() && weight[(*ptr).x] >= Q[Eid].w) {
						int e = (*ptr).x; 
						Merge(E[e].fi, E[e].se); 
						ptr++; 
					}
				} 
				fwdCnt = 0; 
				for(int i = 0; i < edgeCnt; i++) {
					int id = queryEdges[i], u = Find(E[id].fi), v = Find(E[id].se); 
					last[u] = last[v] = 0; 
				}
				for(int i = 0; i < edgeCnt; i++) {
					int id = queryEdges[i], u = Find(E[id].fi), v = Find(E[id].se);   
					addEdge(u, v, id); 
					addEdge(v, u, id); 
					vis[u] = vis[v] = false; 
					tmp_w[id] = weight[id]; 
				}
				for(int i = 0; i < Eid; i++) {
					if(Q[i].type == 1) {
						tmp_w[Q[i].id] = Q[i].w; 
					}
				}
				function<void(int)> dfs = [&](int u) -> void { // function<return-type(para1-type, para2-type, ...) 
					ans[Eid] += sz[u]; 
					vis[u] = true;  
					for(int i = last[u]; i; i = nxt[i]) {
						int v = to[i];
						if(!vis[v] && tmp_w[edge[i]] >= Q[Eid].w) dfs(v);  
					}
				};
				dfs(Find(Q[Eid].id)); 
			}
			for(int i = 0; i < queryCnt; i++) 
				if(Q[i].type == 2) 
					cout << ans[i] << '\n';  
				else 
					weight[Q[i].id] = Q[i].w; 
			for(int i = 0; i < edgeCnt; i++) {
				s.insert(setInt(queryEdges[i])); 
			}
			queryCnt = 0; 
		} 
	}
//   cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
}
