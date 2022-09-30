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
	inline Point operator- (const Point &oth) {
		return Point(x - oth.x, y - oth.y); 
	}
	inline Point operator-= (const Point &oth) {
		x -= oth.x, y -= oth.y; 
		return (*this); 
	}
};
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
 
bool sign(int x) {
	return x > 0; 
}

bool segIntersect(Point a1, Point a2, Point a3, Point a4) {
	bool ok = true; 
	// parallel lines
	if((a2 - a1) * (a4 - a3) == 0) {
		if((a3 - a1) * (a3 - a2)) ok = false; 
		else {
			for(int rep = 0; rep < 2; rep++) {
				if(max(a1.x, a2.x) < min(a3.x, a4.x) || max(a1.y, a2.y) < min(a3.y, a4.y)) ok = false; 
				swap(a1, a3); 
				swap(a2, a4); 
			}
		}
	}
	else {
		for(int rep = 0; rep < 2; rep++) {
			ll s1 = (a4 - a3) * (a1 - a3), s2 = (a4 - a3) * (a2 - a3); 
			if(s1 && s2 && sign(s1) == sign(s2)) ok = false; 
			swap(a1, a3);
			swap(a2, a4);  
		}
	}
	return ok; 
}
 
signed main() {
	int test; cin >> test; 
	while(test--) {
		Point a1, a2, a3, a4; 
		cin >> a1 >> a2 >> a3 >> a4; 
		cout << (segIntersect(a1, a2, a3, a4) ? "YES\n" : "NO\n"); 	
	}
}
