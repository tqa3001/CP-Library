#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;

const int maxN = 1e6 + 5; 

void cntSort(vector<int> &a, vector<int> &v) {
	int n = a.size(); 
	int mxrnk = max(n, 300); 
	vector<int> pos(mxrnk, 0), tmp(n); 
	for(int i = 0; i < n; i++) {
		pos[v[a[i]]]++; 
	}
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
		for(int i = 0; i < n; i++) {
			sa[i] = (sa[i] - k + n) % n; 
		}
		cntSort(sa, rnk); 
		rnk[sa[0]] = 0; 
		auto cmp = [&] (const int &x, const int &y) {
			if(rnk[x] != rnk[y]) return rnk[x] < rnk[y]; 
			int px = (x + k) % n, py = (y + k) % n; 
			return rnk[px] < rnk[py]; 
		};
		for(int i = 1; i < n; i++) {
			tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]); 
		}
		tmp.swap(rnk); 
	}
	return sa; 
}

signed main() {
	string s; //cin >> s; 
	for(int i = 1; i <= 500000; i++) s.push_back('a'); 
	s = s + '$'; 
	vector<int> sa = suffixArray(s); 	
//	for(auto x : sa) cout << x << ' '; 
}
