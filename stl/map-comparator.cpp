#include <bits/stdc++.h>
using namespace std;

struct cmp {
	bool operator() (int l,int r) const {
		return l > r;
	}
};
set<int, cmp> S; 
// map<int, int, cmp> M; 

signed main() {
	int n; cin >> n; 
	for(int i = 1; i <= n; i++) {
		int val; cin >> val; 
		S.insert(val); 
	}
	for(auto x : S) 
		cout << x << ' '; 
}