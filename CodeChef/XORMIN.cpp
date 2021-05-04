#include<bits/stdc++.h>
using namespace::std;

const int SUML = 200000 * 20 + 5;
const int L = 20;
const int N = 200000 + 5;
const int E = 26;

int n;
int T;
int in[N];
int out[N];
int root[N];
int frec[SUML];
int trie[SUML][E];

void copy(int last, int pos){
	trie[pos][0] = trie[last][0];
	trie[pos][1] = trie[last][1];
	frec[pos] = frec[last];
}

void insert(int last, int pos, int x){
	for(int i = L - 1; i >= 0; i--){
		int nxt = (x >> i) & 1;
		if()
	}
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &q);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		for(int i = 1; i < n; i++){
			int u, v;
			scanf("%d %d", &u, &v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		T = 1;
		DFS(1);
		nodes = 0;
		addNode();
		root[0] = 0;
		for(int i = 1; i <= n; i++){
			int at = v[i];
			root[i] = nodes;
			addNode();
			copy(root[i - 1], root[i]);
			insert(root[i - 1], root[i], a[at]);
		}
	}
	return 0;
}
