/*
	Aho-corrasick algorithm. 
	Status: tested with https://codeforces.com/problemset/problem/963/D. 
*/
#include <bits/stdc++.h>
#define pb push_back
using namespace std;

struct Node {
	int nxt[26], go[26], link, leaflink; 
	int p; 
	char c; 
	vector<int> strId; 
	Node(int p = -1, char c = '$') : p(p), c(c) {
		for(int i = 0; i < 26; i++) 
			nxt[i] = go[i] = -1; 
		link = leaflink = -1; 
	}
}; 
vector<Node> Trie;  

void add(const string &s, int id) {
	int cur = 0; 
	for(auto &c : s) {
		if(Trie[cur].nxt[c - 'a'] == -1) {
			Trie[cur].nxt[c - 'a'] = Trie.size(); 
			Trie.pb(Node(cur, c)); 
		}
		cur = Trie[cur].nxt[c - 'a']; 
	}
	Trie[cur].strId.pb(id); 
}

int go(int u, char c); 

int getlink(int u) {
	if(Trie[u].link == -1) {
		if(!u || !Trie[u].p) Trie[u].link = 0; 
		else {
			Trie[u].link = go(getlink(Trie[u].p), Trie[u].c); 
		}
	}
	return Trie[u].link; 
}

int go(int u, char c) {
	if(Trie[u].go[c - 'a'] == -1) {
		if(Trie[u].nxt[c - 'a'] != -1) Trie[u].go[c - 'a'] = Trie[u].nxt[c - 'a']; 
		else {
			Trie[u].go[c - 'a'] = !u ? 0 : go(getlink(u), c); 
		}
 	}
	return Trie[u].go[c - 'a']; 
}

int getleaflink(int u) {
	if(Trie[u].leaflink == -1) {
		if(!u) Trie[u].leaflink = 0;  
		else {
			int nxt = getlink(u); 
			if(!Trie[nxt].strId.empty()) Trie[u].leaflink = nxt; 
			else {
				Trie[u].leaflink = getleaflink(nxt); 
			}
		}
	}
	return Trie[u].leaflink; 
}

signed main() {
	Trie.pb(0); 
}

/*
	Bug logs:
	1. Node(int p, char c) : p(p), c(c) -> Node(char c, int p) : c(c), p(p) -> error. 
*/