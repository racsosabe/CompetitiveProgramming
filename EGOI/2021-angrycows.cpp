#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;
const long long inf = 1e18;

int n;
int m;
int c[N];
bool vis[N];
bool used[N];
long long D[N];
vector< pair<int, int> > G[N];

void Dijkstra(){
	priority_queue< pair<long long, int> > Q;
	for(int i = 1; i <= n; i++){
		D[i] = inf;
		if(c[i] == 1){
			D[i] = 0;
			Q.emplace(make_pair(0, i));
		}
	}
	while(!Q.empty()){
		long long dis = -Q.top().first;
		int u = Q.top().second;
		Q.pop();
		if(dis > D[u]) continue;
		for(auto e : G[u]){
			int v = e.first;
			int w = e.second;
			if(D[v] > D[u] + w){
				D[v] = D[u] + w;
				Q.emplace(make_pair(-D[v], v));
			}
		}
	}
}

bool can(long long x){
	for(int i = 1; i <= n; i++) vis[i] = used[i] = false;
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		if(c[i] == -1){
			queue<int> Q;
			Q.emplace(i);
			vis[i] = true;
			while(!Q.empty()){
				int u = Q.front();
				Q.pop();
				for(auto e : G[u]){
					int v = e.first;
					if(vis[v]) continue;
					if(c[v] == 1 or (c[v] == 0 and D[v] <= x)) continue;
					Q.emplace(v);
					vis[v] = true;
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		if(not vis[i]) continue;
		for(auto e : G[i]){
			int v = e.first;
			if(c[v] == 1) return false;
			if(vis[v]) continue;
			used[v] = true;
		}
	}
	int cnt = 0;
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		if(c[i] == 1){
			cnt += 1;
			queue<int> Q;
			Q.emplace(i);
			vis[i] = true;
			while(!Q.empty()){
				int u = Q.front();
				Q.pop();
				for(auto e : G[u]){
					int v = e.first;
					if(vis[v] or used[v]) continue;
					Q.emplace(v);
					vis[v] = true;
				}
			}
		}
	}
	return cnt == 1;
}

void print(){
	vector<int> res;
	for(int i = 1; i <= n; i++){
		if(used[i]) res.emplace_back(i);
	}
	printf("%d\n", (int)res.size());
	for(int i = 0; i < res.size(); i++){
		printf("%d%c", res[i], " \n"[i + 1 == res.size()]);
	}
}

void solve(){
	Dijkstra();
	long long lo = 0, hi = m * 1e9;
	while(lo < hi){
		long long mi = lo + (hi - lo) / 2;
		if(not can(mi)) lo = mi + 1;
		else hi = mi;
	}
	if(not can(lo)){
		puts("-1");
		return;
	}
	can(lo);
	print();
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= n; i++){
		scanf("%d", &c[i]);
	}
	for(int i = 1; i <= m; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
	}
	solve();
	return 0;
}
