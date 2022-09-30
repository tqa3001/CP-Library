/*
	Knuth optimization O(n^3) -> O(n^2) 
	https://vn.spoj.com/problems/OPTCUT/
*/
#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 

const int maxN = 2005; 
const ll INF = numeric_limits<ll>::max(); 

int n; 
ll a[maxN], dp[maxN][maxN], pre[maxN]; 
int opt[maxN][maxN];

ll cost(int i, int j) { return pre[j] - pre[i - 1]; } 
 
signed main() {
	cin >> n; 
	for(int i = 1; i <= n; i++) cin >> a[i], pre[i] = pre[i - 1] + a[i];
	for(int i = 1; i <= n; i++) 
		for(int j = 1; j <= n; j++) 
			dp[i][j] = INF; 
	for(int len = 1; len <= n; len++) {
		for(int i = 1; i <= n - len + 1; i++) {
			int j = i + len - 1; 
			if(len == 1) {
				dp[i][j] = 0; 
				opt[i][j] = i; 
				continue; 
			}
			for(int k = opt[i][j - 1]; k <= opt[i + 1][j]; k++) {
				if(dp[i][k] != INF && dp[k + 1][j] != INF && dp[i][j] > dp[i][k] + dp[k + 1][j] + cost(i, j)) {
					dp[i][j] = dp[i][k] + dp[k + 1][j] + cost(i, j); 
					opt[i][j] = k; 
				}
			}
		}
	}
	cout << dp[1][n];   
}

