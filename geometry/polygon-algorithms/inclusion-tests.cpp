/*
	- Check if a point lies inside a convex polygon
	- return values: 0 - outside, 1 - inside, 2 - on the boundary
	- status: AC-ed 166B
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end() 
using namespace std;
typedef long long ll; 

struct Point {
	ll x, y; 
	Point() {}; 
	Point(ll x, ll y) : x(x), y(y) {}; 
	inline ll operator* (const Point &oth) const {
		return x * oth.y - oth.x * y; 
	}
	inline Point operator- (const Point &oth) const{
		return Point(x - oth.x, y - oth.y); 
	}
	inline bool operator== (const Point &oth) const {
		return x == oth.x && y == oth.y; 
	}
	inline bool operator< (const Point &oth) const {
		return (x != oth.x ? x < oth.x : y < oth.y); 
	}
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
ostream &operator<< (ostream &os, const Point &P) { return os << P.x << ' ' << P.y; }

using Polygon = vector<Point>;

inline int sgn(const ll &x) { 
	if(!x) return 0; 
	return (x > 0 ? 1 : -1); 
}

int inclusionTriangle(const Point &P, const Polygon &triangle) {
	assert((int)triangle.size() == 3); 
	int sign[3]; 
	for(int i = 0; i < 3; i++) sign[i] = sgn((triangle[i] - P) * (triangle[(i + 1) % 3] - P)); 
	if(sign[0] == sign[1] && sign[1] == sign[2])  
		return 1; 
	for(int i = 0; i < 3; i++) 
		if(sign[i] + sign[(i + 1) % 3] == 0) 
			return 0; 
	return 2; 
}

int inclusionConvex(const Point &P, const Polygon &poly, const int &mxId) { // assuming that the point with lowest x-cordinate -> index 0 + clockwise order (typical convexhull order)
	assert(!poly.empty());
	int N = poly.size();  
	if(P.x < poly[0].x || P.x > poly[mxId].x) 
		return 0; 	
	int ccw = sgn((poly[0] - P) * (poly[mxId] - P));
	if(!ccw) {
		if(P == poly[0] || P == poly[mxId]) return 2; 
		return (mxId == 1 || mxId == N - 1 ? 2 : 1); 
	}
	else if(ccw > 0) {
		int id = lower_bound(poly.begin(), poly.begin() + mxId, P) - poly.begin(); 
		int sign = sgn((poly[(id - 1 + N) % N] - P) * (poly[id] - P)); 
		if(!sign) return 2; 
		return sign < 0; 
	}
	else {
		int id = lower_bound(poly.rbegin(), poly.rend() - mxId, P) - poly.rbegin(); 
		id = N - 1 - id; 
		int sign = sgn((poly[id] - P) * (poly[(id + 1) % N] - P)); 
		if(!sign) return 2; 
		return sign < 0; 
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	int n; 
	cin >> n; 
	Polygon poly(n); 
	for(int i = 0; i < n; i++) cin >> poly[i]; 
	int mnId = min_element(all(poly)) - poly.begin(); 
	rotate(poly.begin(), poly.begin() + mnId, poly.end()); 
	int mxId = max_element(all(poly)) - poly.begin(); 
	int m; 
	cin >> m; 
	bool ok = true; 
	for(int i = 0; i < m; i++) {
		Point P; 
		cin >> P; 
		ok &= (inclusionConvex(P, poly, mxId) == 1); 
	}	
	cout << (ok ? "YES" : "NO"); 
}