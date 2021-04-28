#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int inf = 1e9 + 10;

int n;
int m;
int D[2][N];
vector<int> G[N];
vector<int> W[N];

void Dijkstra(int id){
	int src = id == 0 ? 1 : n;
	for(int i = 1; i <= n; i++) D[id][i] = inf;
	D[id][src] = 0;
	priority_queue< pair<int, int> > Q;
	Q.emplace(make_pair(0, src));
	while(!Q.empty()){
		int u = Q.top().second;
		int d = -Q.top().first;
		Q.pop();
		if(d != D[id][u]) continue;
		for(int i = 0; i < G[u].size(); i++){
			int v = G[u][i];
			int w = W[u][i];
			if(D[id][v] > D[id][u] + w){
				D[id][v] = D[id][u] + w;
				Q.emplace(make_pair(-D[id][v], v));
			}
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		W[u].emplace_back(w);
		W[v].emplace_back(w);
	}
	for(int i = 0; i < 2; i++) Dijkstra(i);
	for(int i = 1; i <= n; i++){
		printf("%d\n", D[0][i] + D[1][i]);
	}
	return 0;
}
