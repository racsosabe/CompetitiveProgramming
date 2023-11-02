#include<bits/stdc++.h>
using namespace::std;

const int N = 1000000 + 5;

int n;
int k;
int d[N];
int h[N];
int par[N];
int deg[N];
int vis[N];
int npar[N];
int clen[N];
int comp[N];
int where[N];
long long nxt[N];
long long sum[N];
long long act[N];
vector<int> G[N];
vector<int> Gt[N];

void init(){
	for(int i = 1; i < n; i++){
		for(int j = i; j < n; j += i) d[j] += 1;
	}
	for(int i = 0; i < n; i++){
		int to = i + d[i] < n ? i + d[i] : i + d[i] - n;
		G[i].emplace_back(to);
		Gt[to].emplace_back(i);
		deg[to] += 1;
	}
}

vector<int> getCycles(){
	queue<int> Q;
	for(int i = 0; i < n; i++){
		if(deg[i] == 0){
			Q.emplace(i);
			vis[i] = 1;
		}
	}
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			deg[v] -= 1;
			if(deg[v] == 0){
				Q.emplace(v);
				vis[v] = 1;
			}
		}
	}
	vector<int> res;
	int pos = 0;
	for(int i = 0; i < n; i++){
		if(vis[i]) continue;
		int at = i;
		do{
			res.emplace_back(at);
			comp[at] = pos;
			clen[pos]++;
			vis[at] = 2;
			at = G[at][0];
		}while(vis[at] == 0);
		pos += 1;
	}
	return res;
}

void DFS(int u){
	for(int v : Gt[u]){
		if(vis[v] == 2) continue;
		h[v] = h[u] + 1;
		comp[v] = comp[u];
		DFS(v);
	}
}

void solve(){
	vector<int> cycle = getCycles();
	for(int i = 0; i < n; i++){
		par[i] = G[i][0];
		act[i] = i;
		where[i] = i;
	}
	for(int val = k; val > 0; val >>= 1){
		if(val & 1){
			for(int i = 0; i < n; i++){
				sum[i] += act[where[i]];
				where[i] = par[where[i]];
			}
		}
		for(int i = 0; i < n; i++){
			nxt[i] = act[i] + act[par[i]];
			npar[i] = par[par[i]];
		}
		for(int i = 0; i < n; i++){
			act[i] = nxt[i];
			par[i] = npar[i];
		}
	}
	for(auto x : cycle){
		DFS(x);
	}
	int ans = -1;
	long long best = LLONG_MAX;
	for(int i = 0; i < n; i++){
		if(h[i] + clen[comp[i]] >= k){
			if(ans == -1 or best > sum[i]){
				ans = i;
				best = sum[i];
			}
		}
	}
	if(ans == -1){
		puts("-1");
		return;
	}
	for(int i = 0; i < k; i++){
		printf("%d%c", ans, " \n"[i + 1 == k]);
		ans = G[ans][0];
	}
}

int main(){
	scanf("%d %d", &n, &k);
	init();
	solve();
	return 0;
}
