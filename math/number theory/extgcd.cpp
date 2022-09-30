/*
	- euclid(a, b, x, y): find x, y -> ax + by = gcd(a, b) in O(log) 
	- crt(a, b, n, m): x = a mod n, x = b mod m, if a < n, b < m -> x < lcm(n, m). works for nm < 2^62. complexity is also O(log)
	x = pn + a = qm + b -> qm - pn = diff (diff = a - b)
						-> if (a - b) !divisble by gcd(n, m), no solution. 
						else: solve nX + mY = gcd(n, m) (= d)
						->  n * X * diff / d + m * Y * diff / d = diff. 
						-> p = X * n * diff / d
	- why crt ? to transform a congurent eqt (ax = b mod N) to a system of congurent equations (ax = b mod pi) where p1, p2, ... are distinct primes
	of N. 
	- status: AC-ed https://open.kattis.com/problems/generalchineseremainder. 
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std; 
typedef long long ll; 
typedef pair<ll, ll> pll; 

istream &operator>> (istream &is, pll &p) { return is >> p.fi >> p.se; }
ostream &operator<< (ostream &os, const pll &p) { return os << p.fi << ' ' << p.se; } 

inline ll euclid(ll a, ll b, ll &x, ll &y) {
	if(!b) return x = 1, y = 0, a; 
	ll d = euclid(b, a % b, y, x); 
	return y -= (a / b) * x, d; 
} 

inline pll crt(const pll &P, const pll &Q) {
	ll a, n, b, m; 
	tie(a, n) = P, tie(b, m) = Q; 
	if(n > m) swap(a, b), swap(n, m); 
	ll x, y, d = euclid(n, m, x, y), lcm = n * m / d; 
	if((a - b) % d) return {-1, -1}; 
	x = (b - a) % m * x % m / d * n + a;
	return {x + (x < 0) * lcm, lcm}; 
}

pll crt(const vector<pll> &S) {
	assert(!S.empty()); 
	pll ret = S[0]; 
	for(int i = 1; i < (int)S.size(); i++) ret = crt(ret, S[i]); 
	return ret; 
}

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0); 
	int test; cin >> test; 
	while(test--) {
		pll p1, p2; cin >> p1 >> p2;
		pll ans = crt(p1, p2); 
		if(ans.fi == -1) cout << "no solution\n"; 
		else cout << ans << '\n'; 
	}
}

