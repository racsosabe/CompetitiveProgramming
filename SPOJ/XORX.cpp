#include<bits/stdc++.h>
using namespace::std;

const int SUML = 32 * 200000 + 5;
const int L = 31;

int n;
int k;
int nodes;
int frec[SUML];
int trie[SUML][2];

void addNode(){
	frec[nodes] = 0;
	trie[nodes][0] = trie[nodes][1] = 0;
	nodes += 1;
}

void insert(int x){
	int pos = 0;
	for(int i = L - 1; i >= 0; i--){
		int nxt = (x >> i) & 1;
		if(trie[pos][nxt] == 0){
			trie[pos][nxt] = nodes;
			addNode();
		}
		pos = trie[pos][nxt];
		frec[pos] += 1;
	}
}

int maximizer(int x){
	int pos = 0;
	int ans = 0;
	for(int i = L - 1; i >= 0; i--){
		int dx = (x >> i) & 1;
		int nxt = dx ^ 1;
		if(trie[pos][nxt] == 0) nxt ^= 1;
		ans |= (nxt ^ dx) << i;
		pos = trie[pos][nxt];
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &k);
		nodes = 0;
		addNode();
		insert(0);
		int prefix = 0;
		int best = 0;
		for(int i = 1; i <= n; i++){
			int x;
			scanf("%d", &x);
			prefix ^= x;
			int cand = maximizer(prefix ^ k);
			if(cand > best){
				best = cand;
			}
			insert(prefix);
		}
		printf("%d\n", best ^ k);
	}
	return 0;
}
