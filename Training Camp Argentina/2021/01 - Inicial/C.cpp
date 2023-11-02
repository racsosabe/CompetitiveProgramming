#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
char s[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool validPos(int i, int j){
	return i >= 0 and j >= 0 and i < n and j < n;
}

bool solve(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			int cnt = 0;
			for(int k = 0; k < 4; k++){
				int vx = i + dx[k];
				int vy = j + dy[k];
				if(validPos(vx, vy) and s[vx][vy] == 'o') cnt ^= 1;
			}
			if(cnt) return false;
		}
	}
	return true;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		scanf("%s", s[i]);
	}
	puts(solve() ? "YES" : "NO");
	return 0;
}
