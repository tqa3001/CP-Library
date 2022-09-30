/*
	Notes: 
	- catalan[n] = C(2n, n) / (n + 1)
 	- sterling[n] here refers to sterling numbers of the second kind 
 	- 
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 

const int smallN = 3005, mod = 1e9 + 7; 

ll catalan[smallN], sterling[smallN][smallN];  

void calCatalan(int N) {
	catalan[0] = catalan[1] = 1; 
	for(int i = 2; i <= N; i++) {
		for(int j = 0; j < N; j++) {
			catalan[i] += catalan[j] * catalan[i - j - 1] % mod; 
			if(catalan[i] > mod) 
				catalan[i] -= mod; 
		}
	}
}

void calSterling(int N, int K) { // partition N items -> K non-empty sets. 
 	sterling[0][0] = 1; 
 	for(int i = 1; i <= N; i++) {
 		for(int j = 1; j <= K; j++) {
 			sterling[i][j] = sterling[i - 1][j - 1] + j * sterling[i - 1][j] % mod;
 			if(sterling[i][j] > mod) 
 				sterling[i][j] -= mod;   
 		}
 	}
}

signed main() {
	calCatalan(3000);
	for(int i = 0; i <= 10; i++) cout << catalan[i] << ' '; cout << "\n\n";
	calSterling(3000, 3000);   
	for(int i = 0; i <= 10; i++) {
		for(int j = 0; j <= 10; j++) {
			cout << sterling[i][j] << ' '; 
		}
		cout << '\n'; 
	}
}