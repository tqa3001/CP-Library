#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back 
using namespace std;
typedef pair<int, int> ii;  

const int maxN = 2e5 + 5, maxM = 3e5 + 5, maxTree = 5e5 + 5;   
int n, m, q; 

struct Edge {
	int u, v, remtime; 
	bool operator< (const Edge &oth) {
		return remtime > oth.remtime; 
	}
} E[maxM]; 

int value[maxN]; 

vector<ii> askQ; 

int dsu[maxN + maxM];
void initDsu(int N) { for(int i = 1; i <= N; i++) dsu[i] = i; }
int Find(int x) { return x == dsu[x] ? x : dsu[x] = Find(dsu[x]); } 

int RTNodes; 
int w[maxTree]; 
vector<int> RT[maxTree]; 
bool hasParent[maxTree]; 

int jump[maxTree][22];  

int eulerCnt = 1;
int s[maxTree], e[maxTree]; 

void dfs(int u, int p) {
	s[u] = eulerCnt++; 
   	jump[u][0] = p; 
	for(int i = 1; i < 20; i++) {
		jump[u][i] = jump[jump[u][i - 1]][i - 1];
	}
	for(auto &v : RT[u]) {
		dfs(v, u); 
	}
	e[u] = eulerCnt - 1; 
}

int getAncestor(int u, int rem) {
	for(int i = 19; i >= 0; i--) {
		if(w[jump[u][i]] > rem) 
			u = jump[u][i]; 
	}
	return u; 
}

const int ST_SIZE = 4 * maxTree; 
int st[ST_SIZE], index[ST_SIZE]; 

void update(int i, int l, int r, int id, int val) {
	if(l == r) st[i] = val, index[i] = id;  
	else {
		int mid = (l + r) >> 1; 
		if(id <= mid) update(i << 1, l, mid, id, val); 
		else {
			update(i << 1 | 1, mid + 1, r, id, val); 
		}
		if(st[i << 1] > st[i << 1 | 1]) 
			st[i] = st[i << 1], index[i] = index[i << 1]; 
		else 
			st[i] = st[i << 1 | 1], index[i] = index[i << 1 | 1];  
	}
}

ii getMax(int i, int l, int r, int L, int R) {
	if(R < l || r < L || L > R) return {-1, -1}; 
	if(L <= l && r <= R) {
		return {st[i], index[i]}; 
	}
	int mid = (l + r) >> 1; 
	return max(getMax(i << 1, l, mid, L, R), getMax(i << 1 | 1, mid + 1, r, L, R)); 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	cin >> n >> m >> q;
	for(int i = 1; i <= n; i++) {
		cin >> value[i]; 
	}
	for(int i = 1; i <= m; i++) {
		cin >> E[i].u >> E[i].v; 
		E[i].remtime = q + 1; 
	} 
	for(int i = 1; i <= q; i++) {
		int type; cin >> type; 
		if(type == 1) {
			int u; cin >> u; 
			askQ.pb({u, i}); 
		}
		else {
			int edgeId; cin >> edgeId; 
			E[edgeId].remtime = i; 
		}
	}
	sort(E + 1, E + m + 1); 
	initDsu(n + m); 
	RTNodes = n; 
	for(int i = 1; i <= n; i++) {
		w[i] = q + 1; 
	}
	for(int i = 1; i <= m; i++) {
		int u = Find(E[i].u), v = Find(E[i].v); 
		w[++RTNodes] = E[i].remtime; 
		dsu[u] = dsu[v] = RTNodes; 		
		hasParent[u] = hasParent[v] = true; 
		RT[RTNodes].pb(u); 
		if(u != v) 	
			RT[RTNodes].pb(v); 
	}
	vector<int> vert; 
	for(int i = 1; i <= n + m; i++) 
		if(!hasParent[i]) 
			vert.pb(i);
	assert(!vert.empty());  
	if((int)vert.size() > 1) {
		RTNodes++; 
		for(auto u : vert) {
			RT[RTNodes].pb(u); 
		}
		w[RTNodes] = 0;
	}
	dfs(RTNodes, RTNodes);
	for(int i = 1; i <= n + m; i++) {
		update(1, 1, RTNodes, i, -1); 
	}
	for(int i = 1; i <= n; i++) {
		update(1, 1, RTNodes, s[i], value[i]); 
	}
	for(auto &T : askQ) {
		int u = T.fi, id = T.se; 
		int p = getAncestor(u, id); 
		ii tmp = getMax(1, 1, RTNodes, s[p], e[p]); 
		cout << tmp.fi << '\n'; 
		update(1, 1, RTNodes, tmp.se, 0);  
	}
}