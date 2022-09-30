#include <bits/stdc++.h>
using namespace std;

vector<int> zFunction(const string &s) {
	int n = s.size(); 
	vector<int> z(n); 
	z[0] = -1; 
	int l = -1, r = -1; 
	for(int i = 1; i < n; i++) {
		if(i <= r) {
			z[i] = min(z[i - l], r - i + 1); 
		}
		while(i + z[i] <= n && s[i + z[i]] == s[z[i]]) z[i]++; 
		if(i + z[i] - 1 > r) {
			r = i + z[i] - 1; 
			l = i; 
		}
	}
	return z; 
}

signed main() {
	string s; 
	cin >> s; 
	vector<int> z = zFunction(s); 
	for(auto v : z) cout << v << ' '; 
}
