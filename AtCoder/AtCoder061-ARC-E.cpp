#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- BFS & Graph modelling problem

	- Try to consider a Bipartite graph in which the set of vertices L represents

	  the stations and the set R represents the same-company connected components.

	- Notice that the number of nodes and edges is O(n + m). 

	- Thus, we can create an edge from each station u to each connected component

	  that contains it. This means that if we go from L to R and then from R to L

	  we will be traversing only 1 edge in the original graph, so if we get the

	  shortest distance from L(1) to L(n) divided by 2, then that will be our answer.

	- Complexity: O(n + m).
*/

const int N = 1000000 + 5;

int n;
int m;
int len;
int D[N];
int Q[N];
bool vis[N];
vector<int> G[N];
vector<int> G2[N];
vector< pair<int, int> > E[N];

void BFS(int src){
	for(int i = 1; i <= n + len; i++) D[i] = -2;
	D[src] = 0;
	int sz = 0;
	int at = 0;
	Q[sz++] = src;
	while(at < sz){
		int u = Q[at++];
		for(int v : G[u]){
			if(D[v] != -2) continue;
			D[v] = D[u] + 1;
			Q[sz++] = v;
		}
	}
}

void addEdge(int u, int v){
	G[u].emplace_back(v);
	G[v].emplace_back(u);
}

void build(int color){
	for(auto e : E[color]){
		G2[e.first].emplace_back(e.second);
		G2[e.second].emplace_back(e.first);
	}
	for(auto e : E[color]){
		if(not vis[e.first]){
			stack<int> S;
			len += 1;
			S.emplace(e.first);
			while(!S.empty()){
				int u = S.top();
				S.pop();
				addEdge(u, len + n);
				for(int v : G2[u]){
					if(vis[v]) continue;
					S.emplace(v);
					vis[v] = true;
				}				
			}
		}
		if(not vis[e.second]){
			stack<int> S;
			len += 1;
			S.emplace(e.second);
			while(!S.empty()){
				int u = S.top();
				S.pop();
				addEdge(u, len + n);
				for(int v : G2[u]){
					if(vis[v]) continue;
					S.emplace(v);
					vis[v] = true;
				}				
			}
		}
	}
	for(auto e : E[color]){
		G2[e.first].clear();
		G2[e.second].clear();
		vis[e.first] = vis[e.second] = false;
	}
}

int main(){
	scanf("%d %d", &n, &m);
	vector< pair<int, pair<int, int> > > edges;
	for(int i = 1; i <= m; i++){
		int u, v, c;
		scanf("%d %d %d", &u, &v, &c);
		edges.emplace_back(make_pair(c, make_pair(u, v)));
		E[c].emplace_back(make_pair(u, v));
	}
	for(int i = 1; i <= 1000000; i++){
		if(E[i].empty()) continue;
		build(i);
	}
	BFS(1);
	printf("%d\n", D[n] / 2);
	return 0;
}
