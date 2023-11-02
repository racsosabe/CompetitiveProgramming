#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int m;
int q;
int len;
int par[N];
bool vis[N];
int comp[N];
int sizes[N];
stack<int> S;
set<int> T[N];
vector<int> G[2][N];

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

void join(int a, int b){
	a = get(a);
	b = get(b);
	if(a == b) return;
	if(sizes[a] > sizes[b]) swap(a, b);
	par[a] = b;
	sizes[b] += sizes[a];
}

void DFS(int u, int id){
	vis[u] = true;
	for(int v : G[id][u]){
		if(vis[v]) continue;
		DFS(v, id);
	}
	if(id == 0) S.emplace(u);
	else comp[u] = len;
}

void getSCC(){
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		DFS(i, 0);
	}
	for(int i = 1; i <= n; i++) vis[i] = false;
	while(!S.empty()){
		int u = S.top();
		S.pop();
		if(vis[u]) continue;
		len += 1;
		DFS(u, 1);
	}
	for(int i = 1; i <= n; i++){
		int u = comp[i];
		for(int x : G[0][i]){
			int v = comp[x];
			T[u].emplace(v);
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &q);
	for(int i = 1; i <= n; i++){
		par[i] = i;
		sizes[i] = 1;
	}
	for(int i = 1; i <= m; i++)
		int u, v;
		scanf("%d %d", &u, &v);
		join(u, v);
		G[0][u].emplace_back(v);
		G[1][v].emplace_back(u);
	}
	getSCC();
	while(q--){
		int a, b;
		scanf("%d %d", &a, &b);
		puts(get(a) == get(b) and (h[comp[a]] < h[comp[b]] or comp[a] == comp[b]) ? "Yes" : "No");
	}
	return 0;
}
