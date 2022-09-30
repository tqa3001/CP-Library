#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int mod = 1e9 + 7; 

struct Matrix {
	ll M[105][105]; 
	Matrix() {
		memset(M, 0, sizeof M); 
	}
	Matrix operator * (const Matrix &oth) {
		Matrix ret; 
		for(int i = 0; i < 100; i++) {
			for(int k = 0; k < 100; k++) {
				for(int j = 0; j < 100; j++) {
					ret.M[i][j] = (ret.M[i][j] + M[i][k] * oth.M[k][j] % mod) % mod; 
				}
			}
		}
		return ret; 
	}
} unit, base;

Matrix bp(Matrix a, ll n) {
	Matrix ret = unit; 
	while(n) {
		if(n & 1) ret = ret * a;  
		a = a * a;  
		n >>= 1; 
	}
	return ret; 
}

ll fibonacci(ll n) {
	Matrix tmp; 
	tmp.M[0][0] = 0, tmp.M[0][1] = 1;
	tmp = tmp * bp(base, n - 1); 
	return tmp.M[0][1]; 
}

signed main() {
	for(int i = 0; i < 100; i++) {
		unit.M[i][i] = 1; 
	}
	base.M[0][0] = 0; 
	base.M[0][1] = 1; 
	base.M[1][0] = 1; 
	base.M[1][1] = 1; 
	while(1) {
		ll n; 
		cin >> n; 
		cout << fibonacci(n) << '\n'; 
	}
}
