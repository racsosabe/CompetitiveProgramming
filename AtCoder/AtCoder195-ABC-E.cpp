#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;
const int MOD = 7;

int n;
char S[N];
char X[N];
int memo[N][MOD];

void solve(){
	for(int i = 1; i < MOD; i++) memo[n][i] = 1;
	for(int i = n - 1; i >= 0; i--){
		int turn = S[i] == 'A';
		int x = X[i] - '0';
		for(int j = 0; j < MOD; j++){
			int nxt_mod = (j * 10 + x) % MOD;
			memo[i][j] = turn ^ 1;
			if(memo[i + 1][nxt_mod] == turn) memo[i][j] = turn;
			nxt_mod = (j * 10) % MOD;
			if(memo[i + 1][nxt_mod] == turn) memo[i][j] = turn;
		}
	}
}

int main(){
	scanf("%d", &n);
	scanf("%s %s", X, S);
	solve();
	puts(memo[0][0] ? "Aoki" : "Takahashi");
	return 0;
}
