/*
	- Linear convexhull, using double to check isect
	Status: AC-ed APIO2014 Sequence. 
*/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
using namespace std; 
typedef long long ll; 
typedef long double ld; 

const ll INF = numeric_limits<ll>::max(); 

struct Line {
	ll k, m;
	int id;  
	ll f(const ll &x) { return k * x + m; }
	bool operator< (const Line &oth) {
		return mp(k, m) < mp(oth.k, oth.m); 
	}
}; 

struct cvh {
	int ptr = 0; 
	vector<Line> hull; 
	void reset() { ptr = 0; hull.clear(); }
	inline int sz() { return hull.size(); }
	bool bad(const Line &a, const Line &b, const Line &c) { 
		if(b.k == c.k && b.m <= c.m) return true; 
		return (ld) (a.m - b.m) / (ld) (b.k - a.k) >= (ld) (b.m - c.m) / (ld) (c.k - b.k); 
	}
	void add(ll k, ll m, int id) {
		Line newline = {k, m, id}; 
		while(sz() >= 2 && bad(hull[sz() - 2], hull[sz() - 1], newline)) hull.pop_back(); 
		hull.pb(newline); 
	}
	Line query(ll x) {
		if(!sz()) {
			Line amogus = {-INF, -INF, -1}; 
			return amogus; 
		}
		if(ptr >= sz())
			ptr = sz() - 1;  
		while(ptr + 1 < sz() && hull[ptr].f(x) <= hull[ptr + 1].f(x)) ptr++; 
		return hull[ptr]; 
	}
} Cvh;

signed main() {

}