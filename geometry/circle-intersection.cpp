/*
	status: stress-tested. 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long double ld; 

struct Point {
	ld x, y; 
	Point() {}; 
	Point(ld x, ld y) : x(x), y(y) {}; 
	inline ld dist2() const { return x * x + y * y; }
	inline Point operator- (const Point &oth) const { return Point(x - oth.x, y - oth.y); }
	inline Point operator+ (const Point &oth) const { return Point(x + oth.x, y + oth.y); }
	inline Point operator* (const ld T) const { return Point(x * T, y * T); }
	inline bool operator== (const Point &oth) const { return x == oth.x && y == oth.y; }
	Point perp() const {
		return Point(-y, x); // rotate 90 degrees counterclockwise.
	}
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
ostream &operator<< (ostream &os, Point &P) { return os << P.x << ' ' << P.y; }  

bool intersection(const Point &a, const Point &b, ld r1, ld r2, Point &ret1, Point &ret2) {
	if(a == b) return false; 
	Point vec = b - a; 
	ld sum = r1 + r2, diff = r1 - r2; 
	ld d2 = vec.dist2(), p = (d2 + r1 * r1 - r2 * r2) / (ld) (2 * d2);  
	if(d2 > sum * sum || d2 < diff * diff) return false; 
	ld h2 = r1 * r1 - p * p * d2; 
	Point H = a + vec * p; 
	Point per = vec.perp() * sqrt(h2 / d2);  
	ret1 = H + per, ret2 = H - per; 
	return true; 
}

signed main() {
	cout << fixed << setprecision(10); 
	Point a, b, p1, p2; 
	cin >> a >> b; 
	ld r1, r2; 
	cin >> r1 >> r2; 
	if(intersection(a, b, r1, r2, p1, p2)) {
		cout << "Yes\n" << p1 << ' ' << p2 << '\n';  
	}
	else cout << "No\n"; 
}
