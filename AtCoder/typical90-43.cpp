#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int m;
int D[N][N];
char s[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool validPos(int i, int j){
	return i >= 1 and j >= 1 and i <= n and j <= m;
}

void BFS(int sx, int sy){
	memset(D, -1, sizeof D);
	queue<int> Q;
	Q.emplace(sx);
	Q.emplace(sy);
	D[sx][sy] = 0;
	while(!Q.empty()){
		int ux = Q.front(); Q.pop();
		int uy = Q.front(); Q.pop();
		for(int k = 0; k < 4; k++){
			int pos = 1;
			int vx = ux;
			int vy = uy;
			while(true){
				vx += dx[k]; vy += dy[k];
				if(not validPos(vx, vy)) break;
				if(s[vx][vy] == '#') break;
				if(D[vx][vy] != -1 and D[vx][vy] < 1 + D[ux][uy]) break;
				D[vx][vy] = D[ux][uy] + 1;
				Q.emplace(vx);
				Q.emplace(vy);
			}
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	int sx, sy, tx, ty;
	scanf("%d %d", &sx, &sy);
	scanf("%d %d", &tx, &ty);
	for(int i = 1; i <= n; i++){
		scanf("%s", s[i] + 1);
	}
	BFS(sx, sy);
	printf("%d\n", D[tx][ty] - 1);
	return 0;
}
