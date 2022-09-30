/*
	O(n log n) polynomial multiplication, tested by AC-ing SPOJ POLYMUL. 
*/
#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 
typedef complex<double> cd; 
typedef vector<ll> vll; 

constexpr double pi = acos(-1); 

void fft(vector<cd> &a, bool inv) {
	int n = a.size(), Log = 31 - __builtin_clz(n);  
	assert(__builtin_popcount(n) == 1); 
	vll rev(n); 
	for(int i = 0; i < n; i++) rev[i] = (rev[i >> 1] | (i & 1) << Log) >> 1; 
	for(int i = 0; i < n; i++) 
		if(i < rev[i]) 
			swap(a[i], a[rev[i]]); 
	for(int k = 1; k < n; k <<= 1) {
		double alp = pi / k * (inv ? -1 : 1); 
		cd wn(cos(alp), sin(alp)); 
		for(int i = 0; i < n; i += (k << 1)) {
			cd w(1); 
			for(int j = 0; j < k; j++) {
				cd u = a[i + j], v = w * a[i + j + k]; 
				a[i + j] = u + v, a[i + j + k] = u - v; 
				w *= wn; 
			}
		}
	}
	if(inv) {
		for(auto &x : a) x /= n; 
	}
}

vll mul(const vll &va, const vll &vb) {
	vector<cd> a(all(va)), b(all(vb));  
	int n = (int)a.size() + (int)b.size() - 1, Lg = 31 - __builtin_clz(n); 
	n = (1 << (Lg + 1)); 
	a.resize(n);   
	b.resize(n); 
	fft(a, false), fft(b, false); 
	for(int i = 0; i < n; i++) {
		a[i] *= b[i];  
	}
	fft(a, true); 
	vll ret(n); 
	for(int i = 0; i < n; i++) {
		ret[i] = round(a[i].real());  
	}
	return ret; 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	int test; cin >> test; 
	while(test--) {
		int deg; cin >> deg; 
		vll a[2]; 
		for(int rep = 0; rep < 2; rep++) {
			for(int i = 0; i <= deg; i++) {
				int coeff; cin >> coeff; 
				a[rep].pb(coeff); 
			}
		}
		vll res = mul(a[0], a[1]);
		for(int i = 0; i <= (deg << 1); i++) {
			cout << res[i] << ' '; 
		}
		cout << '\n'; 
	}
}
