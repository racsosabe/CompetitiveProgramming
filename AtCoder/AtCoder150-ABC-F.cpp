#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that if we apply the shift and then the Xor with the same value X, the XOR 

	  between each pair of adjacent elements (cyclic) doesn't change at all, so we can

	  use this for pattern matching.

	- The only obstacle for this is the cyclic xor difference (a[n - 1] ^ a[0]), so 

	  we must match first the non-cyclic xor differences and check the cyclic one

	  for each candidate.
	
	  After this, if a candidate is valid, then the shift value is known and the 

	  X value should be a[0] ^ b[k].

	- Complexity: O(n) if we use some linear algorithm for pattern matching

*/

const int N = 200000 + 5;

int n;
int a[N];
int b[N];

void solve() {
	vector<int> dif_xor;
	for(int i = 1; i < n; i++) dif_xor.emplace_back(a[i] ^ a[i - 1]);
	dif_xor.emplace_back(-1);
	vector<int> pi(dif_xor.size(), 0);
	int k = 0;
	for(int i = 1; i < dif_xor.size(); i++) {
		while(k and dif_xor[k] != dif_xor[i]) k = pi[k - 1];
		if(dif_xor[k] == dif_xor[i]) k += 1;
		pi[i] = k;
	}
	vector<int> dif_b;
	for(int i = 1; i < 2 * n - 1; i++) dif_b.emplace_back(b[i % n] ^ b[(i + n - 1) % n]);
	k = 0;
	vector<int> res(n, -1);
	for(int i = 0; i < dif_b.size(); i++) {
		while(k and dif_b[i] != dif_xor[k]) k = pi[k - 1];
		if(dif_b[i] == dif_xor[k]) k += 1;
		if(k == n - 1) {
			if((b[(i + 1) % n] ^ b[(i + 2) % n]) == (a[n - 1] ^ a[0])) {
				res[(2 * n - (i + 2)) % n] = a[0] ^ b[(i + 2) % n];
			}
		}
	}
	for(int i = 0; i < n; i++) {
		if(~res[i]) printf("%d %d\n", i, res[i]);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	for(int i = 0; i < n; i++) scanf("%d", b + i);
	if(n == 1) {
		printf("0 %d\n", a[0] ^ b[0]);
		return 0;
	}
	solve();
	return 0;
}
