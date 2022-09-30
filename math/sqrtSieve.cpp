#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int MAX_PR = 1e6; 
vector<int> primes; 
bool isp[MAX_PR + 5]; 

inline void Sieve(int n) {
	memset(isp, true, n + 1); 
	isp[1] = false; 
	for(int i = 2; (ll) i * i <= n; i++)  { // benchmark: changing i -> i * i doesn't yield any significant advantage in terms of runtime for n = 1e6. 
		if(isp[i]) {
			for(int j = i * i; j <= n; j += i) { // be cautious: j = i * i can result in overflow.
				isp[j] = false; 
			}
		}
	}
	for(int i = 2; i <= n; i++) {
		if(isp[i]) {
			primes.push_back(i); 
		}
	}
}

signed main() {
	Sieve(MAX_PR); 
}
