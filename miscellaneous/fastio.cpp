#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

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

ll readLL() {
	ll a, c; 
	while((a = gc()) < 40); 
	if(a == '-') return -readLL(); 
	while((c = gc()) >= 48) a = (a - 48) * 10 + c; 
	return a - 48; 
}

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0); 
	freopen("input.txt", "r", stdin); 
	freopen("output.txt", "w", stdout); 
	int n = readInt(); 
	for(int i = 1; i <= n; i++) {
		ll num = readLL(); 
		cout << num << '\n';
	}
}
