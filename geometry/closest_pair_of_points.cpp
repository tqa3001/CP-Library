#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int maxN = 2e5 + 5; 
const ll INF = numeric_limits<ll>::max(); 

ll sq(ll x) {
	return x * x; 
}

struct Point {
	ll x, y; 
	Point() {}; 
	Point(ll x, ll y) : x(x), y(y) {}; 
	inline ll operator* (const Point &oth) {
		return x * oth.y - y * oth.x; 
	}
	inline Point operator- (const Point &oth) {
		return Point(x - oth.x, y - oth.y); 
	}
	inline ll dis(const Point &oth) {
		return sq(x - oth.x) + sq(y - oth.y);  
	}
} P[maxN], tmp[maxN];

bool cmp_x(const Point &a, const Point &b) {
	if(a.x != b.x) return a.x < b.x; 
	return a.y < b.y; 
}

bool cmp_y(const Point &a, const Point &b) {
	if(a.y != b.y) return a.y < b.y; 
	return a.x < b.x; 
}

int n; 

ll Solve(int l, int r) {
	if(r - l <= 2) {
		ll ret = INF; 
		for(int i = l; i <= r; i++) {
			ret = min(ret, P[i].dis(P[(i == r ? l : i + 1)])); 
		}
		sort(P + l, P + r + 1, cmp_y); 
		return ret; 
	}
	int mid = (l + r) >> 1; 
	ll ret = min(Solve(l, mid), Solve(mid + 1, r)); 
	merge(P + l, P + mid + 1, P + mid + 1, P + r + 1, tmp + l, cmp_y); 
	for(int i = l; i <= r; i++) {
		P[i] = tmp[i]; 
	}
	for(int i = l, ptr = l; i <= r; i++) {
		if(sq(P[i].x - P[mid].x) <= ret) {
			while(ptr < i && sq(P[ptr].y - P[i].y) > ret) ptr++; 
			for(int j = ptr; j < i; j++) {
				ret = min(ret, P[i].dis(P[j])); 
			}
		}
	}
	return ret; 
}

signed main() {
	cin >> n; 
	for(int i = 1; i <= n; i++) {
		cin >> P[i].x >> P[i].y; 
	}
	sort(P + 1, P + n + 1, cmp_x); 
	cout << Solve(1, n); 
}
