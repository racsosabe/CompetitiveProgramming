#include<bits/stdc++.h>
using namespace::std;

const int N = 10000 + 5;
const int MOD = 1000000000 + 7;

int n;
int memo[2][N];

int main(){
	scanf("%d", &n);
	memo[0][0] = 1;
	for(int i = 0; i < n; i++){
		int cur = i & 1;
		int nxt = cur ^ 1;
		for(int j = 0; j <= i + 1; j++) memo[nxt][j] = 0;
		for(int j = 0; j <= i; j++){
			memo[nxt][j + 1] += memo[cur][j];
			if(memo[nxt][j + 1] >= MOD) memo[nxt][j + 1] -= MOD;
			if(j == 0) continue;
			memo[nxt][j - 1] += memo[cur][j];
			if(memo[nxt][j - 1] >= MOD) memo[nxt][j - 1] -= MOD;
		}
	}
	printf("%d\n", memo[n & 1][0]);
	return 0;
}
