#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that if we go from i = n to 1 and check the current parity of a[i]

	  we will know if we must put a ball in box i. After that we can update the 

	  divisors of i by switching their parity (a[j] ^= 1 for j | i).

	- Since we will iterate over all the divisors in the worst case, the complexity is O(nlogn)

*/

const int N = 200000 + 5;

int n;
int a[N];
int b[N];
vector<int> D[N];

void init() {
	for(int i = 1; i <= n; i++) {
		for(int j = i; j <= n; j += i) {
			D[j].emplace_back(i);
		}
	}
}

int main() {
	scanf("%d", &n);
	init();
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	vector<int> res;
	for(int i = n; i >= 1; i--) {
		if(a[i]) {
			res.emplace_back(i);
			for(int d : D[i]) a[d] ^= 1;
		}
	}
	printf("%d\n", (int)res.size());
	for(int i = 0; i < res.size(); i++) printf("%d%c", res[i], " \n"[i + 1 == res.size()]);
	return 0;
}
