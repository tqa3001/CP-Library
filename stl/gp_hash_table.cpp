#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll; 

struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};

__gnu_pbds::gp_hash_table<ll, int> M({},{},{},{},{1<<16}); 
// unordered_map: ~5500ms
// map ~2100ms:
// gp_hash_table: MLE, but 550ms ?? (108 ms for 1e6 insertions)

signed main() {
	for(int i = 1; i <= 10000000; i++) { 
		ll x = (ll) 1e16 + i; 
		auto it = M.find(x); 
		if(it == M.end()) 
			M[x] = i; 
	}
	cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << '\n'; 
}