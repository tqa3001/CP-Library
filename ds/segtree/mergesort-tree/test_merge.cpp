#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pb push_back
using namespace std;

signed main() {
	vector<int> a, b, c;
	a.pb(1); 
	b.pb(1), b.pb(2);
//	c.resize(3); // this must be added if you don't use back_inserter. 
	merge(all(a), all(b), back_inserter(c)); 
	for(auto x : c) cout << x << ' '; cout << '\n';	
}
