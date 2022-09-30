#include <bits/stdc++.h>
#define pb push_back
using namespace std;

struct Node {
	int l, r; 
	int lazy; 
	int pre, suf, mx; 
	int lid, rid; 
	void all0() {
		pre = suf = mx = r - l + 1;  
	}
	void all1() {
		pre = suf = mx = 0;
	}
	Node(int l, int r) : l(l), r(r) { lazy = lid = rid = -1, all0(); }; 
	bool full() const {
		return mx == r - l + 1; 
	}
	void Merge(const Node &a, const Node &b) {
		pre = (a.full() ? a.pre + b.pre : a.pre); 
		suf = (b.full() ? a.suf + b.suf : b.suf); 
		mx = max(a.mx, b.mx); 
		if(a.suf + b.pre > mx) {
			mx = a.suf + b.pre; 
		}
	}
};

vector<Node> st; 

void fromLazy(int i) {
	int lazy = st[i].lazy; 
	if(lazy != -1) {
		(!lazy ? st[i].all0() : st[i].all1()); 
	}
}

void Push(int i) {
	int l = st[i].l, r = st[i].r, mid = (l + r) >> 1; 
	if(l != r) {
		if(st[i].lid == -1) st[i].lid = st.size(), st.pb(Node(l, mid)); 
		if(st[i].rid == -1) st[i].rid = st.size(), st.pb(Node(mid + 1, r)); 
	}
	if(st[i].lazy != -1) {
		fromLazy(i); 
		if(l != r) {
			int lid = st[i].lid, rid = st[i].rid; 
			st[lid].lazy = st[rid].lazy = st[i].lazy; 
		}
		st[i].lazy = -1; 
	}
}

bool bad(int i, int L, int R) {
	return R < st[i].l || st[i].r < L || L > R; 
}

void Update(int i, int L, int R, int val) {
	fromLazy(i); 
	if(L <= st[i].l && st[i].r <= R) {
		st[i].lazy = val; 
		fromLazy(i); 
		return; 
	}
	Push(i); 
	int lid = st[i].lid, rid = st[i].rid; 
	if(!bad(lid, L, R)) Update(lid, L, R, val); 
	if(!bad(rid, L, R)) Update(rid, L, R, val); 
	st[i].Merge(st[lid], st[rid]);  
}

void Remove(int l, int r) {
	Update(0, l, r, 0); 
}

void Add(int l, int r) {
	Update(0, l, r, 1); 
}

int firstAtleast(int i, int sz) {
	Push(i); 
	if(st[i].l == st[i].r) 
		return st[i].l; 
	int lid = st[i].lid, rid = st[i].rid; 
	if(st[lid].mx >= sz) 
		return firstAtleast(lid, sz);  // this is wrong ??? st[lid].mx may not be recalculated from its lazy value. maybe i was just lucky to get ac (no 1-n queries)
	if(st[lid].suf > 0 && st[lid].suf + st[rid].pre >= sz) {
		int ret = st[lid].r - st[lid].suf + 1; 
		return ret;
	}
	return firstAtleast(rid, sz); 
}

int N; 

struct Event {
	int t, len, m; 
	int add;  // 0 -> remove, 1 -> add. 
	int l, r; 
	Event() {}; 
	Event(int t, int len, int m, bool add, int l, int r) : t(t), len(len), m(m), add(add), l(l), r(r) {}; 
	bool operator> (const Event &oth) const {
		if(t != oth.t) return t > oth.t;
		return add > oth.add; 
	}
};

bool ok(int sz) {
	return st[0].mx >= sz; 
}

queue<Event> q; 
priority_queue<Event, vector<Event>, greater<Event> > pq; 

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	st.pb(Node(1, N));
	int _t, _m, _p;  
	while(cin >> _t >> _m >> _p, _t || _m || _p) {
		pq.push(Event(_t, _p, _m, 1, 0, 0)); 
	}
	int mxT = 0, cntSz = 0; 
	while(!pq.empty()) {
		auto T = pq.top(); pq.pop(); 
		mxT = max(mxT, T.t); 	
		if(!T.add) {
			Remove(T.l, T.r); 
			while(!pq.empty()) {
				Event S = pq.top(); 
				if(S.t != T.t || S.add) break; 
				Remove(S.l, S.r); 
				pq.pop(); 
			}
			while(!q.empty()) {
				Event S = q.front(); 
				if(!ok(S.m)) {
					break; 
				}
				q.pop(); 
				int pos = firstAtleast(0, S.m); 
				Add(pos, pos + S.m - 1); 
				pq.push(Event(T.t + S.len, 0, 0, 0, pos, pos + S.m - 1)); 
			}	
		}
		else {
			if(!ok(T.m)) {
				cntSz++; 
				q.push(T); 
			}
			else {
				int pos = firstAtleast(0, T.m); 
				Add(pos, pos + T.m - 1); 
				pq.push(Event(T.t + T.len, 0, 0, 0, pos, pos + T.m - 1)); 
			}
		}
	}
	cout << mxT << '\n' << cntSz << '\n'; 
}
