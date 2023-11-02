#include<bits/stdc++.h>
using namespace::std;

const int MAX = 100000 + 5;
const int MOD = 1000000000 + 7;

int n;
int memo[MAX];

int solve(){
	memo[0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= min(i, 9); j++){
			memo[i] += memo[i - j];
			if(memo[i] >= MOD) memo[i] -= MOD;
		}
	}
	return memo[n];
}

int main(){
	scanf("%d", &n);
	if(n % 9) puts("0");
	else printf("%d\n", solve());
	return 0;
}
