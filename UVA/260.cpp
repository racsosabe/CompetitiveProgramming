#include<bits/stdc++.h>
using namespace::std;

const int N = 200 + 5;

int n;
char s[N][N];
bool vis[N][N];
int dx[] = {-1, -1, 0, 0, 1, 1};
int dy[] = {-1, 0, 1, -1, 1, 0};

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < n;
}

void BFS(int x, int y, char c){
	queue<int> Q;
	Q.emplace(x);
	Q.emplace(y);
	vis[x][y] = true;
	while(!Q.empty()){
		int ux = Q.front();
		Q.pop();
		int uy = Q.front();
		Q.pop();
		for(int k = 0; k < 6; k++){
			int vx = ux + dx[k];
			int vy = uy + dy[k];
			if(validPos(vx, vy) and !vis[vx][vy] and s[vx][vy] == c){
				vis[vx][vy] = true;
				Q.emplace(vx);
				Q.emplace(vy);
			}
		}
	}
}

void clear(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			vis[i][j] = false;
		}
	}
}

int solve(){
	int ans = 0;
	for(int i = 0; i < n; i++){
		if(s[i][0] == 'w' and !vis[i][0]) BFS(i, 0, 'w');
	}
	for(int i = 0; i < n; i++){
		if(vis[i][n - 1]) ans = 1;
	}
	clear();
	return ans;
}

int main(){
	int caso = 1;
	while(scanf("%d", &n) == 1 and n){
		for(int i = 0; i < n; i++){
			scanf("%s", s[i]);
		}
		printf("%d %c\n", caso++, solve() ? 'W' : 'B');
	}
	return 0;
}
