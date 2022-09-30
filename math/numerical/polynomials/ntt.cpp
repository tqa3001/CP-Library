/*
	- NTT: f * g, coeff modulo p. 
	- p = 2^k * c + 1 
	- 998244353 = 119 * (1 << 23) + 1, primitive root = 3. 
	- status: AC-ed https://judge.yosupo.jp/problem/convolution_mod (~550ms with iosbase, ~450ms with fastio)
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end() 
#define pb push_back
using namespace std;
typedef long long ll;
typedef vector<int> vi; 

const ll mod = 998244353, rt = 3, invrt = 332748118; 

struct mint { 
	ll x; 
	mint() {x = 0; }
	mint(ll _x) {
		x = (-mod < _x && _x < mod ? _x : _x % mod); 
		if(x < 0) x += mod; 
	}; 
	mint &operator= (const ll &val) { *this = mint(val); 
		return *this; } 
	mint &operator+= (const mint &oth) { *this = mint(x + oth.x);  
		return *this; }
	mint &operator-= (const mint &oth) { *this = mint(x - oth.x); 
		return *this; }
	mint &operator*= (const mint &oth) { *this = mint(x * oth.x); 
		return *this; }
	friend mint bp(mint a, const mint &n) {
		mint ret = 1; 
		ll pw = n.x; 
		while(pw) {
			if(pw & 1) ret *= a;  
			a *= a; 
			pw >>= 1;  
		}
		return ret; 
	}
	friend mint invert(const mint &a) { return bp(a, mod - 2); }
	mint &operator/= (const mint &oth) { *this *= invert(oth); 
		return *this; }
	friend bool operator== (const mint &a, const mint &b) { return a.x == b.x; } 
	friend bool operator!= (const mint &a, const mint &b) { return a.x != b.x; } 
	friend mint operator+ (mint a, const mint &b) { return a += b; }
	friend mint operator- (mint a, const mint &b) { return a -= b; }
	friend mint operator* (mint a, const mint &b) { return a *= b; }
	friend mint operator/ (mint a, const mint &b) { return a /= b; }
};
typedef vector<mint> vm; 
istream &operator>> (istream &is, mint &a) { return is >> a.x; }
ostream &operator<< (ostream &os, const mint &a) { return os << a.x; }

void ntt(vm &a, bool inv) {
	int n = a.size(), Log = 31 - __builtin_clz(n); 
	assert(__builtin_popcount(n) == 1); 
	vi rev(n); 
	for(int i = 0; i < n; i++) rev[i] = (rev[i >> 1] | (i & 1) << Log) >> 1;  
	for(int i = 0; i < n; i++) 
		if(i < rev[i]) 
			swap(a[i], a[rev[i]]); 
	for(int k = 1; k < n; (k <<= 1)) {
		mint root = (inv ? rt : invrt); 
		mint gn = bp(root, (mod - 1) / (k << 1)); 
		for(int i = 0; i < n; i += (k << 1)) {
			mint g = 1; 
			for(int j = 0; j < k; j++) {
				mint u = a[i + j], v = g * a[i + j + k]; 
				a[i + j] = u + v, a[i + j + k] = u - v; 
				g *= gn;  
			}
		}
	}
	if(inv) {
		mint tmp = invert(mint(n)); 
		for(int i = 0; i < n; i++) a[i] *= tmp; 
	}
}

vm mul(const vm &va, const vm &vb) {
	vm a(all(va)), b(all(vb)); 
	int n = (int)a.size() + (int)b.size() - 1, Log = 31 - __builtin_clz(n); 
	n = (1 << (Log + 1)); 
	a.resize(n); 
	b.resize(n); 
	ntt(a, false), ntt(b, false); 
	for(int i = 0; i < n; i++) a[i] *= b[i]; 
	ntt(a, true); 
	return a; 
}

signed main() {
	vm a, b; 
	int deg1, deg2; 
	cin >> deg1 >> deg2; 
	for(int i = 0; i < deg1; i++) {
		mint coeff; cin >> coeff; 
		a.pb(coeff); 
	}
	for(int i = 0; i < deg2; i++) {
		mint coeff; cin >> coeff; 
		b.pb(coeff); 
	}
	vm c = mul(a, b); 
	for(int i = 0; i < deg1 + deg2 - 1; i++) cout << c[i] << ' '; 
}
