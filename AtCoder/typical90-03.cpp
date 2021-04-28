#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int D[N];
int Q[N];
vector<int> G[N];

pair<int, int> getFurthest(int src){
	for(int i = 1; i <= n; i++) D[i] = -1;
	D[src] = 0;
	int at = 0, sz = 0;
	Q[sz++] = src;
	while(at < sz){
		int u = Q[at++];
		for(int v : G[u]){
			if(D[v] != -1) continue;
			D[v] = D[u] + 1;
			Q[sz++] = v;
		}
	}
	int best = 1;
	for(int i = 2; i <= n; i++){
		if(D[i] > D[best]) best = i;
	}
	return {D[best], best};
}

int solve(){
	pair<int, int> cur = getFurthest(1);
	pair<int, int> res = getFurthest(cur.second);
	return res.first + 1;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	printf("%d\n", solve());
	return 0;
}
