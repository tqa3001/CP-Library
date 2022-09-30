#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 
typedef pair<int, int> ii; 

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); 

ll randInt(const ll &l, const ll &r) { return rng() % (r - l + 1) + l; }

void weakTree(int N) { 
	vector<int>p(N + 1, 0), idx(N + 1);
	iota(all(idx), 0); 
	shuffle(idx.begin() + 1, idx.end(), rng); 
	for(int i = 2; i <= N; i++)  
		p[i] = randInt(1, i - 1); 
	for(int i = 1; i <= N; i++) {
		int par = idx[p[i]], u = idx[i]; 
		if(par) 
			cout << par << ' ' << u << '\n'; 
	}
}

void line(int N) {
	vector<int> idx(N + 1); 
	iota(all(idx), 0); 
	shuffle(idx.begin() + 1, idx.end(), rng); 
	for(int i = 1; i < N; i++) 
		cout << idx[i] << ' ' << idx[i + 1] << '\n'; 
}

void sun(int N) {
	int root = randInt(1, N); 
	for(int i = 1; i < N; i++)
		if(i != root) 
			cout << i << ' ' << root << '\n'; 
}

void randGraph(int N, int M) { // no self-loops / multiple edges.
	set<ii> edges; 
	for(int i = 1; i <= M; i++) {
		int u = randInt(1, N), v = randInt(1, N); 
		while(u == v || edges.count({u, v}) || edges.count({v, u})) 
			u = randInt(1, N), v = randInt(1, N);
		edges.insert({u, v}); 
		cout << u << ' ' << v << '\n';   
	}
}

signed main() {
	randGraph(10, 35); 
}