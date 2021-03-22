#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- DP problem.

	- First, notice that we can just consider the maximum of all r for a fixed l.

	- Thus, we only have O(n) intervals to shuffle and we can just map each l to its
	
	  corresponding r_l (if there is no such r, we can consider r_l = l)

	- Now, let's assume that we have fixed the values from the first l - 1 positions.

	  Then, we are interested in the following information:

	  - The number of ones that are left to be assigned.

	  - The upper bound of the interval to be shuffled (let it be R)

	- If R < r_l for the given l, we can extend the upper bound to r_l (and adding the
	
	  corresponding number of ones). Otherwise, we don't do anything.

	  It's easy to notice that R is max(r_1, r_2, ..., r_l) after the previous step.

	- If we set r_i = max(r_1, ..., r_i) beforehand, we just need to add the number

	  of ones in the interval (r_(l - 1), r_i] each time (let this variable be extra).

	- We can define memo[l][o] as the number of different strings that we can get

	  given that we have fixed the first l - 1 characters and we need to assign

	  o ones.

	- The transition is not really hard if we sum up the previous observations:

	  extra = ac(r_l) - ac(r_(l - 1)), where ac(i) is the number of ones in the prefix [1, i]

	  The maximum number of ones that can be carried by after the previous position

	  is r_(l - 1) - (l - 1), so we will define limit_ones = r_(l - 1) - l + 1.

	  Then, for all j in [0, limit_ones] we can update:

	  memo[l][j + extra] = memo[l - 1][j] + memo[l - 1][j + 1]

	  The first term is if we assigned 0 to position l - 1 and the second one is

	  if we assigned 1.

	- Our answer will be memo[n + 1][0], which we can compute by assigning r_(n + 1) = n + 1
	
	  and ac(n + 1) = ac(n). We can get the same result by appending a '0' to our

	  string and computing memo[s.size()][0].

	- Complexity: O(n^2 + m)
*/

const int N = 3000 + 5;
const int MOD = 1000000000 + 7;

int n;
int m;
int R[N];
char s[N];
int ac[N];
int memo[N][N];

int solve(){
	memo[0][0] = 1;
	for(int i = 1; i <= n; i++){
		int extra = ac[R[i]] - ac[R[i - 1]];
		int limit_ones = R[i - 1] - i + 1;
		for(int j = 0; j <= limit_ones; j++){
			int &res = memo[i][j + extra];
			res = memo[i - 1][j] + memo[i - 1][j + 1];
			if(res >= MOD) res -= MOD;
		}
	}
	return memo[n][0];
}

int main(){
	scanf("%d %d", &n, &m);
	scanf("%s", s + 1);
	s[++n] = '0';
	for(int i = 1; i <= m; i++){
		int l, r;
		scanf("%d %d", &l, &r);
		R[l] = max(R[l], r);
	}
	for(int i = 1; i <= n; i++){
		ac[i] = ac[i - 1] + s[i] - '0';
		R[i] = max(R[i], R[i - 1]);
		if(R[i] < i) R[i] = i;
	}
	printf("%d\n", solve());
	return 0;
}
