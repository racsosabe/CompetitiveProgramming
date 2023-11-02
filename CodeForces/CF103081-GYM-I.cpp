#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int D[N];
bool vis[N];
vector<int> G[N];

int getComp(int src){
	queue<int> Q;
	Q.emplace(src);
	int cnt = 0;
	vis[src] = true;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		cnt++;
		for(int v : G[u]){
			if(vis[v]) continue;
			Q.emplace(v);
			vis[v] = true;
		}
	}
	return cnt;
}

int BFS(int src){
	for(int i = 1; i <= n; i++) D[i] = -1;
	D[src] = 0;
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			if(D[v] == -1){
				D[v] = D[u] + 1;
				Q.emplace(v);
			}
		}
	}
	return *max_element(D + 1, D + n + 1);
}

int solve(){
	if(getComp(1) != n) return -1;
	int diam = BFS(1);
	int ans = 0;
	while((1 << ans) < diam) ans += 1;
	return ans + 1;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	printf("%d\n", solve());
	return 0;
}
