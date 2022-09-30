#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int smallN = 3005, mod = 1e9 + 7; 

ll C[smallN][smallN]; 

void calBinomial(int N, int K) {
	C[0][0] = 1; 
	for(int i = 1; i <= N; i++) {
		C[i][0] = C[i][i] = 1; 
		for(int j = 1; j < i; j++) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1]; 
			if(C[i][j] > mod) C[i][j] -= mod; 
		}
	}
}

signed main() {
	calBinomial(3000, 3000); 
	cout << C[5][3] << ' ' << C[6][4] << ' ' << C[10][5] << '\n'; 
}