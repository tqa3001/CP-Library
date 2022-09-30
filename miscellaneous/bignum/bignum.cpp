#include <bits/stdc++.h>
#define pb push_back 
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll; 
typedef vector<int> bigint; 

inline void fix(bigint &a) {
	while((int)a.size() > 1 && !a.back()) a.pop_back(); 
}

bigint get(const string &x) {
	bigint ret; 
	for(auto c : x) ret.pb(c - '0');
	reverse(all(ret)); 
	return ret; 
}

bigint add(const bigint &a, const bigint &b) {
	int len = max((int)a.size(), (int)b.size()); 
	bigint ret; 
	int carry = 0; 
	for(int i = 0; i < len; i++) {
		int val = (i < (int)a.size() ? a[i] : 0) + (i < (int)b.size() ? b[i] : 0) + carry; 
		if(val >= 10) {
			val -= 10; 
			carry = 1; 
		}
		else carry = 0; 
		ret.pb(val); 
	}
	if(carry) ret.pb(1); 
	fix(ret); 
	return ret; 
}

bigint sub(const bigint &a, const bigint &b) {
	bigint ret; 
	int carry = 0; 
	for(int i = 0; i < (int)a.size(); i++) {
		int val = a[i] - (i < (int)b.size() ? b[i] : 0) - carry; 
		if(val < 0) {
			carry = 1; 
			val += 10; 
		}
		else carry = 0; 
		ret.pb(val); 
	}
	fix(ret); 
	return ret; 
}

bigint mul(const bigint &a, const bigint &b) {
	bigint ret((int)a.size() + (int)b.size()); 
	for(int i = 0; i < (int)a.size(); i++) {
		int carry = 0; 
		for(int j = 0; j <= (int)b.size(); j++) {
			ret[i + j] += a[i] * (j < (int)b.size() ? b[j] : 0) + carry; 
			carry = ret[i + j] / 10; 
			ret[i + j] %= 10; 
		}
	}
	fix(ret); 
	return ret; 
}

pair<bigint, int> div(const bigint &a, int d) {
	bigint ret; 
	int rem = 0; 
	for(int i = (int)a.size() - 1; i >= 0; i--) {
		rem = rem * 10 + a[i]; 
		ret.pb(rem / d); 
		rem %= d; 
	}
	reverse(all(ret)); 
	fix(ret); 
	return {ret, rem}; 
}

void print(const bigint &a) {
	for(int i = (int)a.size() - 1; i >= 0; i--) {
		cout << a[i]; 
	}
	cout << '\n'; 
}

signed main() {
	while(true) {
		char type; 
		cin >> type;
		if(type != '/') {
			string _a, _b; 
			cin >> _a >> _b; 
			bigint a = get(_a), b = get(_b); 
			if(type == '+') {
				print(add(a, b)); 
			}
			if(type == '-') {
				print(sub(a, b)); 
			}
			if(type == '*') {
				print(mul(a, b)); 
			}	
		}
		else {
			string _a; 
			int d; 
			cin >> _a >> d; 
			bigint a = get(_a); 
			bigint ret; 
			int rem; 
			tie(ret, rem) = div(a, d); 
			print(ret); 
			cout << "rem: " << rem << '\n'; 
		}
	}
}  
