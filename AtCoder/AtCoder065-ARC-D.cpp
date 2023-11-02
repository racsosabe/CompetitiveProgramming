#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int m[2];
int a[2][N];
bool vis[N];
vector<int> G[N];

int main(){
	scanf("%d %d %d", &n, &m[0], &m[1]);
	for(int id = 0; id < 2; id++){
		for(int i = 1; i <= n; i++){
			G[i].clear();
			vis[i] = false;
		}
		for(int j = 0; j < m[id]; j++){
			int u, v;
			scanf("%d %d", &u, &v);
			G[u].emplace_back(v);
			G[v].emplace_back(u);
		}
		int c = 1;
		for(int i = 1; i <= n; i++){
			if(vis[i]) continue;
			queue<int> Q;
			Q.emplace(i);
			vis[i] = true;
			a[id][i] = c;
			while(!Q.empty()){
				int u = Q.front();
				Q.pop();
				for(int v : G[u]){
					if(vis[v]) continue;
					Q.emplace(v);
					a[id][v] = c;
					vis[v] = true;
				}
			}
			c++;
		}
	}
	map< pair<int, int>, int> F;
	for(int i = 1; i <= n; i++){
		F[make_pair(a[0][i], a[1][i])] += 1;
	}
	for(int i = 1; i <= n; i++){
		printf("%d%c", F[make_pair(a[0][i], a[1][i])], " \n"[i == n]);
	}
	return 0;
}
