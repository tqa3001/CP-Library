#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e5 +5; 

int n; 
int a[maxN];  
set<int> st;

signed main() {
	cin >> n; 
	for(int i = 1; i <= n; i++)
		cin >> a[i]; 
	for(int i = 1; i <= n; i++) {
		st.insert(a[i]); 
		set<int>::iterator it = st.find(a[i]); it++; 
		if(it!=st.end()) 
			st.erase(it);
	}
	cout << st.size() << endl;
}
