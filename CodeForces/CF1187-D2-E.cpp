#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int subtree[N];
long long in[N];
long long out[N];
vector<int> G[N];

void DFS1(int u, int p = -1){
	subtree[u] = 1;
	for(int v : G[u]){
		if(v == p) continue;
		DFS1(v, u);
		subtree[u] += subtree[v];
		in[u] += in[v] + subtree[v];
	}
}

void DFS2(int u, int p = -1){
	long long sum_in = 0;
	for(int v : G[u]){
		if(v == p) continue;
		sum_in += in[v] + subtree[v];
	}
	for(int v : G[u]){
		if(v == p) continue;
		out[v] = n - subtree[v] + sum_in + out[u] - in[v] - subtree[v];
		DFS2(v, u);
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
	DFS1(1);
	DFS2(1);
	long long ans = 0;
	for(int i = 1; i <= n; i++){
		ans = max(ans, in[i] + out[i]);
	}
	printf("%lld\n", ans + n);
	return 0;
}
