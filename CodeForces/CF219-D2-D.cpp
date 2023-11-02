#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int sz[N];
int in[N];
int out[N];
vector<pair<int, int>> G[N];

void add_edge(int u, int v) {
	G[u].emplace_back(v, 0);
	G[v].emplace_back(u, 1);
}

void DFS1(int u, int p = -1) {
	sz[u] = 1;
	for(auto e : G[u]) {
		int v, w;
		tie(v, w) = e;
		if(v == p) continue;
		DFS1(v, u);
		sz[u] += sz[v];
		in[u] += in[v] + w;
	}
}

void DFS2(int u, int p = -1) {
	int sum_to_u = 0;
	for(auto e : G[u]) {
		int v, w;
		tie(v, w) = e;
		if(v == p) continue;
		sum_to_u += in[v] + w;
	}
	for(auto e : G[u]) {
		int v, w;
		tie(v, w) = e;
		if(v == p) continue;
		out[v] = out[u] + sum_to_u - in[v] - w + 1 - w;
		DFS2(v, u);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i < n; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(u, v);
	}
	DFS1(1);
	DFS2(1);
	int res = INT_MAX;
	for(int i = 1; i <= n; i++) if(res > in[i] + out[i]) res = in[i] + out[i];
	printf("%d\n", res);
	vector<int> v;
	for(int i = 1; i <= n; i++) {
		if(res == in[i] + out[i]) v.emplace_back(i);
	}
	for(int i = 0; i < v.size(); i++) printf("%d%c", v[i], " \n"[i + 1 == v.size()]);
	return 0;
}
