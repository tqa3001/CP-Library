/*
	DNC solution for APIO2014 Sequence
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int maxN = 1e5 + 5, maxK = 205; 
const ll INF = numeric_limits<ll>::max(); 
int n, k; 
ll a[maxN]; 

ll dp[maxN], _dp[maxN]; 
int opt[maxN]; 
int trace[maxK][maxN];  

ll cost(int i, int j) {
	assert(j < i); 
	return _dp[j] + a[j] * (a[i] - a[j]); 
}

void solve(int l, int r, int lo, int hi) {
	if(l > r) return; 
	int mid = (l + r) >> 1; 
	opt[mid] = -1; 
	for(int i = lo; i <= min(hi, mid - 1); i++) {
		if(opt[mid] == -1 || cost(mid, opt[mid]) < cost(mid, i)) {
			opt[mid] = i; 
		}
	}
	if(opt[mid] == -1) dp[mid] = -INF; 
	else dp[mid] = cost(mid, opt[mid]); 
	solve(l, mid - 1, lo, opt[mid]); 
	solve(mid + 1, r, opt[mid], hi); 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	cin >> n >> k; 
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; 
		a[i] += a[i - 1]; 
	}
	for(int layer = 2; layer <= k + 1; layer++) {
		_dp[0] = -INF; 
		for(int i = 1; i <= n; i++) _dp[i] = dp[i]; 
		solve(1, n, 1, n); 
		for(int i = 1; i <= n; i++) 
			trace[layer][i] = opt[i]; 
	}
	cout << dp[n] << '\n'; 
	vector<int> ans; 
	for(int i = k + 1, cur = n; i > 1; i--) {
		ans.push_back(trace[i][cur]); 
		cur = trace[i][cur]; 
	}
	for(int i = (int)ans.size() - 1; i >= 0; i--) 
	 	if(ans[i]) cout << ans[i] << ' '; 
}