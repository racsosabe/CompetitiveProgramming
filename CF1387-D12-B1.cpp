#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int ans[N];
long long res;
vector<int> G[N];

void DFS(int u, int p = -1){
	for(int v : G[u]){
		if(v == p) continue;
		DFS(v, u);
		if(ans[v] == 0){
			res += 2;
			if(ans[u] == 0){
				ans[u] = v;
				ans[v] = u;
			}
			else{
				ans[v] = ans[u];
				ans[u] = v;
			}
		}
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
	if(ans[1] == 0){
		res += 2;
		ans[1] = ans[G[1].back()];
		ans[G[1].back()] = 1;
	}
	printf("%lld\n", res);
	for(int i = 1; i <= n; i++){
		printf("%d%c", ans[i], " \n"[i == n]);
	}
	return 0;
}
