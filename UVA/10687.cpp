#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int x[N];
int y[N];
bool vis[N];
vector<int> G[N];

vector<int> getOrder(){
	vector<int> res(n);
	iota(res.begin(), res.end(), 1);
	sort(res.begin(), res.end(), [&] (int i, int j){
		if(x[i] == x[j]) return y[i] < y[j];
		return x[i] < x[j];
	});
	return res;
}

int d(int i, int j){
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

void clear(){
	for(int i = 1; i <= n; i++){
		G[i].clear();
		vis[i] = false;
	}
}

void DFS(int u){
	vis[u] = true;
	for(int v : G[u]){
		if(vis[v]) continue;
		DFS(v);
	}
}

int main(){
	while(scanf("%d", &n) == 1 and n){
		for(int i = 1; i <= n; i++) scanf("%d %d", x + i, y + i);
		vector<int> p = getOrder();
		for(int i = 0; i < n; i++){
			int min1 = -1, min2 = -1;
			for(int j = 0; j < n; j++){
				if(i == j) continue;
				if(min1 == -1) min1 = j;
				else{
					if(min2 == -1 or d(p[i], p[min2]) > d(p[i], p[j])) min2 = j;
					if(d(p[i], p[min1]) > d(p[i], p[min2])) swap(min1, min2);
				}
			}
			if(min1 != -1) G[p[i]].emplace_back(p[min1]);
			if(min2 != -1) G[p[i]].emplace_back(p[min2]);
		}
		DFS(1);
		bool can = true;
		for(int i = 1; i <= n; i++){
			if(not vis[i]) can = false;
		}
		puts(can ? "All stations are reachable." : "There are stations that are unreachable.");
		clear();
	}
	return 0;
}
