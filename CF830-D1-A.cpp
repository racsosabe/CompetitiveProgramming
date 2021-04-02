#include<bits/stdc++.h>
using namespace::std;

const int N = 2000 + 5;

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
int k;
int p;
int a[N];
int b[N];

long long dis(int i, int j){
	int x = a[i];
	int y = b[j];
	if(1ll * x * y <= 0) return 1ll * abs(x - y) + abs(y);
	if(abs(x) >= abs(y)) return abs(x);
	return 1ll * abs(x - y) + abs(y);
}

bool can(int x){
	BipartiteMatcher BM(n, k);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < k; j++){
			if(dis(i, j) <= x) BM.addEdge(i, j);
		}
	}
	return BM.solve() == n;
}

int solve(){
	for(int i = 0; i < n; i++) a[i] -= p;
	for(int i = 0; i < k; i++) b[i] -= p;
	int lo = 0, hi = 2e9;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(not can(mi)) lo = mi + 1;
		else hi = mi;		
	}
	return lo;
}

int main(){
	scanf("%d %d %d", &n, &k, &p);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < k; i++) scanf("%d", b + i);
	printf("%d\n", solve());
	return 0;
}
