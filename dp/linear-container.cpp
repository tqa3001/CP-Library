/*
	- Line convexhull for monotonic lines insertion + queries. 
	Status: 
*/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std; 
typedef long long ll; 

const ll INF = numeric_limits<ll>::max(); 

struct Line {
	ll k, m; 
	ll f(const ll &x) { return k * x + m; }
	bool operator< (const Line &oth) {
		return mp(k, m) < mp(oth.k, oth.m); 
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
	} // beware of overflow !
	void add(ll k, ll m) {
		Line newline = {k, m}; 
		while(sz() >= 2 && bad(hull[sz() - 2], hull[sz() - 1], newline)) hull.pop_back(); 
		hull.pb(newline); 
	}
	ll query(ll x) {
		if(!sz()) return -INF; 
		if(ptr >= sz())
			ptr = sz() - 1;  
		while(ptr + 1 < sz() && hull[ptr].f(x) <= hull[ptr + 1].f(x)) ptr++; 
		return hull[ptr].f(x); 
	}
};

signed main() {

}