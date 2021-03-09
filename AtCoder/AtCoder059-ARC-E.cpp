#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:
	
	- Classic DP problem

	- Just notice that if we fix the number of candies for each children, we will

	  have to add g(0) * g(1) * ... * g(n - 1), where

	  g(i) = a[i]^e[i] + (a[i] + 1)^e[i] + ... + b[i]^e[i]

	- Thus, we can just model the problem as a Knapsack and multiply the adding

	  for the chosen exponent with the result of DP(pos + 1, left - e[pos])

	- Preprocess the sum of powers to get them in O(1) to improve the complexity.

	- Complexity: O(nC^2)
*/

const int N = 400 + 5;
const int MOD = 1000000000 + 7;

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = (1ll * r * a) % MOD;
		a = (1ll * a * a) % MOD;
		b >>= 1;
	}
	return r;
}

int n;
int C;
int a[N];
int b[N];
int pot[N][N];
bool vis[N][N];
int memo[N][N];

void preprocess(){
	for(int i = 1; i < N; i++) pot[0][i] = 1;
	for(int e = 1; e <= C; e++){
		for(int i = 1; i < N; i++){
			pot[e][i] = (1ll * pot[e - 1][i] * i) % MOD;
		}
	}
	for(int e = 0; e <= C; e++){
		for(int i = 1; i < N; i++){
			pot[e][i] += pot[e][i - 1];
			if(pot[e][i] >= MOD) pot[e][i] -= MOD;
		}
	}
}

int query(int e, int l, int r){
	return (pot[e][r] + MOD - pot[e][l - 1]) % MOD;
}

int DP(int pos, int left){
	if(pos == n) return left == 0;
	if(vis[pos][left]) return memo[pos][left];
	int ans = 0;
	for(int i = 0; i <= left; i++){
		ans += mul(query(i, a[pos], b[pos]), DP(pos + 1, left - i));
		if(ans >= MOD) ans -= MOD;
	}
	vis[pos][left] = true;
	return memo[pos][left] = ans;
}

int main(){
	scanf("%d %d", &n, &C);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++) scanf("%d", b + i);
	preprocess();
	printf("%d\n", DP(0, C));
	return 0;
}
