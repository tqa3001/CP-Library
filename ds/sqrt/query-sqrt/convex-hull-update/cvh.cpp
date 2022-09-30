/*
	- Task description: (according to my memory)
	- array of n elements. each element is a line y = ax + b. 
	- 2 types of query:
	1 id a b: replace line at element id with y = ax + b
	2 l r x: max of all line l -> r for x. 
	- constaints: 
	n <= 1e5, q <= 1e5. probably 5 - 7s.  
*/
#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end() 
#define mp make_pair
using namespace std;
typedef long long ll; 

const int maxN = 1e5, blocksize = 750; 
const ll INF = numeric_limits<ll>::max(); 

int n, q; 

struct Line {
	ll k, m; 
	ll f(const int &x) { return k * x + m; }
	bool operator< (const Line &oth) {
		return mp(k, m) < mp(oth.k, oth.m); 
	}
} a[maxN]; 

struct replaceQ {
	int qtime, id, k, m; 
}; 

struct queryQ {
	int qtime, l, r, x;
	bool operator< (const queryQ &oth) {
		return x < oth.x; 
	}
}; 

bool sgn(const ll &x) {
	if(!x) return 0; 
	return x > 0 ? 1 : -1; 
}

struct cvh {
	int ptr = 0; 
	vector<Line> hull; 
	void reset() { ptr = 0; hull.clear(); }
	inline int sz() { return hull.size(); }
	bool bad(const Line &a, const Line &b, const Line &c) {
		if(b.k == c.k && b.m <= c.m) return true; 
		ll denom = (b.k - a.k) * (c.k - b.k); 
		ll numer = (a.m - b.m) * (c.k - b.k) - (b.m - c.m) * (b.k - a.k); 
		return !numer || (sgn(denom) == sgn(numer)); 
	}
	void add(int k, int m) {
		Line newline = {k, m}; 
		while(sz() >= 2 && bad(hull[sz() - 2], hull[sz() - 1], newline)) hull.pop_back(); 
		hull.pb(newline); 
	}
	ll query(int x) {
		if(!sz()) return -INF; 
		while(ptr + 1 < sz() && hull[ptr].f(x) < hull[ptr + 1].f(x)) ptr++; 
		return hull[ptr].f(x); 
	}
} ST[4 * maxN];  //reset

void resetST(int i, int l, int r) {
	ST[i].reset(); 
	if(l != r) {
		int mid = (l + r) >> 1; 
		resetST(i << 1, l, mid); 
		resetST(i << 1 | 1, mid + 1, r);
	}
}

void update(int i, int l, int r, int id, int k, int m) {
	ST[i].add(k, m); 
	if(l != r) {
		int mid = (l + r) >> 1; 
		(id <= mid ? update(i << 1, l, mid, id, k, m) : update(i << 1 | 1, mid + 1, r, id, k, m)); 
	}
}

ll query(int i, int l, int r, int L, int R, int x) { // becareful when choosing type (ll / int)
	if(R < l || r < L || L > R) return -INF;
	if(L <= l && r <= R) return ST[i].query(x); 
	int mid = (l + r) >> 1; 
	return max(query(i << 1, l, mid, L, R, x), query(i << 1 | 1, mid + 1, r, L, R, x)); 
}

bool changed[maxN]; // reset 
Line tmp_line[maxN]; 

vector<int> process(vector<replaceQ> &repl, vector<queryQ> &Q, const int &block) {
	for(int i = 1; i <= n; i++) changed[i] = false; 
	resetST(1, 1, n);
	for(auto &T : repl) changed[T.id] = true;  
	vector<int> v; 
	for(int i = 1; i <= n; i++) 
		if(!changed[i]) 
			v.pb(i);
	sort(all(v), [&](const int &x, const int &y) {
		return a[x] < a[y]; 
	}); 
	for(auto i : v) 
		update(1, 1, n, i, a[i].k, a[i].m); 
	int sz = Q.size(); 
	sort(all(Q)); 
	vector<int> ans(sz);
	int tmpCnt = -1; 
	for(auto &T : Q) {
		ll mx = -INF; 
		for(auto &qry : repl) {
			tmp_line[qry.id] = a[qry.id]; 
		}
		for(auto &qry : repl) {
			if(qry.qtime < T.qtime) {
				tmp_line[qry.id] = {qry.k, qry.m}; 
			}
		}
		for(auto &qry : repl) {
			if(T.l <= qry.id && qry.id <= T.r) {
				mx = max(mx, tmp_line[qry.id].f(T.x)); 
//				cout << "peko " << qry.id << '\t' << tmp_line[qry.id].k << ' ' << tmp_line[qry.id].m << '\n';  
			}
		}
		ll tmp = query(1, 1, n, T.l, T.r, T.x); 
		mx = max(mx, tmp); 
//		cout << "query segtree: " << tmp << '\n';
		ans[++tmpCnt] = mx; 
	}
	for(auto &T : repl) {
		a[T.id] = {T.k, T.m}; 
	}
	return ans; 
}

signed main() {
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) {
		cin >> a[i].k >> a[i].m; 
	}
	for(int b = 1; b <= q; b += blocksize) {
		vector<replaceQ> repl; 
		vector<queryQ> Q; 
		for(int i = b; i <= min(b + blocksize - 1, q); i++) {
			int type; cin >> type; 
			if(type == 1) {
				int id, k, m; cin >> id >> k >> m; 
				repl.pb({i, id, k, m}); 
			}
			else {
				int l, r, x; cin >> l >> r >> x; 
			 	Q.pb({i, l, r, x}); 
			}
		}
		vector<int> res = process(repl, Q, b); 
		for(auto &val : res) {
			cout << val << '\n'; 
		} 
	}
}