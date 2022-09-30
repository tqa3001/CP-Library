#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

void cntSort(vector<int> &a, vector<int> &v) {
	int n = a.size(); 
	int mxrnk = max(300, n);
	vector<int> pos(mxrnk, 0), tmp(n); 
	for(int i = 0; i < n; i++) pos[v[i]]++; 
	for(int i = 0, sum = 0; i < mxrnk; i++) {
		int cnt = pos[i]; 
		pos[i] = sum; 
		sum += cnt; 
	}
	for(int i = 0; i < n; i++) {
		int bucket = v[a[i]]; 
		tmp[pos[bucket]++] = a[i]; 
	}
	a.swap(tmp); 
}

vector<int> suffixArray(const string &s) {
	int n = s.size(); 
	vector<int> sa(n), rnk(n), tmp(n); 
	for(int i = 0; i < n; i++) rnk[i] = s[i]; 
	iota(all(sa), 0); 
	cntSort(sa, rnk); 
	for(int k = 1; k < n; k <<= 1) {
		for(int i = 0; i < n; i++) sa[i] = (sa[i] - k + n) % n; 
		cntSort(sa, rnk); 
		auto cmp = [&] (const int &x, const int &y) {
			if(rnk[x] != rnk[y]) return rnk[x] < rnk[y]; 
			int rx = rnk[(x + k) % n], ry = rnk[(y + k) % n]; 
			return rx < ry; 
		};
		tmp[sa[0]] = 0; 
		for(int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]); 
		rnk.swap(tmp); 
	}
	return sa; 
}

vector<int> kasai(const string &s, const vector<int> &sa) {
	int n = s.size(); 
	vector<int> lcp(n), pos(n); 
	for(int i = 0; i < n; i++) pos[sa[i]] = i;  
	for(int i = 0, cur = 0; i < n; i++) {
		if(!pos[i]) continue; 
		if(cur) cur--; 
		int j = sa[pos[i] - 1];
		cout << i << ' ' << j << ' ' << cur << '\n'; 
		while(j + cur < n && i + cur < n && s[j + cur] == s[i + cur]) cur++; 
		lcp[pos[i] - 1] = cur; 
	}
	return lcp; 
}

signed main() {
	string s; 
	cin >> s; 
	s = s + '$'; 
	vector<int> sa = suffixArray(s); 
	vector<int> lcp = kasai(s, sa); 		
	cout << "sa: "; for(auto x : sa) cout << x << ' '; cout << '\n'; 
	cout << "lcp: "; for(auto x : lcp) cout << x << ' '; cout << '\n'; 
}
