#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Just notice that gcd(i, i + 1) = 1, so any continuous range with length >= 2

	  will have gcd = 1, the only exception is the range [n, n], whose gcd is n

	  Thus, answer is 2n - 1

	- Complexity: O(1)

*/

long long n;

int main(){
	scanf("%lld", &n);
	printf("%lld\n", 2 * n - 1);
	return 0;
}
