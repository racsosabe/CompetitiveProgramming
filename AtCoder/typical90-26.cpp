#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int h[N];
int cnt[3];
vector<int> G[N];

void DFS(int u, int p = -1){
	cnt[h[u]] += 1;
	for(int v : G[u]){
		if(v == p) continue;
		h[v] = h[u] ^ 1;
		DFS(v, u);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(1);
	int want = n >> 1;
	int depth = cnt[0] >= want ? 0 : 1;
	for(int i = 1; i <= n; i++){
		if(h[i] ^ depth) continue;
		if(want > 0){
			printf("%d", i);
			want--;
			putchar(want ? ' ' : '\n');
		}
	}
	return 0;
}
