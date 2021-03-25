#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- DP problem.

	- Let's define f(k) as the number of infinite sequences with the conditions
	
	  defined in the problem but changing i >= n to i >= k in the first one.

	- Then, we can analyze by cases the possibilities:

	  1) If a[1] = 1, then the next k - 1 elements can be whatever they want

	     constrained by the conditions, basically is a valid infinite sequence

	     with parameter k - 1, so we have f(k - 1) sequences.

	  2) If we have a[1] > 1 and a[2] > 1, then the sequence will be fixed already,

	     so the number of such sequences is (n - 1) * (n - 1).

	  3) If we have a[1] > 1 and a[2]....a[1 + a[1]] = 1, we must consider two cases as well:

	     - a[1] + 1 < k, then the answer is f(k - a[1] - 1)

	     - a[1] + 1 >= k, then the answer is fixed, so we have the following 

	       inequality:

	       a[1] + 1 >= k -> a[1] >= k - 1, but a[1] <= n

	       k - 1 <= a[1] <= n -> n - k + 2 possibilities.

	  So we will have the following recursion:

	  f(k) = (n - 1)^2 + (n - k + 2) + f(k - 1) + f(k - 3) + f(k - 4) + ... + f(1)

	- Note: The base cases will be f(1) = n and f(2) = n^2, since the recursion

	  will be counting twice the sequence 1, 1 (it holds the case 1) and 3) with a[1] = 2 - 1).

	- Complexity: O(n) if we use an extra variable to store the sum of f(x) for x <= k - 3.
*/

const int N = 1000000 + 5;
const int MOD = 1000000000 + 7;

inline void add(int &r, int a){
	r += a;
	if(r >= MOD) r -= MOD;
}

int mul(int a, int b){
	return (1ll * a * b) % MOD;
}

int n;
int memo[N];

int solve(){
	memo[1] = n;
	memo[2] = mul(n, n);
	int suma = 0;
	for(int i = 3; i <= n; i++){
		if(i - 3 >= 1) add(suma, memo[i - 3]);
		add(memo[i], mul(n - 1, n - 1));
		add(memo[i], n - i + 2);
		add(memo[i], memo[i - 1]);
		add(memo[i], suma);
	}
	return memo[n];
}

int main(){
	scanf("%d", &n);
	printf("%d\n", solve());
	return 0;
}
