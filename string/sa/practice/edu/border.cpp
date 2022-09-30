#include <bits/stdc++.h>
#define int long long
#define ii pair<int, int> 
#define fi first
#define se second
using namespace std;

const int maxN = 4e5 + 5; 

void cntSort(vector<int> &a, const vector<int> &v) {
	int n = a.size();
	int mxrnk = max(n, 300LL);  
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
	cntSort(sa, rnk); 
	for(int k = 1; k < n; k <<= 1) {
		for(int i = 0; i < n; i++) sa[i] = (sa[i] - k + n) % n; 
		cntSort(sa, rnk); 
		auto cmp = [&] (const int &x, const int &y) {
			return rnk[x] != rnk[y] ? rnk[x] < rnk[y] : rnk[(x + k) % n] < rnk[(y + k) % n]; 
		}; 
		tmp[sa[0]] = 0;  // this was the SECOND TIME i wrote this ... = 1 !!!@!!@!!@!!
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
		while(max(i, j) + cur < n && s[i + cur] == s[j + cur]) cur++; 
		lcp[pos[i] - 1] = cur;  
	}
	return lcp; 
}

string s; 
int n; 
vector<int> sa, lcp;
int sp[maxN][22], Lg[maxN]; 

int getMin(int l, int r) {
	int Log = Lg[r - l + 1]; 
	return lcp[sp[l][Log]] < lcp[sp[r - (1 << Log) + 1][Log]] ? sp[l][Log] : sp[r - (1 << Log) + 1][Log]; 
}

int ans; 

void Solve() {
	queue<ii> q; 
	q.push({1, n}); 
	while(!q.empty()) {
		int l, r; tie(l, r) = q.front(); q.pop(); 
		if(l == r) continue; 
		int mn = getMin(l, r - 1); 
		ans += (mn - l + 1) * (r - mn) * lcp[mn]; 
		q.push({l, mn}); 
		q.push({mn + 1, r});  
	}
	ans += n * (n + 1) / 2; 
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); 

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); 
	cout.tie(0); 
	cin >> s; 
	s = s + '$'; 
	sa = suffixArray(s); 
	lcp = kasai(s, sa);
	n = s.size() - 1; 
	Lg[1] = 0; 
	for(int i = 2; i <= n; i++) Lg[i] = Lg[i >> 1] + 1; 
	for(int len = 0; (1 << len) <= n; len++) {
		for(int i = 1; i + (1 << len) - 1 <= n; i++) {
			if(!len) sp[i][len] = i; 
			else {
				if(lcp[sp[i][len - 1]] < lcp[sp[i + (1 << (len - 1))][len - 1]]) sp[i][len] = sp[i][len - 1]; 
				else sp[i][len] = sp[i + (1 << (len - 1))][len - 1]; 
 			}
		}
	}
	ans = 0; 
	Solve(); 
	cout << ans << '\n';	  
}
