#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end() 
using namespace std;
typedef long long ll; 

struct Point {
	ll x, y; 
	Point() {} 
	Point(int x, int y) : x(x), y(y) {}; 
	inline ll operator* (const Point &oth) {
		return x * oth.y - y * oth.x; 
	} 
	Point operator-= (const Point &oth) {
		x -= oth.x; y -= oth.y; 
		return (*this); 
	} 
	inline bool up() { return y > 0 || (!y && x >= 0); }
	inline bool operator!= (const Point &oth) { return x != oth.x || y != oth.y; }
}; 
istream &operator>> (istream &is, Point &P) { return is >> P.x >> P.y; }
ostream &operator<< (ostream &os, const Point &P) { return os << P.x << ' ' << P.y; }

void polarSort(vector<Point> &P, const Point &origin) {
	for(auto &T : P) assert(T != origin); 
	auto cmp = [&](Point a, Point b) {
		a -= origin; b -= origin; 
		return (a.up() == b.up() ? a * b > 0 : a.up() < b.up()); 
	}; 
	sort(all(P), cmp); 
}

signed main() {
	int n; cin >> n;
	vector<Point> P(n); 
	Point origin; cin >> origin; 
	for(int i = 0; i < n; i++) cin >> P[i]; 
	polarSort(P, origin); 
	for(int i = 0; i < n; i++) cout << P[i] << '\n'; 
}