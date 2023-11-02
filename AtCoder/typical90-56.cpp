#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const int MAX = 100000 + 5;

int n;
int s;
int a[2][N];
bool vis[N][MAX];
bool memo[N][MAX];
bool choice[N][MAX];

bool DP(int pos, int left){
	if(left < 0) return false;
	if(pos == n) return left == 0;
	if(vis[pos][left]) return memo[pos][left];
	bool ans = false;
	for(int i = 0; i < 2; i++){
		if(DP(pos + 1, left - a[i][pos])){
			choice[pos][left] = i;
			ans = true;
		}
	}
	vis[pos][left] = true;
	return memo[pos][left] = ans;
}

void rebuild(int pos, int left){
	if(pos == n){
		puts("");
		return;
	}
	putchar('A' + choice[pos][left]);
	left -= a[choice[pos][left]][pos];
	rebuild(pos + 1, left);
}

int main(){
	scanf("%d %d", &n, &s);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 2; j++){
			scanf("%d", &a[j][i]);
		}
	}
	if(not DP(0, s)){
		puts("Impossible");
		return 0;
	}
	rebuild(0, s);
	return 0;
}
