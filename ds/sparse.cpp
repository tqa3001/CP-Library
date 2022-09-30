#include <bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll; 

const int maxN = 1e5 + 5; 
int n, q; 
int a[maxN], lg[maxN]; 

ll sp[maxN][22]; 

ll get(int l, int r) {
	int Log = lg[r - l + 1]; 
	return min(sp[l][Log], sp[r - (1 << Log) + 1][Log]); 
}

signed main() {
	cin >> n >> q;
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; 
		lg[i] = (i == 1 ? 0 : lg[i >> 1] + 1);
	}
	for(int len = 0; len < 20; len++) {
		for(int i = 0; i + (1LL << len) - 1 <= n; i++) {
			if(!len) {
				sp[i][len] = a[i]; 
			}
			else sp[i][len] = min(sp[i][len - 1], sp[i + (1LL << (len - 1))][len - 1]); 
		}
	}
	for(int i = 1; i <= q; i++) {
		int l, r; 
		cin >> l >> r; 
		cout << get(l, r) << '\n'; 
	}
}
