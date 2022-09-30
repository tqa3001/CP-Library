// A file containing important bitset operations, because I easily forget bitset member functions and it would
// be cringe if that happens in a contest. 
#include <bits/stdc++.h>
using namespace std;

bitset<1005> bs; 

signed main() {
	// access -> []
	bs[1] = 1; 
	int n; cin >> n; 
	// reset, flip, set, count, first first, find next, print
	for(int i = 1; i <= n; i++) {
		int type; cin >> type;  
		if(!type) bs.reset(); 
		if(type == 1) {
			int pos; cin >> pos; 
			bs.flip(pos); 
		}
		if(type == 2) {
			int pos; cin >> pos;
			bs.set(pos); 
		}
		if(type == 3) {
			cout << bs.count() << '\n'; 
		}
		if(type == 4) { // type == 4, 5: return size of bitset if bitset is empty. also works only for gnu compiler. 
			cout << bs._Find_first() << '\n'; 
		}
		if(type == 5) {
			int pos; cin >> pos; // if pos is on -> won't return pos, but will return first set bit after pos. 
			cout << bs._Find_next(pos) << '\n'; 
		}
		if(type == 6) {
			int sz; cin >> sz; 
			for(int i = 0; i < sz; i++) 
				cout << bs[i]; 
			cout << '\n';  
		}
	}
}
