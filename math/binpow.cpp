#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
typedef long long ll;  

ll bp(ll a, ll n) { // non-recursive bp idea: n = 0101001010011 -> iterate through all the bits from low to high, if bit = 1, *= a^(2^k)
	ll ret = 1; 
	while(n) {
		if(n & 1) ret = ret * a % mod; 
		a = a * a % mod; 
		n >>= 1;
	}
	return ret; 
}

signed main() {
	while(1) {
		ll a, n; 
		cin >> a >> n; 
		cout << bp(a, n) << '\n'; 
	}
}
