#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int a[N];
int b[N];
int subtree[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	subtree[u] = 1;
	for(int v : G[u]){
		if(v == p) continue;
		DFS(v, u);
		subtree[u] += subtree[v];
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		scanf("%d %d", a + i, b + i);
		G[a[i]].emplace_back(b[i]);
		G[b[i]].emplace_back(a[i]);
	}
	DFS(1);
	long long ans = 0;
	for(int i = 1; i < n; i++){
		int x = min(subtree[a[i]], subtree[b[i]]);
		ans += 1ll * x * (n - x);
	}
	printf("%lld\n", ans);
	return 0;
}
