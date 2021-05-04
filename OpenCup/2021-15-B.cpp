#include<bits/stdc++.h>
using namespace::std;

const int MAX = 500 * 500 + 5;
const int N = 500 + 5;

int n;
int m;
int x[MAX];
int y[MAX];
int U[N][N];
int D[N][N];
int L[N][N];
int R[N][N];
bool vis[N][N];
long long ans = 0;

void updateCol(int j){
	for(int i = 1; i <= n; i++){
		if(vis[i][j]) D[i][j] = 1 + D[i - 1][j];
		else D[i][j] = 0;
	}
	for(int i = n; i >= 1; i--){
		if(vis[i][j]) U[i][j] = 1 + U[i + 1][j];
		else U[i][j] = 0;
	}
}

void updateRow(int i){
	for(int j = 1; j <= m; j++){
		if(vis[i][j]) L[i][j] = 1 + L[i][j - 1];
		else L[i][j] = 0;
	}
	for(int j = m; j >= 1; j--){
		if(vis[i][j]) R[i][j] = 1 + R[i][j + 1];
		else R[i][j] = 0;
	}
}

void update(int a, int b){
	vis[a][b] = true;
	updateRow(a);
	updateCol(b);

}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n * m; i++){
		scanf("%d %d", x + i, y + i);
	}
	stack<long long> S;
	for(int i = n * m - 1; i >= 0; i--){
		S.emplace(ans);
		update(x[i], y[i]);
	}
	while(!S.empty()){
		printf("%lld\n", S.top());
		S.pop();
	}
	return 0;
}
