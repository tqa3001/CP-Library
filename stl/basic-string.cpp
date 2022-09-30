/*
	basic_string<primitive_type / pair> can be very useful in problems where one must implement
	a lot of vector merging and concatenating. 
*/
#include <bits/stdc++.h>
using namespace std;

ostream &operator<< (ostream &os, const basic_string<int> &a) { for(auto &x : a) os << x << ' '; return os; }

signed main() {
	int n, m; cin >> n >> m; 
	basic_string<int> a, b;  
	for(int i = 1; i <= n; i++) {
		int x; cin >> x; 
		a += x; 
	}
	for(int i = 1; i <= m; i++) {
		int x; cin >> x; 
		b += x; 
	}
	cout << a << '\n' << b << '\n';  
	a += b; 
	cout << a << '\n'; 
	sort(a.begin(), a.end()); 
	if(!a.empty()) 
		a[0] += 100; 
	if((int)a.size() > 1) 
		a.pop_back(); // c++11 
	cout << a; 
}