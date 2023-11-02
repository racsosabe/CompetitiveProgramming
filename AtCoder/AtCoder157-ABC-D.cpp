#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- We can just compute the connected components and initialize each answer for 

	  the nodes as res[u] = component_size(u) - 1 - |Adj(u)|. We can directly remove

	  the neighbors since there are no multiedges and the friendship edges are different

	  from the blockship edges.

	  After that we just reduce 1 for each blockship edge (u, v) such that both u and v

	  belong to the same component.

	- Complexity: O(n + m)

*/

const int N = 100000 + 5;

int n;
int m;
int k;
int len;
int sz[N];
int res[N];
bool vis[N];
int comp[N];
vector<int> G[N];

void DFS(int u) {
	vis[u] = true;
	comp[u] = len;
	sz[len] += 1;
	for(int v : G[u]) {
		if(vis[v]) continue;
		DFS(v);
	}
}

int main() {
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	for(int i = 1; i <= n; i++) {
		if(vis[i]) continue;
		DFS(i);
		len += 1;
	}
	for(int i = 1; i <= n; i++) res[i] = sz[comp[i]] - 1 - (int)G[i].size();
	for(int i = 0; i < k; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		if(comp[u] == comp[v]) {
			res[u] -= 1;
			res[v] -= 1;
		}
	}
	for(int i = 1; i <= n; i++) printf("%d%c", res[i], " \n"[i == n]);
	return 0;
}
