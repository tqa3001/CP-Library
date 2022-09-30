/*
	Template for modular arithmetic problems. 
	- currently only works for prime modulos. 
	- inspired by benq's template: https://github.com/bqi343/USACO/
	Convention: use mint for calculating, int / ll for comparing. 
*/
#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;
 
const ll mod = 1e9 + 7; 

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

signed main() {
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 
	const int threshold = 1e7; // 1e8 -> 700ms on cf.  
	for(int i = 1; i <= threshold; i++) {
		mint a = rng(), b = rng(); 
		a = (a + b) * a * a - b * 3; 
	}
	mint a = 5, b = 2e9, p = 9, q = 3;  
	cout << a + (ll)2e9 << ' ' << a + b << '\t' << p / q << '\n'; 
	cout << "add mod to a: " << a + mod << '\n'; 
	mint pw = 1; 
	cout << "power of twos: \n"; 
	for(int i = 1; i < 40; i++) {
		cout << (pw *= 2) << ' '; 
	}
} 
