#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

signed main() {
	int n, k;  
	cin >> n >> k; 
	vector<int> a(n); 
	for(int i = 0; i < n; i++) cin >> a[i]; 
	rotate(a.begin(), a.begin() + k, a.end()); 
	for(int i = 0; i < n; i++) 
		cout << a[i] << ' '; 
}