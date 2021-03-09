#include<bits/stdc++.h>
using namespace::std;

const int N = 3010 + 5;

int n;
int ans;
int cow[N][N];
int cnt[N][N];
queue<int> pendingX;
queue<int> pendingY;
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool validPos(int x, int y){
	return x >= 0 and y >= 0 and x < N and y < N;
}

void update(int x, int y, int a){
	if(cow[x][y]){
		ans -= 1 - a;
		return;
	}
	ans += a;
	cow[x][y] = 1;
	if(cnt[x][y] == 3){
		pendingX.emplace(x);
		pendingY.emplace(y);
	}
	for(int k = 0; k < 4; k++){
		int vx = x + dx[k];
		int vy = y + dy[k];
		if(validPos(vx, vy)){
			cnt[vx][vy] += 1;
			if(cnt[vx][vy] == 3 and cow[vx][vy]){
				pendingX.emplace(vx);
				pendingY.emplace(vy);
			}	
		}
	}
}

void adjust(){
	while(!pendingX.empty()){
		int x = pendingX.front(); pendingX.pop();
		int y = pendingY.front(); pendingY.pop();
		for(int k = 0; k < 4; k++){
			int vx = x + dx[k];
			int vy = y + dy[k];
			if(validPos(vx, vy) and cow[vx][vy] == 0){
				update(vx, vy, 1);
			}
		}
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		int x, y;
		scanf("%d %d", &x, &y);
		x += 1000;
		y += 1000;
		update(x, y, 0);
		adjust();
		printf("%d\n", ans);
	}
	return 0;
}
