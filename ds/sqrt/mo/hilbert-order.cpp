/*
	O(n sqrt n) -> O(n sqrt q) 
	Usage: return hilbert(l, r, 21, 0) < hilbert(oth.l, oth.r, 21, 0); 
	Status: tested (replaced cmp in /normal-mo.cpp)
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

inline ll hilbert(int x, int y, int pw, int rotate) {
	if(!pw) 
		return 0; 
	int hpow = 1 << (pw - 1);
	int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	static const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	ll subSqrSize = 1LL << (2 * pw - 2);
	ll ans = seg * subSqrSize;
	ll add = hilbert(nx, ny, pw - 1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSqrSize - add - 1);
	return ans;
}

signed main() {

}