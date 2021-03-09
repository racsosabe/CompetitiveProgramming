#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 10;

int n;
int ans;
int cnt;
int a[N][N];
char s[N][N];
int vis[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < n;
}

void backtracking(int x, int y, int prefix, int want){
	if(prefix == 0){
		ans = max(ans, cnt);
	}
	for(int k = 0; k < 4; k++){
		int vx = x + dx[k];
		int vy = y + dy[k];
		if(validPos(vx, vy) and !vis[vx][vy]){
			if((want == 1 and prefix + a[x][y] >= 0) or (prefix + a[x][y] >= 0 and a[vx][vy] == want)){
				vis[vx][vy] = vis[x][y] + 1;
				cnt += 1;
				backtracking(vx, vy, prefix + a[vx][vy], a[vx][vy]);
				cnt -= 1;
				vis[vx][vy] = 0;
			}
		}
	}
}

int main(){
	setIO("hshoe", 1, 1);
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", s[i]);
		for(int j = 0; j < n; j++) a[i][j] = s[i][j] == '(' ? 1 : -1;
	}
	if(a[0][0] == 1){
		vis[0][0] = 1;
		cnt += 1;
		backtracking(0, 0, 1, 1);
		vis[0][0] = 0;
	}
	printf("%d\n", ans);
	return 0;
}
