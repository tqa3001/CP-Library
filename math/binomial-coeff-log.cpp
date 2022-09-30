#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int largeN = 2e5 + 5, mod = 1e9 + 7; 

ll bp(ll a, ll n) { 
	ll ret = 1; 
	while(n) {
		if(n & 1) ret = ret * a % mod; 
		a = a * a % mod; 
		n >>= 1;
	}
	return ret; 
}

ll fac[largeN], invfac[largeN];  

void calFactorial(int N) {
	invfac[0] = fac[0] = 1; 
	for(int i = 1; i <= N; i++) { 
		fac[i] = fac[i - 1] * i % mod; 
		invfac[i] = bp(fac[i], mod - 2); 
 	} 
}

int C(int N, int K) {
	if(N < K) return 0; 
	return fac[N] * invfac[K] % mod * invfac[N - K] % mod; 
}

signed main() {
	calFactorial(2e5); 
	while(1) {
		int n, k; 
		cin >> n >> k; 
		cout << C(n, k) << '\n'; 
	}
}