#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that we can see the problem like a matching between two 1, 2, ..., n sequences

	- So, we can focus in adding the i-th element of both sequences at a time and consider

	  the matching as an open-close DP problem.

	- Thus, we can have the current position of the element to add (pos), the number of 

	  currently unmatched elements in each of the sequences (q1, q2) and the matching difference

	  left (k - cost of matching).

	- Now, we should notice that q1 = q2, since each time we match two elements both

	  sequences reduce in 1, so we only need to define the following function:


	  f(pos, unmatched, left) = Number of matchings such that we have already considered 

	  the first "pos" elements in each sequence, out of which "unmatched" elements in each sequence have not been

	  matched yet, we have "left" cost remaining to cover and we will add the "pos + 1" elements.

	- Notice that we have several options to make:

	  1) Match pos + 1 elements: This will not change the unmatched elements and will reduce "left" by 2 * unmatched, since each time we increase "pos" by 1

	     then it means that each "unmatched" element increases in 1 its distance with its matching element.

		 This adds f(pos + 1, unmatched, left - 2 * unmatched)
	
	  2) Match ONLY ONE of pos + 1 elements with an unmatched element: This will not change the number of unmatched elements and will reduce "left" by 2 * unmatched.

	     This adds f(pos + 1, unmatched, left - 2 * unmatched) 2 * unmatched times, since for each pair of type (pos + 1, X) and (X, pos + 1) X has "unmatched" possible values

	  3) Match BOTH pos + 1 elements to an unmatched element: This will reduce the number of unmatched elements in 1, since we will take 2 elements in each sequence. This will also reduce "left"

	     by 2 * (unmatched - 1).

		 This adds f(pos + 1, unmatched - 1, left - 2 * (unmatched - 1)) unmatched^2 times, since we choose independently two pairs (pos + 1, X) and (X, pos + 1) with X having "unmatched" possible values.

	  4) Don't match any of pos + 1 elements: This increases "unmatched" in 1 and reduces "left" by 2 * (unmatched + 1).

	     This adds f(pos + 1, unmatched + 1, left - 2 * (unmatched + 1))

	- The base case should be when pos == n and we will answer 1 if and only if left == 0 and unmatched == 0.

	  An additional check should be added to return 0 when left < 0.

	- Complexity: O(n^2 k).

*/

const int N = 50 + 5;
const int M = 50 * 50 + 5;
const int MOD = 1e9 + 7;

int mul(long long a, long long b) {
	return a * b % MOD;
}

int n;
int k;
int f[N];
bool vis[N][N][M];
int memo[N][N][M];

int DP(int pos, int unmatched, int left) {
	if(left < 0) return 0;
	if(pos == n) return left == 0 and unmatched == 0;
	if(vis[pos][unmatched][left]) return memo[pos][unmatched][left];
	int res = 0;
	res += DP(pos + 1, unmatched, left - 2 * unmatched); // Match pos - pos
	if(res >= MOD) res -= MOD;
	res += mul(unmatched << 1, DP(pos + 1, unmatched, left - 2 * unmatched)); // Match only one of pos with an unmatched
	if(res >= MOD) res -= MOD;
	res += mul(unmatched, mul(unmatched, DP(pos + 1, unmatched - 1, left - 2 * (unmatched - 1)))); // Match both pos with an unmatched (number of unmatched reduces in 1)
	if(res >= MOD) res -= MOD;
	res += DP(pos + 1, unmatched + 1, left - 2 * (unmatched + 1)); // Don't match pos yet
	if(res >= MOD) res -= MOD;
	vis[pos][unmatched][left] = true;
	return memo[pos][unmatched][left] = res;
}

int main() {
	scanf("%d %d", &n, &k);
	f[0] = 1;
	for(int i = 1; i <= n; i++) f[i] = mul(i, f[i - 1]);
	printf("%d\n", DP(0, 0, k));
	return 0;
}
