#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5 + 5; 

string s, t; 
int n, pf[maxN];

signed main() {
	cin >> s; n = s.length(); 
	for(int i = 1, k = 0; i < n; i++) {
		while(k and s[k] != s[i]) k = pf[k - 1]; 
		if(s[k] == s[i]) k++; 
		pf[i] = k; 
	}
	cin >> t;
	vector<int> ans;  
	for(int i = 0, k = 0; i < (int)t.size(); i++) {
		while(k and (k == n or s[k] != t[i])) k = pf[k - 1]; 
		if(s[k] == t[i]) k++; 
		if(k == n) ans.push_back(i); 
	}
	for(auto pos : ans) cout << pos << ' '; 
}
