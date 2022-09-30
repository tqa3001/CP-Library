#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int maxN = 1e6 + 5; 
int n; 
ll fen[maxN]; 

void update(int i, ll val) { while(i <= n) fen[i] += val, i += i & (-i); }
ll query(int i) { ll ret = 0; while(i) ret += fen[i], i -= (i & (-i)); return ret; }
