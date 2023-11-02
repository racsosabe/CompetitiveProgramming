#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Since the value of n is not that big, we can compute the cycle for each possible

	  start in O(n), so we can have the prefix sums and then just analyze each possible

	  path.

	- The structure of each path should be:
	
	  (some prefix of size r <= length of the cycle) + max{0, (floor(k - r) / k * sum of the cycle)}

	- Complexity: O(n^2)
*/

const int N = 5000 + 5;

int n;
int k;
int p[N];
int c[N];
int a[N];
bool vis[N];
long long maxpre[N];
long long prefix[N];

long long solve(int at) {
	int x = at;
	int len = 0;
	maxpre[0] = LLONG_MIN;
	do {
		x = p[x];
		len += 1;
		prefix[len] = prefix[len - 1] + c[x];
		maxpre[len] = max(maxpre[len - 1], prefix[len]);
	} while(x != at);
	if(len >= k) return maxpre[k];
	long long res = maxpre[len];
	if(prefix[len] >= 0) {
		for(int r = 1; r <= len; r++) {
			res = max(res, prefix[len] * ((k - r) / len) + maxpre[r]);
		}
	}
	return res;
}

int main() {
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", p + i);
	for(int i = 1; i <= n; i++) scanf("%d", c + i);
	long long res = LLONG_MIN;
	for(int i = 1; i <= n; i++) res = max(res, solve(i));
	printf("%lld\n", res);
	return 0;
}
