#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- DP & Counting problem.

	- Just notice that we need to know how many people are left to assign to the

	  groups and the size of the next groups to form.

	- Thus, we can do one of the following:

	  1) Don't form any group with our current size (which means F_i = 0)

	  2) Form between c and d groups.

	- For the second case, we need to count correctly, so we can say that we 

	  will take size people for the first group, for which we have C(left, size)

	  ways to do so, then for the second one we have C(left - size, size), and 

	  so on until the i-th one. If we write down the terms of the multiplication

	  we will end up with the following expression:

	  (size!)^(-i) * left! * ((left - i * size)!)^(-1)

	  However, we are not taking in consideration the order of the groups, so 

	  we must divide the factor by (i!)^(-1)

	  Thus, if f(s, l) is the number of different valid partitions we can make

	  given that we already formed all the groups with size < s and we have l 

	  people left, our recurrence will be:

	  f(s, l) = f(s + 1, l) + sum from i = c to d f(s + 1, l - i * s) * (s!)^(-i) * l! * ((l - i * s)!)^(-1)

	- One can think that the iteration for the sum is O(n), which is true, but

	  since we will be taking different s values, the complexity for a given l

	  is O(l * H_n), which is O(nlogn). Remember that we have O(n) different l values.

	- Complexity: O(n^2 logn).
*/

const int N = 1000 + 5;
const int MOD = 1000000000 + 7;

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
int a;
int b;
int c;
int d;
int f[N];
int fi[N];
int memo[N][N];

void init(){
	f[0] = 1;
	for(int i = 1; i < N; i++) f[i] = (1ll * i * f[i - 1]) % MOD;
	fi[N - 1] = pow_mod(f[N - 1], MOD - 2);
	for(int i = N - 2; i >= 0; i--){
		fi[i] = (1ll * (i + 1) * fi[i + 1]) % MOD;
	}
}

int solve(){
	int len = b - a + 1;
	memo[len][0] = 1;
	for(int i = len - 1; i >= 0; i--){
		int s = i + a;
		memo[i][0] = 1;
		for(int l = 1; l <= n; l++){
			memo[i][l] = memo[i + 1][l];
			int fise = pow_mod(fi[s], c);
			for(int j = c; j <= d and j * s <= l; j++){
				int factor = (1ll * f[l] * fi[l - j * s]) % MOD;
				factor = (1ll * factor * fise) % MOD;
				factor = (1ll * factor * fi[j]) % MOD;
				memo[i][l] += (1ll * memo[i + 1][l - j * s] * factor) % MOD;
				if(memo[i][l] >= MOD) memo[i][l] -= MOD;
				fise = (1ll * fise * fi[s]) % MOD;
			}
		}
	}
	return memo[0][n];
}

int main(){
	init();
	scanf("%d %d %d %d %d", &n, &a, &b, &c, &d);
	printf("%d\n", solve());
	return 0;
}
