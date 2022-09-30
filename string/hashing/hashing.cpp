/*
	notes:
	base, mod -> primes
	base > # different values, 137 > # English letters 
	problems of the type "given set of string, count # occurences of S -> birthday paradox -> double hash"
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int maxN = 1e6 + 5;
const int mod[] = {(int)1e9 + 7, (int)1e9 + 9}, base = 31; 

int n; 
string s; 
ll pw[2][maxN]; 
ll h[2][maxN]; 

void initHash() {
	pw[0][0] = pw[1][0] = 1; 
	for(int m = 0; m < 2; m++) {
		for(int i = 1; i <= n; i++) {
			pw[m][i] = pw[m][i - 1] * base % mod[m]; 	
		}
	}
	for(int m = 0; m < 2; m++) {
		for(int i = 1; i <= n; i++) {
			h[m][i] = (h[m][i - 1] * base + (s[i] - 'a' + 1)) % mod[m]; 
		}
	}
}

inline ll combine(const int &x, const int &y) {
	return x * INT_MAX + y; 
}

ll getHash(int l, int r) {
	ll ret[2]; 
	for(int m = 0; m < 2; m++) {
		ret[m] = (h[m][r] - h[m][l - 1] * pw[m][r - l + 1] % mod[m]) % mod[m]; 
		if(ret[m] < 0) ret[m] += mod[m]; 
	}
	return combine(ret[0], ret[1]); 
}

int cmp(int lx, int rx, int ly, int ry) {
	int l = 1, r = min(rx - lx + 1, ry - ly + 1); 
	while(l < r) {
		int mid = (l + r + 1) >> 1; 
		if(getHash(lx, lx + mid - 1) == getHash(ly, ly + mid - 1)) {
			l = mid; 	
		} 
		else r = mid - 1; 
	}
	if(l == min(rx - lx + 1, ry - ly + 1)) {
		if(rx - lx + 1 == ry - ly + 1) return 2; 
		return rx - lx + 1 > ry - ly + 1; 
	}	
	else {
		return s[lx + l] > s[ly + l]; 
	}
}

void stringHash() { 
	cin >> s; 
	n = s.size(); 
	s = ' ' + s; 
	initHash();
	int q; 
	cin >> q; 
	for(int i = 1; i <= n; i++) {
		int x, y, l, r; 
		cin >> x >> y >> l >> r; 
		cout << cmp(x, y, l, r) << '\n'; 
	}	
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count()); 

map<int, ll> Hash;
ll hashVal[maxN]; 

void xorHash() {
	// Works well for sets, but not for multisets. 
	Hash.clear(); 
	int setCnt; cin >> setCnt;
	for(int i = 1; i <= setCnt; i++) {
		int sz; cin >> sz; 
		for(int j = 1; j <= sz; j++) {
			int x; 
			cin >> x; 
			if(Hash.find(x) == Hash.end()) Hash[x] = rng() % (1LL << 60); // to avoid overflow. 
			hashVal[i] ^= Hash[x]; 
		}
	}
	for(int i = 1; i <= setCnt; i++) cout << i << '\t' << hashVal[i] << '\n'; 
}

void polyHash() { // https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
	Hash.clear(); 
	int setCnt; cin >> setCnt; 
	for(int i = 1; i <= setCnt; i++) {
		int h = 1, sz; cin >> sz;  
		for(int j = 1; j <= sz; j++) {
			int x; cin >> x; 
			if(Hash.find(x) == Hash.end()) Hash[x] = rng() % mod[0]; 
			h = h * (Hash[x] + 1) % mod[0]; 
		}
		cout << i << '\t' << h << '\n'; 
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); 
	int type; 
	cin >> type; 
	if(!type) stringHash(); 
	else if(type == 1) xorHash(); 
	else polyHash(); 
}
