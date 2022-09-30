/*
	- Sliding window of size K 
	Status: AC-ed https://www.spoj.com/problems/ARRAYSUB/
*/
#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e6 + 5; 

int n, k; 
int a[maxN]; 

signed main() {
	cin >> n; 
	for(int i = 1; i <= n; i++) 
		cin >> a[i]; 
	cin >> k; 
	deque<int> dq; 
	for(int i = 1; i <= n; i++) {
		while(!dq.empty() && dq.front() <= i - k) dq.pop_front(); 
		while(!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back(); 
		dq.push_back(i); 
		if(i >= k)
			cout << a[dq.front()] << ' '; 
	}
}