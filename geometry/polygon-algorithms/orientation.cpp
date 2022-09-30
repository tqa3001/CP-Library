/*
	- Check if a simple polygon is listed in counter-clockwise (return true) / clockwise (return false)
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std; 
typedef long long ll; 

struct Point {
	ll x, y; 
	Point() {} 
	Point(ll x, ll y) : x(x), y(y) {} 
	inline ll operator* (const Point &oth) const {
		return x * oth.y - y * oth.x; 
	}
	inline Point operator- (const Point &oth) const {
		return Point(x - oth.x, y - oth.y); 
	}
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; } 

using Polygon = vector<Point>; 

bool orientation(const Polygon &poly) {
	assert(!poly.empty()); 
	int n = poly.size(), mnId = 0; 
	for(int i = 1; i < n; i++) 
		if(poly[i].x < poly[mnId].x)
			mnId = i; 
	return (poly[(mnId - 1 + n) % n] - poly[mnId]) * (poly[(mnId + 1) % n] - poly[mnId]) < 0; 
}

signed main() {
	int n; cin >> n; 
	Polygon poly(n); 
	for(int i = 0; i < n; i++) cin >> poly[i]; 
	cout << orientation(poly); 
}
