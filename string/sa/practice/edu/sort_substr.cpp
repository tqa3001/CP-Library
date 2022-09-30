#include <bits/stdc++.h>
#define ii pair<int, int> 
#define fi first
#define se second 
#define pb push_back
using namespace std;

const int maxN = 4e5 + 5; 

void cntSort(vector<int> &a, const vector<int> &v) {
	int n = a.size(); 
	int mxrnk = max(n, 300); 
	vector<int> pos(mxrnk, 0), tmp(n); 
	for(int i = 0; i < n; i++) pos[v[i]]++; 
	for(int i = 0, sum = 0; i < mxrnk; i++) {
		int cnt = pos[i]; 
		pos[i] = sum; sum += cnt;
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
	for(int i = 0; i < n; i++) sa[i] = i, rnk[i] = s[i]; 
	rnk[n - 1] = 0;
	cntSort(sa, rnk); 
	for(int k = 1; k < n; k <<= 1) {
		for(int i = 0; i < n; i++) sa[i] = (sa[i] - k + n) % n; 
		cntSort(sa, rnk); 
		auto cmp = [&] (const int &x, const int &y) {
			return rnk[x] != rnk[y] ? rnk[x] < rnk[y] : rnk[(x + k) % n] < rnk[(y + k) % n]; 
		}; 
		tmp[sa[0]] = 0; 
		for(int i = 1; i < n; i++) tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]); 
		rnk.swap(tmp); 
	} 
	return sa; 
}

vector<int> kasai(const string &s, const vector<int> &sa) {
	int n = s.size(); 
	vector<int> pos(n), lcp(n); 
	for(int i = 0; i < n; i++) pos[sa[i]] = i; 
	for(int i = 0, cur = 0; i < n; i++) {
		if(!pos[i]) continue; 
		if(cur) cur--; 
		int j = sa[pos[i] - 1]; 
		while(max(i, j) + cur < n and s[i + cur] == s[j + cur]) cur++; 
		lcp[pos[i] - 1] = cur; 
	}
	return lcp; 
}

int n, q; 
string s; 
int sp[maxN][22], Lg[maxN]; 
vector<int> pos; 

int Lcp(int i, int j) {
	int l = pos[i], r = pos[j]; 
	if(l > r) swap(l, r); 
	if(l == r) return n - i; 
	int Log = Lg[r - l]; 
	return min(sp[l][Log], sp[r - (1 << Log)][Log]);
}

signed main() {
	cin >> s; 
	s = s + '$'; // lul 
	n = s.size() - 1; 
	vector<int> sa = suffixArray(s); 
	vector<int> lcp = kasai(s, sa);
	pos.resize(n + 1); 
	for(int i = 0; i <= n; i++) pos[sa[i]] = i; 
	Lg[1] = 0; 
	for(int i = 2; i <= n; i++) Lg[i] = Lg[i >> 1] + 1; 
	for(int len = 0; (1 << len) <= n; len++) {
		for(int i = 1; i + (1 << len) - 1 <= n; i++) {
			if(!len) sp[i][len] = lcp[i]; 
			else {
				sp[i][len] = min(sp[i][len - 1], sp[i + (1 << (len - 1))][len - 1]); 
			}
		}
	}
	vector<ii> a; 
	cin >> q; 
	for(int i = 1; i <= q; i++) {
		int l, r; cin >> l >> r; 
		l--; r--; 
		a.pb({l, r}); 
	}
	auto cmp = [&] (const ii &x, const ii &y) {
		int len = Lcp(x.fi, y.fi); 
		int lenX = x.se - x.fi + 1, lenY = y.se - y.fi + 1;  
		if(len >= min(lenX, lenY)) {
			return lenX != lenY ? lenX < lenY : x < y; 
		}
		return s[x.fi + len] < s[y.fi + len]; 
	}; 
	sort(a.begin(), a.end(), cmp); 
	for(auto T : a) {
		cout << T.fi + 1 << ' ' << T.se + 1 << '\n';  
	}
}
