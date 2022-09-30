/*
	- inside() -> check if point T is inside (0) / outside (1) / on the boundary of (simple) polygon P (2) 
	- status: ac-ed on CSES 
*/
#include <bits/stdc++.h>
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
	inline ll triangle(const Point &a, const Point &b) const {
		return (a - *this) * (b - *this); 
	}
	inline bool betw(const Point &a, const Point &b) const {
		bool okX = x >= min(a.x, b.x) && x <= max(a.x, b.x); 
		bool okY = y >= min(a.y, b.y) && y <= max(a.y, b.y); 
		return !triangle(a, b) && okX && okY;
	}
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
ostream &operator<< (ostream &os, Point &P) { return os << P.x << ' ' << P.y; }  

using Polygon = vector<Point>; 

int inside(const Polygon &P, const Point &T) {
	bool ret = 0; 
	int N = P.size(); 
	for(int i = 0; i < N; i++) {
		if(T.betw(P[i], P[(i + 1) % N])) return 2; 
		// the following line is equivalent to: consider the vector that goes from the point with lower x -> point with greater x, and ccw it. 
		ret ^= ((P[i].x <= T.x) - (P[(i + 1) % N].x <= T.x)) * T.triangle(P[i], P[(i + 1) % N]) > 0; 
	}
	return ret; 
} 

signed main() {
	int n, m; 
	cin >> n >> m;
	Polygon P(n);  
	for(int i = 0; i < n; i++) cin >> P[i]; 
	for(int i = 0; i < m; i++) {
		Point T; 
		cin >> T.x >> T.y; 
		int ans = inside(P, T);
		if(!ans) {
			cout << "OUTSIDE\n"; 
		} 
		else if(ans == 1) cout << "INSIDE\n"; 
		else cout << "BOUNDARY\n"; 
	}
}
