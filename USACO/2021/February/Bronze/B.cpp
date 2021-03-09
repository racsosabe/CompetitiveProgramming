#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;

int n;
int ans;
int v[N][N];
int ac[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool validPos(int x, int y){
	return x >= 0 and y >= 0 and x <= 1000 and y <= 1000;
}

int check(int x, int y){
	if(ac[x][y] == 0) return 0;
	int cnt = 0;
	for(int k = 0; k < 4; k++){
		int vx = x + dx[k];
		int vy = y + dy[k];
		if(validPos(vx, vy) and ac[vx][vy]){
			cnt += 1;
		}
	}
	return cnt == 3;
}

int solve(int x, int y){
	vector< pair<int, int> > cells;
	cells.emplace_back(make_pair(x, y));
	for(int k = 0; k < 4; k++){
		int vx = x + dx[k];
		int vy = y + dy[k];
		if(validPos(vx, vy)) cells.emplace_back(make_pair(vx, vy));
	}
	int res = 0;
	for(int i = 0; i < cells.size(); i++){
		int X = cells[i].first;
		int Y = cells[i].second;
		int new_v = check(X, Y);
		res += new_v - v[X][Y];
		v[X][Y] = new_v;
	}
	return res;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		ac[x][y] = 1;
		ans += solve(x, y);
		printf("%d\n", ans);
	}
	return 0;
}
