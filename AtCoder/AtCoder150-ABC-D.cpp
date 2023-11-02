#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Note that we need X to be a multiple of a[k] * (p + 0.5), but since every a[k]

	  can be expressed as 2 * b[k], we can change it to:

	  X must be a multiple of b[k] * (2p + 1).

	- First of all, we will focus on X being a multiple of each b[k], so it must be 

	  a multiple of their LCM (if this LCM turns out to be greater tham m at some point we must give 0 as the answer)

	- Now, if there exists some k such that LCM / b[k] is even, the answer is also

	  0 (since we need X to be b[k] * (odd integer)).

	- Otherwise, our answer will be m / LCM - (m / LCM) / 2 (since we are taking away

	  the even factors.
	
	- Complexity: O(n log MAX)

*/

const int N = 100000 + 5;

long long gcd(long long a, long long b) {
	while(b) {
		a %= b;
		swap(a, b);
	}
	return a;
}

int n;
int m;
int a[N];

int main() {
	scanf("%d %d", &n, &m);
	long long mcm = 1;
	for(int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		a[i] >>= 1;
		mcm *= a[i] / gcd(mcm, a[i]);
		if(mcm > m) {
			puts("0");
			return 0;
		}
	}
	for(int i = 1; i <= n; i++) {
		if((mcm / a[i]) % 2 == 0) {
			puts("0");
			return 0;
		}
	}
	printf("%lld\n", (m / mcm) - (m / mcm / 2));
	return 0;
}
