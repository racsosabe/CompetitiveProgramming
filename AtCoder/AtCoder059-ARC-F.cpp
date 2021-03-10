#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- DP & Counting problem

	- Consider that we form all the strings with a given length by using the n movements,

	  then, since each character has 2 possibilities, we will get 2^len different

	  strings each time. 

	- However, we are just looking to get 1 particular string from all those, so

	  our answer must be divided by 2^len.

	- We can compute the first value using DP, considering the insertion transitions

	  for each character and the deletion transition.

	- Complexity: O(n^2)

*/

const int N = 5000 + 5;
const int MOD = 1000000000 + 7;

int add(int a, int b){
	return a + b < MOD ? a + b : a + b - MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int pow_mod(int a, int b){
	int r = 1;
	while(b > 0){
		if(b & 1) r = mul(r, a);
		a = mul(a, a);
		b >>= 1;
	}
	return r;
}

int n;
int m;
char s[N];
int memo[N][N];

int solve(){
	memo[0][0] = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j <= n; j++){
			memo[i + 1][j + 1] += add(memo[i][j], memo[i][j]);
			if(memo[i + 1][j + 1] >= MOD) memo[i + 1][j + 1] -= MOD;
			memo[i + 1][max(0, j - 1)] += memo[i][j];
			if(memo[i + 1][max(0, j - 1)] >= MOD) memo[i + 1][max(0, j - 1)] -= MOD;
		}
	}
	return mul(memo[n][m], pow_mod((MOD + 1) / 2, m));
}

int main(){
	scanf("%d", &n);
	scanf("%s", s);
	m = strlen(s);
	printf("%d\n", solve());
	return 0;
}
