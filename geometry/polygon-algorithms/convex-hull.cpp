/*
	- convex hull
	- status: ac-ed on CSES. 
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pb push_back
using namespace std;
typedef long long ll; 
 
struct Point {
	ll x, y; 
	Point() {}; 
	Point(ll x, ll y) : x(x), y(y) {}; 
	inline ll operator* (const Point &oth) const {
		return x * oth.y - oth.x * y; 
	}
	inline Point operator- (const Point &oth) const {
		return Point(x - oth.x, y - oth.y); 
	}
	inline bool operator== (const Point &oth) const {
		return x == oth.x && y == oth.y; 
	}
	inline bool operator< (const Point &oth) const {
		return (x != oth.x ? x < oth.x : y < oth.y); 
	}
}; 

using Polygon = vector<Point>;

Polygon convexHull(vector<Point> P, bool strict) {
	// style of code: make hull more like an array -> easier to handle size conditions. 
	// corner case 1: set of Pointw == 1 point -> the code below will return an empty vector -> must be careful. 
	int N = P.size();  
	sort(all(P)); 
	vector<Point> hull(2 * N); // note: this resize function will add random weird numbers to the hull. 
	if(N == 1) {
		hull[0] = P[1]; hull.resize(1); 
		return hull; 
	}
	int lower = 0, sz = 0;    
	for(int rep = 0; rep < 2; rep++) {
		for(int i = 0; i < N; i++) {
			while(sz >= lower + 2 && (hull[sz - 2] - hull[sz - 1]) * (P[i] - hull[sz - 1]) < strict) sz--; 
			hull[sz++] = P[i]; 
		}
		reverse(all(P)); 
		lower = --sz; 
	}
	hull.resize(sz - (sz == 2 && hull[0] == hull[1])); // corner case 2: hull consists of 2 duplicating points 
	return hull; 
}
 
signed main() { 
	int n; cin >> n; 
	vector<Point> P; 
	for(int i = 0; i < n; i++) {
		Point tmp; cin >> tmp.x >> tmp.y; 
		P.pb(tmp); 
	}
	Polygon hull = convexHull(P, 0); 
	cout << (int)hull.size() << '\n'; 
	for(auto T : hull) cout << T.x << ' ' << T.y << '\n'; 
}
