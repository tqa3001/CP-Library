/*
	Given an array a 2^x integers, find: 
		zeta(mask) = sum(a[mask'] | mask' in mask) 
		mobius(mask) = sum(a[mask'] * (-1)^|mask'| | mask' in mask)
	for each mask in O(2^x * x) 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

vector<int> subOptimal(const vector<int> &a) {
	int mxMask = a.size(); 
	vector<int> dp(mxMask, 0); 
	for(int mask = 0; mask < mxMask; mask++){
		dp[mask] = a[0];
    	for(int i = mask; i; i = (i - 1) & mask){
    		dp[mask] += a[i];
    	}
	}
	return dp; 
}

vector<int> zeta(const vector<int> &a) {
	int mxMask = a.size();
	vector<int> dp(mxMask, 0);  
	for(int mask = 0; mask < mxMask; mask++) {
		dp[mask] = a[mask]; 
	}
	for(int i = 0; (1 << i) < mxMask; i++) {
		for(int mask = 0; mask < mxMask; mask++) {
			if(mask & (1 << i)) 
				dp[mask] += dp[mask ^ (1 << i)]; 
		}
	}
	return dp; 
}

vector<int> _o(const vector<int> &a) {
	vector<int> ret = a; 
	int mxMask = a.size(); 
	for(int mask = 0; mask < mxMask; mask++) {
		if(__builtin_popcount(mask) & 1) {
			ret[mask] *= -1;
		}
	}
	return ret; 
}

vector<int> mobius(const vector<int> &a) {
	return _o(zeta(_o(a))); 
}

signed main() {
	int n; cin >> n; 
	vector<int> a(n);  
	for(int i = 0; i < n; i++) cin >> a[i];
	vector<int> z = mobius(a); 
	for(int mask = 0; mask < n; mask++) {
		cout << bitset<20>(mask) << ' ' << z[mask] << '\n';  
	}
}