#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 

const int maxN = 1e5 + 5, maxSum = 2e5 + 5; 
int test; 
int n; 

int head[maxN], sz[maxN]; 
int total; 
int a[maxSum]; 
int last[maxSum], pos[maxSum]; 
vector<int> idx[maxSum]; 

bool marked[maxSum]; 

inline char gc() {
	static char buffer[1 << 16]; 
	static size_t ptr, sz; 
	if(ptr >= sz) {
		ptr = 0; 
		sz = fread(buffer, 1, sizeof buffer, stdin); 
	}
	return buffer[ptr++]; 
}

int readInt() {
	int a, c; 
	while((a = gc()) < 40); 
	if(a == '-') return -readInt(); 
	while((c = gc()) >= 48) a = (a - 48) * 10 + c; 
	return a - 48; 
}

void solve() {
	n = readInt(); 
	total = 0;
	vector<int> s, smallSet; 
	for(int i = 1; i <= n; i++) {
		head[i] = total + 1; 
		sz[i] = readInt(); 
		for(int j = 1; j <= sz[i]; j++) {
			a[++total] = readInt(); 
			s.pb(a[total]); 
		}
		sort(a + head[i], a + head[i] + sz[i]); 
	}
	sort(all(s)); 
	s.resize(unique(all(s)) - s.begin()); 
	for(int i = 1; i <= total; i++) {
		a[i] = lower_bound(all(s), a[i]) - s.begin() + 1; 
	}	
	int blocksize = sqrt(total);
	for(int b = 1; b <= n; b++) {
		if(sz[b] > blocksize) {
			bool hasAns = false; 
			for(int i = head[b]; i < head[b] + sz[b]; i++) {
				marked[a[i]] = true; 
			}
			for(int c = 1; c <= n; c++) {
				if(c == b) continue; 
				int cnt = 0; 
				for(int i = head[c]; i < head[c] + sz[c]; i++) 
					if(marked[a[i]]) 
						cnt++;
				if(cnt >= 2 && !hasAns) {
					cout << b << ' ' << c << '\n'; 
					hasAns = true; 
				}
			}
			for(int i = head[b]; i < head[b] + sz[b]; i++) {
				marked[a[i]] = false; 
			}
			if(hasAns) return; 
		}
		else {
			smallSet.pb(b); 
		}
	}
	for(int i = 1; i <= (int)s.size(); i++) {
		idx[i].clear(); 
		last[i] = 0; 
	}
	for(auto id : smallSet) 
		for(int i = head[id]; i < head[id] + sz[id]; i++) 
			idx[a[i]].pb(id); 
	for(int val = 1; val <= (int)s.size(); val++) {
		for(auto &id : idx[val]) {
			for(int i = head[id]; i < head[id] + sz[id] && a[i] < val; i++) {
				if(last[a[i]] == val) {
					cout << id << ' ' << pos[a[i]] << '\n'; 
					return; 
				}
				last[a[i]] = val;
				pos[a[i]] = id; 
			}
		}
	}
	cout << -1 << '\n'; 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0); 
	test = readInt();
	while(test--) solve(); 
}