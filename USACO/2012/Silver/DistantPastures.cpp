#include<bits/stdc++.h>
using namespace::std;

void setIO(string name, bool input, bool output){
	string inputname = name + ".in";
	string outputname = name + ".out";
	if(input) freopen(inputname.c_str(), "r", stdin);
	if(output) freopen(outputname.c_str(), "w", stdout);
}

const int N = 900 + 5;
const int inf = 1e9;

int n;
int A, B;
int d[N][N];
char s[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < n;
}

int solve(){
	int len = n * n;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			d[i][j] = i == j ? 0 : inf;
		}
	}
	for(int i = 0; i < len; i++){
		int x = i / n;
		int y = i % n;
		for(int k = 0; k < 4; k++){
			int vx = x + dx[k];
			int vy = y + dy[k];
			if(validPos(vx, vy)){
				d[i][vx * n + vy] = (s[x][y] == s[vx][vy] ? A : B);
			}
		}
	}
	for(int k = 0; k < len; k++){
		for(int i = 0; i < len; i++){
			for(int j = 0; j < len; j++){
				if(d[i][j] > d[i][k] + d[k][j]) d[i][j] = d[i][k] + d[k][j];
			}
		}
	}
	int res = 0;
	for(int i = 0; i < len; i++){
		for(int j = 0; j < len; j++){
			res = max(res, d[i][j]);
		}
	}
	return res;
}

int main(){
	setIO("distant", 1, 1);
	scanf("%d %d %d", &n, &A, &B);
	for(int i = 0; i < n; i++){
		scanf("%s", s[i]);
	}
	printf("%d\n", solve());
	return 0;
}
