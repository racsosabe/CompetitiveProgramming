#include<cstdio>
#include<vector>
#include<cmath>
using namespace::std;

const int N = 10000 + 5;

int n;
int a[N];
int in[N];
int sum[N];
int subtree[N];
vector<int> G[N];
long long memo[N];

long long DP(int u){
	subtree[u] = 1;
	sum[u] = a[u];
	memo[u] = 0;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		memo[u] += DP(v) + (subtree[v] - sum[v] >= 0 ? subtree[v] - sum[v] : sum[v] - subtree[v]);
		sum[u] += sum[v];
		subtree[u] += subtree[v];
	}
	return memo[u];
}

void clear(){
	for(int i = 1; i <= n; i++){
		in[i] = 0;
		G[i].clear();
	}
}

int main(){
	while(scanf("%d", &n) == 1 and n){
		for(int i = 1; i <= n; i++){
			int u, x, q;
			scanf("%d %d %d", &u, &x, &q);
			a[u] = x;
			for(int j = 0; j < q; j++){
				int v;
				scanf("%d", &v);
				in[v] = 1;
				G[u].push_back(v);
			}
		}
		for(int i = 1; i <= n; i++){
			if(in[i]) continue;
			printf("%lld\n", DP(i));
		}
		clear();
	}
	return 0;
}
