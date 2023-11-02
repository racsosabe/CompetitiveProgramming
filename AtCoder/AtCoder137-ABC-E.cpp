#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea: 

	- Just apply a modified Bellman Ford over the edges with new weights (w - P).

	- Try to search a positive cycle reachable from node 1 and you're done.

	- Complexity: O(nm)

*/

const int N = 2500 + 5;
const int inf = 1e9 + 10;

int n;
int m;
int p;
int memo[N];
vector<tuple<int, int, int>> edges;

int BellmanFord(){
	for(int i = 1; i <= n; i++) memo[i] = -inf;
	memo[1] = 0;
	for(int i = 1; i < n; i++){
		for(auto e : edges){
			int u, v, w;
			tie(u, v, w) = e;
			if(memo[u] == -inf) continue;
			if(memo[v] < memo[u] + w){
				memo[v] = memo[u] + w;
			}
		}
	}
	bool relaxed_n = false;
	for(int i = 1; i < n; i++){
		for(auto e : edges){
			int u, v, w;
			tie(u, v, w) = e;
			if(memo[u] == -inf) continue;
			if(memo[u] == inf or memo[v] < memo[u] + w){
				memo[v] = inf;
			}
		}
	}
	return memo[n] == inf ? -1 : max(0, memo[n]);
}

int main(){
	scanf("%d %d %d", &n, &m, &p);
	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		w -= p;
		edges.emplace_back(make_tuple(u, v, w));
	}
	printf("%d\n", BellmanFord());
	return 0;
}
