#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that the structure of color assignment is basically partition the array
	  into the minimum number of disjoint LISs
 
	- By Dillworth theorem, the answer to this problem is the length of the longest anti-chain,

	  so we will want to compute the Longest Non-Increasing Subsequence instead.

	  This can be done by reversing the array and computing the Longest Non-Decreasing Subsequence,

	  which could be easier to implement using upper_bound.

	- Complexity: O(nlogn)
*/

const int inf = 1e9 + 10;

int n;

int main() {
	scanf("%d", &n);
	vector<int> a(n);
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	reverse(a.begin(), a.end());
	vector<int> LNDS(n + 1, inf);
	LNDS[0] = -inf;
	for(int i = 0; i < n; i++) {
		int to = upper_bound(LNDS.begin(), LNDS.end(), a[i]) - LNDS.begin();
		LNDS[to] = a[i];
	}
	int ans = n;
	while(LNDS[ans] == inf) ans -= 1;
	printf("%d\n", ans);
	return 0;
}
