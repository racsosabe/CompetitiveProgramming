#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int q;
bool vis[N];
vector<int> G[N];

vector<int> BFS(int src){
	for(int i = 1; i <= n; i++) vis[i] = false;
	queue<int> Q;
	for(int v : G[src]){
		vis[v] = true;
		Q.emplace(v);
	}
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			if(vis[v]) continue;
			Q.emplace(v);
			vis[v] = true;
		}
	}
	vector<int> res;
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		res.emplace_back(i);
	}
	return res;
}

void clearAll(){
	for(int i = 1; i <= n; i++) G[i].clear();
}

int main(){
	while(scanf("%d", &n) == 1 and n){
		int u;
		while(scanf("%d", &u) == 1 and u){
			int v;
			while(scanf("%d", &v) == 1 and v){
				G[u].emplace_back(v);
			}
		}
		scanf("%d", &q);
		for(int i = 1; i <= q; i++){
			int x;
			scanf("%d", &x);
			vector<int> res = BFS(x);
			printf("%d", (int)res.size());
			for(int x : res){
				printf(" %d", x);
			}
			puts("");
		}
		clearAll();
	}
	return 0;
}
