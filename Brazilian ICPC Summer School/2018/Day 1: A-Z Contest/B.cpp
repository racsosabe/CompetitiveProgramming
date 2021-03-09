#include<bits/stdc++.h>
using namespace::std;

struct BipartiteMatcher {
	vector<vector<int>> g;
	vector<int> L, R;
	vector<bool> vis;

	BipartiteMatcher(int n, int m):
		g(n), L(n, -1), R(m, -1), vis(n) {}

	void addEdge(int a, int b) {
		g[a].emplace_back(b);
	}

	bool match(int x) {
		if (vis[x]) return 0;
		vis[x] = 1;
		for (int v : g[x])
			if (R[v] == -1)
				return R[L[x]=v]=x, 1;
		for (int v : g[x])
			if (match(R[v]))
				return R[L[x]=v]=x, 1;
		return 0;
	}

	int solve() {
		int cnt = 1;
		while (cnt--) {
			fill(vis.begin(), vis.end(), 0);
			for (int i = 0; i < L.size(); ++i) {
				cnt |= L[i] == -1 and match(i);
			}
		}
		int res = 0;
		for (int i = 0; i < L.size(); ++i) {
			res += L[i] != -1;
		}
		return res;
	}
};

int n;
int m;

int main(){
	scanf("%d %d", &n, &m);
	BipartiteMatcher BM(n, m);
	for(int i = 0; i < n; i++){
		int v;
		while(scanf("%d", &v) == 1 and v){
			v -= 1;
			BM.addEdge(i, v);
		}
	}
	printf("%d\n", BM.solve());
	for(int i = 0; i < n; i++){
		if(BM.L[i] == -1) continue;
		printf("%d %d\n", i + 1, BM.L[i] + 1);
	}
	return 0;
}
