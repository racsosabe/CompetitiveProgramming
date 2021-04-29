#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Notice that the graph will have a cycle and some extra outgoing edges

	  from the nodes of the cycle. Thus, some nodes will have a fixed value

	  and the ones from the cycle can't be determined directly.

	- However, if we have some node u from the cycle and consider that its direct

	  children that don't belong to the cycle have values c_1, ..., c_k, then

	  the value of u can only be one of the two minimum non-negative integers

	  that aren't contained in c_1, ..., c_k.

	- Finally, we can check if any of the two values for node u can generate

	  a valid configuration of values.

	- Complexity: O(n)

*/

const int N = 200000 + 5;

int n;
int p[N];
int out[N];
int val[N];
bool vis[N];
bool used[N];
vector<int> G[N];
vector<int> Gt[N];

bool check(){
	bool can = true;
	for(int i = 1; i <= n; i++){
		for(int v : G[i]){
			if(val[v] == val[i]) can = false;
		}
		for(int v : Gt[i]){
			if(val[v] == val[i]) can = false;
		}
		for(int v : G[i]){
			vis[val[v]] = true;
		}
		int g = 0;
		while(vis[g]) g += 1;
		if(g != val[i]) can = false;
		for(int v : G[i]){
			vis[val[v]] = false;
		}
	}
	return can;
}

bool test(int src, int x){
	val[src] = x;
	queue<int> Q;
	Q.emplace(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		if(val[u] == -1){
			for(int v : G[u]){
				assert(val[v] != -1);
				vis[val[v]] = true;
			}
			int g = 0;
			while(vis[g]) g += 1;
			val[u] = g;
			for(int v : G[u]){
				assert(val[v] != -1);
				vis[val[v]] = false;
			}
		}
		for(int v : Gt[u]){
			if(val[v] != -1) continue;
			Q.emplace(v);
		}
	}
	bool ans = check();
	for(int i = 1; i <= n; i++){
		if(not used[i]){
			out[i] = 1;
			val[i] = -1;
		}
	}
	return ans;
}

void solve(){
	memset(val, -1, sizeof val);
	queue<int> Q;
	for(int i = 1; i <= n; i++){
		if(out[i] == 0){
			Q.emplace(i);
			used[i] = true;
			val[i] = 0;
		}
	}
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		if(val[u] == -1){
			for(int v : G[u]){
				vis[val[v]] = true;
			}
			int g = 0;
			while(vis[g]) g++;
			val[u] = g;
			for(int v : G[u]){
				vis[val[v]] = false;
			}
		}
		for(int v : Gt[u]){
			out[v] -= 1;
			if(out[v] == 0){
				Q.emplace(v);
				used[v] = true;
			}
		}
	}
	bool found = false;
	for(int i = 1; i <= n; i++){
		if(not used[i]){
			int nxt = -1;
			for(int v : G[i]){
				if(val[v] == -1) continue;
				vis[val[v]] = true;
			}
			int g1 = 0;
			while(vis[g1]) g1 += 1;
			int g2 = g1 + 1;
			while(vis[g2]) g2 += 1;
			for(int v : G[i]){
				if(val[v] == -1) continue;
				vis[val[v]] = false;
			}
			if(test(i, g1)){
				found = true;
			}
			if(test(i, g2)){
				found = true;
			}
			break;
		}
	}
	puts(found ? "POSSIBLE" : "IMPOSSIBLE");
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", p + i);
		Gt[i].emplace_back(p[i]);
		G[p[i]].emplace_back(i);
		out[p[i]] += 1;
	}
	solve();
	return 0;
}
