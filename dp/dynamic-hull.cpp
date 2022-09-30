/*
	Dynamic convex hull. 
	Status: AC-ed many problems in the past with this code. 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const ll INF = numeric_limits<ll>::max(); 

struct Line {
	ll k, m; 
	mutable ll p; 
	bool isQuery; 
	bool operator< (const Line &oth) const {
		return oth.isQuery ? p < oth.p : k < oth.k; 
	}
};

struct convexHull : multiset<Line, less<Line> > {
	ll div(ll a, ll b) {
		return a / b - (a % b && (a ^ b) < 0); 
	}
	bool isect(iterator x, iterator y) {
		if(y == end()) {
			x->p = INF;
			return false; 
		}
		if(x->k == y->k) {
			x->p = (x->m >= y->m ? INF : -INF); 
		}
		else x->p = div(y->m - x->m, x->k - y->k); 
		return x->p >= y->p; 
	}
	void add(ll k, ll m) {
		iterator y = insert({k, m, 0, 0}), x = y, z = next(y); 
		while(isect(y, z)) z = erase(z); 
		if(x != begin() && isect(--x, y)) isect(x, erase(y)); 
		while((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y)); 
	}
	ll get(const ll &x) {
		if(empty()) return -INF; 
		auto T = lower_bound({0, 0, x, 1});
		return T->k * x + T->m; 
	}
} Cvh;

signed main() {

}
