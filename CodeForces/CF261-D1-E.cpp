#include<bits/stdc++.h>
using namespace::std;

int l, r, p;
vector<int> primes;

int is_prime(int x) {
	if(x == 1) return false;
	for(int i = 2; i * i <= x; i++) {
		if(x % i == 0) return false;
	}
	return true;
}

int main() {
	scanf("%d %d %d", &l, &r, &p);
	for(int i = 2; i <= p; i++) if(is_prime(i)) primes.emplace_back(i);

	return 0;
}
