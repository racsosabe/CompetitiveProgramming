#include<bits/stdc++.h>
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define trav(i, x) for (auto i : x)
#define re(x, y, z) for (int x=y; x<z; ++x)
#define eb emplace_back
#define set_to(x, v) fill(all(x), v)
using namespace std;
using ll = long long;
using vi = vector<int>;
const int inf = 1e9;

/*
	Author: Racso Galvan

	Idea:

	- Min-cut problem.

	- Just notice that if all the same rows / cols leaves are considered connected,

	  we can just connect all of them to an extra node, so we can build a bipartite graph

	  using n nodes for the rows and m nodes for the cols.

	- Now, if we set bidirectional edges for each leaf (except S and T) in (i, j) between the row i and col j with

	  capacity 1 and we connect S (consider its position to be Sx, Sy)

	  with row Sx and col Sy with an infinite capacity outgoing edge and T (consider
	  
	  its position to be Tx, Ty) with row Tx and col Ty with an infinite capacity
	  
	  ingoing edge, the min cut of that network will give us the answer.

	- Complexity: O((n + m)^4) but is better in practice.
*/

const int N = 100 + 5;

struct Dinic {
	struct Edge {
		int to, cap, flow, link;
		Edge() {}
		Edge(int to, int cap, int link, int flow=0):
			to(to), cap(cap), link(link), flow(flow) {}
	};
	vector<vector<Edge>> g;
	vi d, pt;

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
			trav(e, g[v]) {
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

	ll solve(int s, int t) {
		ll res = 0;
		while (bfs(s, t)) {
			set_to(pt, 0);
			while (int flow = dfs(s, t)) {
				res += flow;
			}
		}
		return res;
	}
};


int n;
int m;
char s[N][N];
int in[N][N];
int out[N][N];

int solve(){
	int src = n + m;
	int snk = n + m + 1;
	Dinic D(n + m + 2);
	for(int i = 0; i < n; i++){
		int u = i;
		for(int j = 0; j < m; j++){
			int v = j + n;
			if(s[i][j] == '.') continue;
			D.addEdge(u, v, 1);
			D.addEdge(v, u, 1);
			if(s[i][j] == 'S'){
				D.addEdge(src, u, inf);
				D.addEdge(src, v, inf);
			}
			if(s[i][j] == 'T'){
				D.addEdge(u, snk, inf);
				D.addEdge(v, snk, inf);
			}
		}
	}
	ll ans = D.solve(src, snk);
	return ans >= n * m ? -1 : ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++){
		scanf("%s", s[i]);
	}
	printf("%d\n", solve());
	return 0;
}
