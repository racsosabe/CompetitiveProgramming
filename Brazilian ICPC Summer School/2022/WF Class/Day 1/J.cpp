#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define eb emplace_back
#define set_to(x, v) fill(all(x), v)
using namespace::std;

const int inf = 1e9;

struct Dinic {
	struct Edge {
		int to, cap, flow, link;
		Edge() {}
		Edge(int to, int cap, int link, int flow=0):
			to(to), cap(cap), link(link), flow(flow) {}
	};
	vector<vector<Edge>> g;
	vector<int> d, pt;

	Dinic(int n): g(n), d(n), pt(n) {}

	void addEdge(int a, int b, int cap) {
		if (a == b) return;
	  	int pa = sz(g[a]), pb = sz(g[b]);
		g[a].eb(b, cap, pb); g[b].eb(a, 0, pa);
	}

	bool bfs(int src, int snk) {
		queue<int> q({src});
		set_to(d, inf);
		d[src] = 0;
		while (!q.empty()) {
			int v = q.front(); q.pop();
			if (v == snk) return true;
			for(auto e : g[v]) {
				if (e.flow >= e.cap) continue;
				if (d[e.to] > d[v] + 1) {
					d[e.to] = d[v] + 1;
					q.emplace(e.to);
				}
			}
		}
		return false;
	}

	int dfs(int x, int snk, int flow=inf) {
		if (x == snk || !flow) return flow;
		for (; pt[x] < sz(g[x]); ++pt[x]) {
			auto& e = g[x][pt[x]];
			if (d[e.to] == d[x] + 1) {
				int res = min(e.cap - e.flow, flow);
				if (int push = dfs(e.to, snk, res)) {
					e.flow += push;
					g[e.to][e.link].flow -= push;
					return push;
				}
			}
		}
		return 0;
	}

	long long solve(int s, int t) {
		long long res = 0;
		while (bfs(s, t)) {
			set_to(pt, 0);
			while (int flow = dfs(s, t)) {
				res += flow;
			}
		}
		return res;
	}
};

const int N = 500 + 5;

int n;
int m;
char s[N][N];
int id[N][N];

bool solve(){
	int white = 0, black = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(s[i][j] == 'W') white++;
			else if(s[i][j] == 'B') black++;
		}
	}
	if(black * 2 != white) return false;
	int w = 0, b = 0;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(s[i][j] == '.') continue;
			if(s[i][j] == 'W') id[i][j] = w++;
			else id[i][j] = b++;
		}
	}
	Dinic D(w + 2 * b + 3);
	int src = w + 2 * b;
	int pvt = w + 2 * b + 1;
	int snk = w + 2 * b + 2;
	D.addEdge(pvt, snk, inf);
	for(int i = 0; i < b; i++){
		int at1 = w + 2 * i;
		int at2 = w + 2 * i + 1;
		D.addEdge(at1, pvt, 1);
		D.addEdge(at2, pvt, 1);
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			if(s[i][j] != 'B') continue;
			int v = id[i][j];
			if(i and s[i - 1][j] == 'W'){
				int u = id[i - 1][j];
				D.addEdge(u, w + 2 * v, 1);
			}
			if(i + 1 < n and s[i + 1][j] == 'W'){
				int u = id[i + 1][j];
				D.addEdge(u, w + 2 * v, 1);
			}
			if(j and s[i][j - 1] == 'W'){
				int u = id[i][j - 1];
				D.addEdge(u, w + 2 * v + 1, 1);
			}
			if(j + 1 < m and s[i][j + 1] == 'W'){
				int u = id[i][j + 1];
				D.addEdge(u, w + 2 * v + 1, 1);
			}
		}
	}
	for(int i = 0; i < w; i++) D.addEdge(src, i, 1);
	return D.solve(src, snk) == white;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++){
			scanf("%s", s[i]);
		}
		puts(solve() ? "YES" : "NO");
	}
	return 0;
}
