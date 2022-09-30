/*
	Solution for SPOJ KDIFF.
*/
#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e5 + 5; 
int n, k, ans;
int a[maxN], dp[maxN], pre[maxN];  

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0); 
	cin >> n >> k; 
	for(int i = 1; i <= n; i++) cin >> a[i]; 
	deque<int> mn, mx; 
	dp[0] = 1; 
	for(int i = 1; i <= n; i++) {
		while(!mn.empty() and a[mn.back()] > a[i]) mn.pop_back(); 
		while(!mx.empty() and a[mx.back()] < a[i]) mx.pop_back(); 
		mn.push_back(i), mx.push_back(i); 
		for(int j = dp[i - 1]; j <= i; j++) {
			while(!mn.empty() and mn.front() < j) mn.pop_front(); 
			while(!mx.empty() and mx.front() < j) mx.pop_front(); 
			if(a[mn.front()] >= a[i] - k and a[mx.front()] <= a[i] + k) {
				dp[i] = j; 
				break; 
			} 
		}
	}
	for(int i = 1; i <= n; i++) {
		pre[i] = max(pre[i - 1], i - dp[i] + 1); 
	}
	for(int i = 1; i <= n; i++) ans = max(ans, (i - dp[i] + 1) + pre[dp[i] - 1]); 
	cout << ans; 
}

