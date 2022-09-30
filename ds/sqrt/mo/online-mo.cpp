/*
	MO O(n^5/3) solution for cf 940F
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef pair<int, int> ii; 

const int maxN = 1e5 + 5, blocksize = 2000; 

int n, q; 
int a[maxN]; 

struct askQuery {
	int l, r, qtime;  
	bool operator< (const askQuery &oth) {
		if(l / blocksize != oth.l / blocksize) 
			return l / blocksize < oth.l / blocksize; 
		if(r / blocksize != oth.r / blocksize) 
			return r / blocksize < oth.r / blocksize; 
		return qtime < oth.qtime; 
	}
}; 
vector<askQuery> Q; 

ii update[maxN];
bool isUpd[maxN];  
int ans[maxN];
int tmp[maxN], freq[3 * maxN], cnt[3 * maxN]; 

void add(const int &pos) {
	int val = a[pos]; 
	cnt[freq[val]]--; 
	freq[val]++; 
	cnt[freq[val]]++; 
} 

bool done; 

void rem(const int &pos) {
	int val = a[pos]; 
	cnt[freq[val]]--;
	assert(freq[val] > 0); 
	freq[val]--; 
	cnt[freq[val]]++; 
}

void solve(int lo, int hi) {
	cnt[0] = 1e9; // 0 always in set of freq. 
	for(int i = 0; i < n; i++) 
		assert(!freq[i]); 
	for(int i = 1; i <= n; i++) 
		a[i] = tmp[i]; 
	int L = 0, R = -1, curQuery = 0; 
	function<void(int, int)> assign = [&](const int &pos, const int &val) -> void {
		bool inSeg = L <= pos && pos <= R; 
		if(inSeg) rem(pos); 
		a[pos] = val; 
		if(inSeg) add(pos); 
	};  
	for(int i = lo; i <= hi; i++) {
		int l = Q[i].l, r = Q[i].r, id = Q[i].qtime;  
		while(curQuery < id) {
			curQuery++; 
			if(isUpd[curQuery]) 
				assign(update[curQuery].fi, update[curQuery].se); 
		}
		while(R < r) 
			R++, add(R); 
		while(L > l)
			L--, add(L); 
		while(R > r) 
			rem(R), R--;
		while(L < l) 
			rem(L), L++;  
		int mex = 0; 
		while(cnt[mex]) mex++; 
		ans[id] = mex; 
	}
	for(int i = L; i <= R; i++) 
		rem(i); 
}

signed main() {
	ios_base::sync_with_stdio(0); 
	cin.tie(0); cout.tie(0); 
	cin >> n >> q; 
	vector<int> val; 
	for(int i = 1; i <= n; i++) {
		cin >> a[i]; 
		val.pb(a[i]); 
	}
	for(int i = 1; i <= q; i++) {
		int type; cin >> type; 
		if(type == 1) {
			int l, r; cin >> l >> r; 
			Q.pb({l, r, i}); 
		}
		else {
			int pos, x; cin >> pos >> x; 
			update[i] = {pos, x}; 
			isUpd[i] = true; 
			val.pb(x); 
		}
	}
	sort(all(val)); 
	val.resize(unique(all(val)) - val.begin()); 
	for(int i = 1; i <= n; i++) {
		a[i] = lower_bound(all(val), a[i]) - val.begin(); 
	}
	for(int i = 1; i <= q; i++) 
		if(isUpd[i]) 
			update[i].se = lower_bound(all(val), update[i].se) - val.begin(); 		
	sort(all(Q)); 
	function<ii(int)> block = [](const int &id) -> ii {
		return make_pair(Q[id].l / blocksize, Q[id].r / blocksize); 
	}; 
	for(int i = 1; i <= n; i++) 
		tmp[i] = a[i];
	
	for(int i = 0; i < (int)Q.size(); ) {
		int j = i; 
		while(j < (int)Q.size() && block(i) == block(j)) j++; 
		solve(i, j - 1); 
		i = j;  
	}
	for(int i = 1; i <= q; i++) 
		if(!isUpd[i]) 
			cout << ans[i] << '\n'; 
}