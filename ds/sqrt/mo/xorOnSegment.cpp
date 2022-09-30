#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxN = 5e4 + 5, blocksize = 450;
const int maxVal = (1 << 20) + 5;  
const int INF = 1e9; 
int n, m;
int a[maxN], xorSum[maxVal], ans[maxN]; 

struct Query {
	int l, r, id; 
	bool operator < (const Query &oth) { return r < oth.r; }
}; 
vector<Query> Q[5005];

struct Trie {
	struct Node {
		int nxt[2], mx, mn; 
		Node() { mx = -INF, mn = INF, nxt[0] = nxt[1] = -1; }
	}; 
	vector<Node> T;  
	Trie() { T.pb(Node()); }
	void Add(int val) {
		int cur = 0; 
		for(int i = 19; i >= 0; i--) {
			bool nxtbit = xorSum[val] & (1 << i); 
			if(T[cur].nxt[nxtbit] == -1) {
				T[cur].nxt[nxtbit] = T.size();  
				T.pb(Node());  
			}
			cur = T[cur].nxt[nxtbit]; 
			T[cur].mx = max(T[cur].mx, val); 
			T[cur].mn = min(T[cur].mn, val); 
		}
	}
	int bestXor(int val, bool Less) {
		int ret = 0, cur = 0; 
		for(int i = 19; i >= 0; i--) {
			bool nxtbit = xorSum[val] & (1 << i); 
			int nxt = T[cur].nxt[nxtbit ^ 1]; 
			if(nxt != -1 && (Less ? T[nxt].mn < val : T[nxt].mx > val)) {
				cur = nxt; 
				ret ^= (1 << i); 
			}
			else { // bug 
				nxt = T[cur].nxt[nxtbit]; 
				if(nxt != -1 && (Less ? T[nxt].mn < val : T[nxt].mx > val)) cur = nxt; 
				else return -INF; 
			} 
		}
		return ret; 
	}
};

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	for(int i = 1; i < (1 << 20); i++) xorSum[i] = xorSum[i - 1] ^ i; 
	cin >> n >> m; 
	for(int i = 1; i <= n; i++) cin >> a[i];
	for(int i = 1; i <= m; i++) {
		int l, r; cin >> l >> r; 
		Q[l / blocksize].pb({l, r, i}); 
	}
	int blockcnt = (n + blocksize - 1) / blocksize; 
 	for(int i = 0; i < blockcnt; i++) {
 		sort(Q[i].begin(), Q[i].end()); 
 		Trie Mn, Mx;
 		int L, R; L = R = (i + 1) * blocksize - 1; 
 		int mxConst = -INF;
		for(auto T : Q[i]) {
 			int l = T.l, r = T.r, id = T.id; 
 			while(R < r) {
				R++; 
				Mn.Add(a[R] - 1); Mx.Add(a[R]); 
				mxConst = max(mxConst, Mn.bestXor(a[R], true)); 
				mxConst = max(mxConst, Mx.bestXor(a[R] - 1, false)); 
			}
			Trie tmpMn, tmpMx; 
			ans[id] = mxConst; 
			for(int j = l; j <= min(L, r); j++) {
				tmpMn.Add(a[j] - 1); tmpMx.Add(a[j]);  
				ans[id] = max(ans[id], tmpMn.bestXor(a[j], true)); 
				ans[id] = max(ans[id], tmpMx.bestXor(a[j] - 1, false));  
				ans[id] = max(ans[id], Mn.bestXor(a[j], true)); 
				ans[id] = max(ans[id], Mx.bestXor(a[j] - 1, false)); 
			}	
		}
	}
	for(int i = 1; i <= m; i++) cout << ans[i] << '\n'; 
}
