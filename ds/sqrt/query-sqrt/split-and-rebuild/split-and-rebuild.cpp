/*
	http://acm.math.spbu.ru/~sk1/mm/lections/mipt2016-sqrt/mipt-2016-burunduk1-sqrt.en.pdf
	1. ins(i, x) – insert 𝑥 on 𝑖-th position.
	2. del(i) – erase 𝑖-th element of the array.
	3. sumGreater(l,r,x) – calculate sum of elements greater than 𝑥 on the range [𝑙, 𝑟].
	4. rev(l,r) – reverse the range [𝑙, 𝑟].
	- to optimize to sqrt(nlog) per query, implement split() & rebuild both in O(n), and set blocksize -> sqrt(nlog)
	- status: stress-tested for 5e4 tests with n, q <= 3000. 
*/
#include <bits/stdc++.h>
#define pb push_back
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 

const int maxN = 1e5 + 5;  

int blocksize; 
int n, q; 
int a[maxN], tmp[maxN]; 

struct Block {
	int l, r;
	bool isrev; 
	vector<int> value; 
	vector<ll> sum; 
	Block() {} 
	Block(int l, int r, bool isrev) : l(l), r(r), isrev(isrev) {
		value.resize(r - l + 1), sum.resize(r - l + 1); 
		for(int i = l; i <= r; i++) {
			value[i - l] = a[i];  
		}
		sort(all(value)); 
		for(int i = 0; i < r - l + 1; i++) {
			sum[i] = (!i ? 0LL : sum[i - 1]) + value[i]; 
		}
	} 
	ll getSum(const int &x) {
		int id = lower_bound(all(value), x) - value.begin(); 
		return sum[r - l] - (!id ? 0 : sum[id - 1]); 
	} 
}; 
vector<Block> S; 

void resetS() {
//	cout << "reset\n"; 
	int id = 0; 
	for(auto &block : S) {
		if(!block.isrev) {
			for(int i = block.l; i <= block.r; i++) {
				tmp[++id] = a[i]; 
			}
		}
		else {
			for(int i = block.r; i >= block.l; i--) {
				tmp[++id] = a[i]; 
			}
		}
	}
	n = id; 
	for(int i = 1; i <= n; i++) a[i] = tmp[i]; 
	S.clear(); 	
	for(int b = 1; b <= n; b += blocksize) {
		S.pb(Block(b, min(n, b + blocksize - 1), false)); 
	}
}

int split(int pos) { 
	int i = 0, sum = 0; 
	while(i < (int)S.size() && sum + (S[i].r - S[i].l + 1) < pos) sum += S[i].r - S[i].l + 1, i++;   
	pos -= sum + 1; 
	if(!pos) 
		return i;  
	if(!S[i].isrev) {
		S.insert(S.begin() + i + 1, Block(S[i].l + pos, S[i].r, false)); 
		S[i] = Block(S[i].l, S[i].l + pos - 1, false); 
	}
	else {
		S.insert(S.begin() + i + 1, Block(S[i].l, S[i].r - pos, true));
		S[i] = Block(S[i].r - pos + 1, S[i].r, true); 
	}
	return i + 1; 
}

void ins(int pos, int val) {
	pos = split(pos); 
	a[++n] = val; 
	S.insert(S.begin() + pos, Block(n, n, false));  
}

void del(int pos) {
	int id = split(pos); 
	split(pos + 1); 
	S.erase(S.begin() + id); 
}

ll sumGreater(int l, int r, int x) {
	assert(l <= r);  
	l = split(l), r = split(r + 1) - 1; 
//	cout << "done split " << l << ' ' << r << '\n';  
	ll ret = 0; 
	for(int i = l; i <= r; i++) { 
		ret += S[i].getSum(x); 
	}
	return ret; 
}

void rev(int l, int r) {
	assert(l <= r);
	l = split(l), r = split(r + 1) - 1; 
	for(int i = l; i <= r; i++) {
		S[i].isrev ^= 1; 
	}
	reverse(S.begin() + l, S.begin() + r + 1); 
}

signed main() {
	freopen("input.txt", "r", stdin); 
	freopen("output.txt", "w", stdout); 
	cin >> n >> q; 
	for(int i = 1; i <= n; i++) cin >> a[i]; 
	blocksize = sqrt(n);
	for(int b = 1; b <= n; b += blocksize) {
		S.pb(Block(b, min(n, b + blocksize - 1), false)); 
	}
	for(int t = 1; t <= q; t++) {
		if((int)S.size() > 3 * blocksize) 
			resetS(); 
		int type; cin >> type; 
		if(type == 1) {
			int pos, val; cin >> pos >> val; 
			ins(pos, val); 
		}
		if(type == 2) {
			int pos; cin >> pos; 
			del(pos); 
		}
		if(type == 3) {
			int l, r, x; cin >> l >> r >> x; 
			cout << sumGreater(l, r, x) << '\n'; 
		}
		if(type == 4) {
			int l, r; cin >> l >> r; 
			rev(l, r); 
		}
//		cout << "S: \n"; 
//		for(auto &block : S) {
//			cout << block.l << ' ' << block.r << ' ' << block.isrev << '\t'; 
//			for(auto  x:  block.value) cout << x << ' '; cout << '\n'; 
//		}
	}
	cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << '\n'; 
}