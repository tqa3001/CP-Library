#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll; 
typedef vector<int> vi; 
typedef vector<ll> vll; 

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

inline ll mul(ll a, ll b, ll mod) {
	ll ret = 0; 
	while(b) {
		if(b & 1) ret = (ret + a) % mod; 
		a = a * 2 % mod; 
		b >>= 1; 
	}
	return ret; 
}

inline ll bp(ll a, ll n, ll mod) {
	ll ret = 1; 
	while(n) {
		if(n & 1) ret = mul(ret, a, mod); 
		a = mul(a, a, mod); 
		n >>= 1; 
	}
	return ret; 
}

bool miller_rabin(ll p) {
	if(p <= 5) { return p == 2 || p == 3 || p == 5; }
	ll s = p - 1, k = 0; 
	while(!(s & 1)) {
		k++; 
		s >>= 1;
	}
	for(int t = 1; t <= 5; t++) {
		ll a = rng() % (p - 3) + 2; 
		a = bp(a, s, p); 
		bool bad = true; 
		if((a + p - 1) % p == 0) bad = false; 
		for(int i = 1; i <= k; i++) {
			if((a + 1) % p == 0) bad = false; 
			a = mul(a, a, p); 
		}
		if(bad) return false; 
	}
	return true; 
}

ll f(ll x, ll b, ll c, ll mod) {
	return (mul(x, x, mod) + mul(b, x, mod) + c) % mod; 
}

ll _rho(const ll &x) {
	ll b = rng(), c = rng(); 
	ll tortoise = 2, hare = 2, g = 1; // easy to forget this part
	while(g == 1) {
		tortoise = f(tortoise, b, c, x); 
		hare = f(f(hare, b, c, x), b, c, x); 
		g = __gcd(abs(tortoise - hare), x); 
	}
	return g; 
}

ll rho(const ll &x) { 
	ll ret; 
	while((ret = _rho(x)) == x); 
	return ret; 
}

vll res; 

void fac(const ll &n) {
	if(miller_rabin(n)) {
		res.pb(n); 
		return; 
	}
	ll d = rho(n); 
	fac(d);
	fac(n / d); 
}

signed main() {
	while(1) {
		ll x; 
		cin >> x; 
		res.clear(); 
		fac(x); 
		for(auto val : res) {
			cout << val << ' '; 
		}
		cout << '\n'; 
	}
}
