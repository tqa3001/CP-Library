#include <bits/stdc++.h>
#define int long long
#define pb push_back
using namespace std;

const int maxN = 1e5 + 5; 
const int mod[] = {1341846173, 1944331757}; 
const int base = 31; 
int m, n; 

string A[maxN], B[maxN]; 

struct Node {
	int nxt[26]; 
	int leaf; 
	Node() {
		for(int i = 0; i < 26; i ++) nxt[i] = -1; 
		leaf = -1; 
	}
};
vector<Node> T; 

void Add(const string &s, int index) {
	int cur = 0; 
	for(auto c : s) {
		if(T[cur].nxt[c - 'a'] == -1) {
			T[cur].nxt[c - 'a'] = T.size(); 
			T.pb(Node()); 
		}
		cur = T[cur].nxt[c - 'a']; 
	}
	T[cur].leaf = index; 
}

int pw[2][maxN * 10]; 
vector<int> hashA[2][maxN], hashB[2][maxN]; 
vector<int> goodA[maxN], goodB[maxN]; 
map<int, int> mapA, mapB; 

int Combine(int x, int y) {
	return x * INT_MAX + y; 
}

int getHashA(int i, int l, int r) {
	int ret[2]; 
	for(int type = 0; type < 2; type++) {
		int R = hashA[type][i][r]; 
		int L = (!l ? 0 : hashA[type][i][l - 1] * pw[type][r - l + 1] % mod[type]);
		ret[type] = (R - L) % mod[type]; 
		if(ret[type] < 0) ret[type] += mod[type]; 
	}
	return Combine(ret[0], ret[1]); 
}

int getHashB(int i, int l, int r) {
	int ret[2]; 
	for(int type = 0; type < 2; type++) {
		int R = hashB[type][i][r]; 
		int L = (!l ? 0 : hashB[type][i][l - 1] * pw[type][r - l + 1] % mod[type]);
		ret[type] = (R - L) % mod[type]; 
		if(ret[type] < 0) ret[type] += mod[type]; 
	}
	return Combine(ret[0], ret[1]); 
}

bool peculiarA[maxN], peculiarB[maxN]; 

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> m >> n;  
	int totalLen = 0; 
	for(int i = 1; i <= m; i++) cin >> A[i], totalLen += A[i].size(); 
	for(int i = 1; i <= n; i++) cin >> B[i], totalLen += B[i].size(); 
	pw[0][0] = pw[1][0] = 1; 
	for(int type = 0; type < 2; type++) {
		for(int i = 1; i <= totalLen; i++) {
			pw[type][i] = pw[type][i - 1] * base % mod[type];
		}
	} 
	T.pb(Node()); 
	for(int i = 1; i <= m; i++) {
		Add(A[i], i); 
	}
	for(int i = 1; i <= m; i++) {
		hashA[0][i].resize((int)A[i].size()); 
		hashA[1][i].resize((int)A[i].size()); 
		goodA[i].resize((int)A[i].size(), -1); 
		for(int type = 0; type < 2; type++) {
			for(int j = 0; j < (int)A[i].size(); j++) {
				hashA[type][i][j] = (!j ? A[i][j] - 'a' + 1 : hashA[type][i][j - 1] * base % mod[type] + (A[i][j] - 'a' + 1)) % mod[type]; 
			}	
		}
		int cur = 0; 
		for(int j = 0; j < (int)A[i].size(); j++) {
			char c = A[i][j]; 
			cur = T[cur].nxt[c - 'a']; 
			if(T[cur].leaf != -1 and j < (int)A[i].size() - 1) {
				goodA[i][j] = T[cur].leaf; 
				mapA[getHashA(i, j + 1, (int)A[i].size() - 1)]++;  
			}
		}
	}
	T.clear(); 
	T.pb(Node());
	for(int i = 1; i <= n; i++) {
		string tmp = B[i]; reverse(tmp.begin(), tmp.end());  
		Add(tmp, i); 
	}
	for(int i = 1; i <= n; i++) {
		hashB[0][i].resize((int)B[i].size()); 
		hashB[1][i].resize((int)B[i].size()); 
		goodB[i].resize((int)B[i].size(), -1); 
		for(int type = 0; type < 2; type++) {
			for(int j = 0; j < (int)B[i].size(); j++) {
				hashB[type][i][j] = (!j ? B[i][j] - 'a' + 1 : hashB[type][i][j - 1] * base % mod[type] + (B[i][j] - 'a' + 1)) % mod[type]; 	
			}
		}
		int cur = 0; 
		for(int j = (int)B[i].size() - 1; j >= 0; j--) {
			char c = B[i][j]; 
			cur = T[cur].nxt[c - 'a']; 
			if(T[cur].leaf != -1 and j > 0) {
				goodB[i][j] = T[cur].leaf; 
				mapB[getHashB(i, 0, j - 1)]++; 
			}
		}
	}
	for(int i = 1; i <= m; i++) peculiarA[i] = true; 
	for(int i = 1; i <= m; i++) {
		for(int j = 0; j < (int)A[i].size(); j++) {
			if(goodA[i][j] != -1) {
				int index = goodA[i][j]; 
				int hashVal = getHashA(i, j + 1, (int)A[i].size() - 1); 
				if(mapB.find(hashVal) != mapB.end()) {
					peculiarA[i] = false; 
					peculiarA[index] = false; 
				}
			}
		}
	}
	for(int i = 1; i <= n; i++) peculiarB[i] = true; 
	for(int i = 1; i <= n; i++) {
		for(int j = (int)B[i].size() - 1; j >= 0; j--) {
			if(goodB[i][j] != -1) {
				int index = goodB[i][j]; 
				int hashVal = getHashB(i, 0, j - 1); 
				if(mapA.find(hashVal) != mapA.end()) {
					peculiarB[i] = false; 
					peculiarB[index] = false;  
				}
			}
		}
	}
	int cntA = 0, cntB = 0; 
	for(int i = 1; i <= m; i++) cntA += peculiarA[i]; 
	for(int i = 1; i <= n; i++) cntB += peculiarB[i]; 
	cout << cntA << ' ' << cntB << '\n'; 
}
