#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll; 
typedef vector<int> vi; 
typedef vector<ll> vll; 

const int MAX_PR = 1e7; 
int lp[MAX_PR + 5], phi[MAX_PR + 5]; 

void Sieve(int N) {
	for(int i = 1; i <= N; i++) {
		lp[i] = phi[i] = i; 
	}
	for(int i = 2; i <= N; i++) {
		if(lp[i] == i) {
			for(int j = i; j <= N; j += i) {
				lp[j] = min(lp[j], i); 
				phi[j] -= phi[j] / i; 
			}
		}
	}
}

vi fac(int x) {
	vi ret; 
	while(x > 1) {
		ret.pb(lp[x]); 
		x /= lp[x]; 
	}
	return ret; 
}

vll segmentedSieve(ll L, ll R) {
	assert(R <= (ll)1e18); 
	vector<bool> isp(R - L + 1, true); 
	int sqr = sqrt(R); 
	Sieve(sqr); 
	for(int i = 2; i <= sqr; i++) {
		if(lp[i] == i) {
			for(ll j = (ll) max((ll) i, (L + i - 1) / i) * i; j <= R; j += i) {
				isp[j - L] = false; 
			}
		}
	}
	vll ret; 
	for(int i = 0; i < R - L + 1; i++) {
		if(isp[i] && i + L != 1) ret.pb(i + L); 
	}
	return ret; 
}

signed main() {
	Sieve(MAX_PR); 
	cout << "test lp, phi: \n"; 
	for(int i = 1; i <= 20; i++) {
		cout << lp[i] << ' ' << phi[i] << '\n'; 
	}
	cout << "fac: \n"; 
	int q; 
	cin >> q; 
	while(q--) {
		int x; 
		cin >> x; 
		vi ans = fac(x); 
		for(auto x : ans) cout << x << ' '; cout << '\n'; 
	}
	cout << "segmented sieve: \n"; 
	ll L, R; 
	cin >> L >> R; 
	vll res = segmentedSieve(L, R); 
	for(auto x : res) cout << x << ' ';
}
