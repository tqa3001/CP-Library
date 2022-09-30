/*
	https://www.hackerearth.com/practice/algorithms/searching/binary-search/practice-problems/algorithm/kriti-and-her-birthday-gift/
	|S| <= 10 -> no need to mod. 	
	Hashing won't work well in this problem because of the birthday paradox. 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int maxN = 1e5 + 5; 
const int blocksize = 320; 

int n, q; 
map<ll, int> M; 

struct Query {
	int l, r, id; 
	ll Hash; 
	inline bool operator< (const Query &oth) {
		if(l / blocksize != oth.l / blocksize) 
			return l / blocksize < oth.l / blocksize;
		return r < oth.r; 
	}
} Q[maxN]; 

ll H[maxN]; 

inline ll getHash(const string &s) {
	ll ret = 0; 
	for(int i = 0; i < (int)s.length(); i++) {
		ret = ret * 27 + (s[i] - 'a' + 1); 
	}
	return ret; 
}

int ans[maxN]; 

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0); 
	cin >> n; 
	for(int i = 1; i <= n; i++) {
		string s; 
		cin >> s;
		H[i] = getHash(s); 
	}
	cin >> q; 
	for(int i = 1; i <= q; i++) {
		cin >> Q[i].l >> Q[i].r; 
		string s; cin >> s; 
		Q[i].Hash = getHash(s); 
		Q[i].id = i; 
	}
	sort(Q + 1, Q + q + 1); 
	int L = 0, R = -1; 
	for(int i = 1; i <= q; i++) {
		int l = Q[i].l, r = Q[i].r; 
		while(L < l) 
			M[H[L]]--, L++;  
		while(L > l)
			L--, M[H[L]]++; 
		while(R < r) 
			R++, M[H[R]]++; 
		while(R > r) 
			M[H[R]]--, R--;  
		map<ll, int>::iterator it = M.find(Q[i].Hash); 
		if(it != M.end()) 
			ans[Q[i].id] = (*it).second; 
	}
	for(int i = 1; i <= q; i++)
		cout << ans[i] << '\n'; 
}