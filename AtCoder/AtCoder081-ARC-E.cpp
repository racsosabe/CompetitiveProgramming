#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Just build a graph in which the nodes are the positions and there are edges

	  to the closest position with some letter c.

	- Apply BFS until reaching an outer position (pos > |s|) and that will be the

	  shortest string that isn't a subsequence of s.

	- To get the lexicographically minimal we can just iterate over the edges
	 
	  in lexicographical order.

	- Complexity: O(n * E), where E is the size of the alphabet.

*/

const int N = 200000 + 5;
const int E = 26;

int n;
int D[N];
char s[N];
int par[N];
int parc[N];
int nxt[E][N];

void preprocess(){
	for(int i = 0; i < E; i++) nxt[i][n] = nxt[i][n + 1] = n + 1;
	for(int i = n - 1; i >= 0; i--){
		for(int j = 0; j < E; j++) nxt[j][i] = nxt[j][i + 1];
		nxt[s[i + 1] - 'a'][i] = i + 1;
	}
}

void BFS(int src){
	for(int i = 0; i <= n + 1; i++) D[i] = -1;
	queue<int> Q;
	Q.emplace(src);
	D[src] = 0;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int c = 0; c < E; c++){
			int v = nxt[c][u];
			if(D[v] == -1){
				D[v] = D[u] + 1;
				par[v] = u;
				parc[v] = c;
				Q.emplace(v);
			}
		}
	}
}

void build(){
	stack<char> S;
	int at = n + 1;
	while(at > 0){
		S.emplace(parc[at] + 'a');
		at = par[at];
	}
	while(!S.empty()){
		putchar(S.top());
		S.pop();
	}
	putchar('\n');
}

int main(){
	scanf("%s", s + 1);
	n = strlen(s + 1);
	preprocess();
	BFS(0);
	build();
	return 0;
}
