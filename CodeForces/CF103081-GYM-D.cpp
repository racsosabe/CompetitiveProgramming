#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const int inf = 1e9 + 10;

int n;
int m;
int l;
int r;
int D[N];
vector< pair<int, int> > G[N];

void Dijkstra(int src){
	for(int i = 0; i < n; i++) D[i] = inf;
	D[src] = 0;
	priority_queue< pair<int, int> > Q;
	Q.emplace(make_pair(0, src));
	while(!Q.empty()){
		int u = Q.top().second;
		int dis = -Q.top().first;
		Q.pop();
		if(D[u] != dis) continue;
		for(auto [v, w] : G[u]){
			if(D[v] > w + D[u]){
				D[v] = D[u] + w;
				Q.emplace(make_pair(-D[v], v));
			}
		}
	}
}

int main(){
	scanf("%d %d %d %d", &n, &m, &l, &r);
	vector<tuple<int, int, int>> edges;
	for(int i = 0; i < m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
		edges.emplace_back(make_tuple(w, u, v));
	}
	Dijkstra(0);
	int ans = 0;
	for(auto e : edges){
		int w, u, v;
		tie(w, u, v) = e;
		if(2 * D[u] < r or 2 * D[v] < r) ans += 1;
	}
	printf("%d\n", ans);
	return 0;
}
