#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;
const int M = 300000 + 5;
const long long inf = 1e18;

int n;
int m;
long long L;
long long I[M];
long long F[M];
long long T[M];
long long D[N];
vector< tuple<int, int> > G[N];

long long Dijkstra(int src){
	for(int i = 0; i < n; i++) D[i] = -inf;
	D[src] = L;
	priority_queue< tuple<long long, int> > Q;
	Q.emplace(make_tuple(L, src));
	while(!Q.empty()){
		int u = get<1>(Q.top());
		long long dis = get<0>(Q.top());
		Q.pop();
		if(dis != D[u]) continue;
		for(auto [v, e] : G[u]){
			long long nxt_dis = D[u] - T[e];
			if(nxt_dis < I[e]) continue;
			nxt_dis = ((nxt_dis - I[e]) / F[e]) * F[e] + I[e];
			if(D[v] < nxt_dis){
				D[v] = nxt_dis;
				Q.emplace(make_tuple(D[v], v));
			}
		}
	}
	return D[0] == -inf ? -1 : D[0];
}

int main(){
	scanf("%d %d %lld", &n, &m, &L);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d %d %lld %lld %lld", &u, &v, T + i, I + i, F + i);
		G[v].emplace_back(make_tuple(u, i));
	}
	printf("%lld\n", Dijkstra(n - 1));
	return 0;
}
