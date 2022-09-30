#include <bits/stdc++.h>
using namespace std;
typedef long double ld; 
typedef long long ll; 

const ld INF = 1e18, eps = 1e-13; 

ll minimaInt(ll a, ll b, ll c) { // min at integer y -> l or l + 1. 
	int l = -1e6, r = 1e6; 
	auto f = [&] (const ll &x) -> ll {
		return a * x * x + b * x + c; 
	};
	while(l < r) {
		int mid = (l + r + 1) / 2; 
		if(f(mid) > f(mid - 1)) r = mid - 1; 
		else l = mid; 
	}
	return l; 
}

ld minima(ld a, ld b, ld c) { // y = ax^2 + bx + c, concave
	ld l = -1e6, r = 1e6; 
	auto f = [&] (const ld &x) -> ld {
		return a * x * x + b * x + c; 
	};
	for(int t = 1; t <= 200; t++) {
		ld mid1 = l + (r - l) / 3, mid2 = r - (r - l) / 3; 
		if(f(mid1) < f(mid2)) {
			r = mid2; 
		}
		else l = mid1; 
	}
	return l; 
}

ld search(ld a, ld b, ld k) { // y = ax + b, monotonic
	ld l = -1e9, r = 1e9; 
	for(int t = 1; t <= 200; t++) {
		ld mid = (l + r) / 2; 
		if((ld) a * mid + b < k) { 
			l = mid; 
		}
		else r = mid; 
	}
	return l; 
}

signed main() {
	cout << setprecision(13) << fixed; 
	while(true) {
		ld a, b, c;
		int type; cin >> type >> a >> b >> c; 
		if(type == 1) {
			cout << search(a, b, c) << '\n'; 
		}
		else if(type == 2) cout << minima(a, b, c) << '\n'; 
		else cout << minimaInt(a, b, c) << '\n'; 
	}
}
