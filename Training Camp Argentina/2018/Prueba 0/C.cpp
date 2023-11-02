#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx2")
#include<bits/stdc++.h>
using namespace std;

const int N = 1000 + 5;
const int p[] = {2, 5};
const int inf = 1e8;

int n;
int ans[2];
int a[N][N];
int b[2][N][N];
int memo[2][N][N];

void solve(int id){
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(a[i][j] == 0) b[id][i][j] = -1;
			else{
				int x = a[i][j];
				while(x % p[id] == 0){
					b[id][i][j] += 1;
					x /= p[id];
				}
			}
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			if(i == 1 and j == 1){
				memo[id][i][j] = b[id][i][j];
				continue;
			}
			if(b[id][i][j] == -1){
				memo[id][i][j] = -1;
				continue;
			}
			int val_up = i > 1 ? (memo[id][i - 1][j] == -1 ? -1 : memo[id][i - 1][j] + b[id][i][j]) : inf;
			int val_left = j > 1 ? (memo[id][i][j - 1] == -1 ? -1 : memo[id][i][j - 1] + b[id][i][j]) : inf;
			if(abs(val_up) < abs(val_left)){
				memo[id][i][j] = val_up;
			}
			else{
				memo[id][i][j] = val_left;
			}
		}
	}
	ans[id] = memo[id][n][n];
}

void build(int id){
	printf("%d\n", abs(ans[id]));
	int i = n;
	int j = n;
	stack<char> S;
	while(i != 1 or j != 1){
		int val_up = memo[id][i - 1][j] == -1 ? -1 : (i > 1 ? memo[id][i - 1][j] + b[id][i][j] : inf);
		int val_left = memo[id][i][j - 1] == -1 ? -1 : (j > 1 ? memo[id][i][j - 1] + b[id][i][j] : inf);
		if(abs(val_up) < abs(val_left)){
			i -= 1;
			S.emplace('D');
		}
		else{
			j -= 1;
			S.emplace('R');
		}
	}
	while(!S.empty()){
		putchar(S.top());
		S.pop();
	}
	puts("");
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	for(int id = 0; id < 2; id++){
		solve(id);
	}
	if(abs(ans[0]) < abs(ans[1])) build(0);
	else build(1);
	return 0;
}
