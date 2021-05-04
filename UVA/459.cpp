#include<bits/stdc++.h>
using namespace::std;

const int N = 30;

int n;
bool vis[N];
vector<int> G[N];

void DFS(int u){
	vis[u] = true;
	for(int v : G[u]){
		if(vis[v]) continue;
		DFS(v);
	}
}

void clear(){
	for(int i = 0; i < n; i++) G[i].clear();
}

int main(){
	int t;
	scanf("%d", &t);
	getchar();
	getchar();
	while(t--){
		char c = getchar();
		n = c - 'A' + 1;
		c = getchar();
		c = getchar();
		while(isalpha(c)){
			char d = getchar();
			int u = c - 'A';
			int v = d - 'A';
			G[u].emplace_back(v);
			G[v].emplace_back(u);
			getchar();
			c = getchar();
		}
		int cnt = 0;
		for(int i = 0; i < n; i++) vis[i] = false;
		for(int i = 0; i < n; i++){
			if(vis[i]) continue;
			DFS(i);
			cnt += 1;
		}
		printf("%d\n", cnt);
		clear();
		if(t) puts("");
	}
	return 0;
}
