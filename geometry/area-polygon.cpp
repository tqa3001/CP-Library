#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
 
struct Point {
	ll x, y; 
	Point() {}; 
	Point(ll x, ll y) : x(x), y(y) {}; 
	inline ll operator* (const Point &oth) {
		return x * oth.y - oth.x * y;  
	}
	Point operator- (const Point &oth) {
		return Point(x - oth.x, y - oth.y); 
	}
	Point operator-= (const Point &oth) {
		x -= oth.x, y -= oth.y; 
		return (*this); 
	}
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
 
signed main() {
	int n; cin >> n; 
	vector<Point> P(n); 
	for(int i = 0; i < n; i++) cin >> P[i]; 
	int area = 0; 
	for(int i = 0; i < n; i++) {
		area += (P[i] - P[0]) * (P[(i + 1) % n] - P[0]);
	}
	cout << abs(area); // 2 times of the area. 
}
