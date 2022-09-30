#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;

const int maxN = 2e5 + 5, INF = 1e9; 

int n; 
int a[maxN], pos[maxN];  

int distinct; 
vector<int> Val; 

void compress() {
	for(int i = 1; i <= n; i++) Val.pb(a[i]); 
	sort(all(Val)); 
	Val.resize(unique(all(Val)) - Val.begin()); 
	distinct = Val.size(); 
	for(int i = 1; i <= n; i++) {
		pos[i] = lower_bound(all(Val), a[i]) - Val.begin() + 1; 
	}
}

signed main() {
	cin >> n; 
	for(int i = 1; i <= n; i++) cin >> a[i]; 
	compress(); 
}
