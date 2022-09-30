/*
	Works for c++ >= 14.
	Doesn't make much of a difference tbh. 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

constexpr int MAX_PR = 1e6; 

template<int N> 
struct primeTable {
	bool isp[N + 1]; 
	constexpr primeTable() : isp() {
		for(int i = 2; i <= N; i++) isp[i] = true; 
		for(int i = 2; (ll) i * i <= N; i++) {
			if(isp[i]) {
				for(int j = i * i; j <= N; j += i) isp[j] = false; 
			}
		}
	}
};

signed main() {
	primeTable<MAX_PR> sieve; 
	cout << sieve.isp[7] << ' ' << sieve.isp[8]; 
}
